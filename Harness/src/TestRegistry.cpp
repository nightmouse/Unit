#include "Basic/src/rc_ptr.h"
#include "Basic/src/StringUtils.h"
#include "Harness/src/ITest.h"
#include "Harness/src/JsonFormatter.h"
#include "Harness/src/TestContext.h"
#include "Harness/src/TestRegistry.h"
#include "Harness/src/TestResults.h"

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace Unit;

static string TestName_s;

void SegvHandler(int sig)
{
    cerr << "Test [" << TestName_s << "] caused a segmentation fault." << endl;
    exit(-1);
}

typedef std::vector<ITest::Ptr> VectorType;

// singleton implementation class
class impl
{
    public:
        static impl * GetInstance() 
        { 
            if (!instance_m.get()) { 
                instance_m.reset(new impl);
            }
            return instance_m.get();
        }

        bool registerTest(ITest * ptr) 
        { 
            try { 
                ITest::Ptr tmp(ptr);
                if (!isUniqueName(tmp->getName())) { 
                    badName_m = tmp->getName();
                    return false;
                }
                tests_m.push_back(tmp);
            } catch(std::exception & e) { 
                return false;
            }
            return true;
        }

        void runTests(const TestSpec & spec) const 
        {
            if (!badName_m.empty()) { 
                throw runtime_error("Two or more tests registered with name [" + badName_m + "]");
            }
            signal(SIGSEGV, SegvHandler); // set up the signal handler for segmentation faults

            // add or remove tests based on the command line
            VectorType selected = filterTests(spec); 

            // run the tests
            VectorType::iterator i;
            for (i=selected.begin(); i!=selected.end(); ++i) {
                const ITest::Ptr tmp(*i); 
                TestContext context(tmp);
                try { 
                    TestName_s = tmp->getName();
                    context.run();
                } catch(const exception & e) { 
                   context.fail(string("failed with exception: ") + e.what());
                } catch (...) { 
                   context.fail("failed with an unknown exception: ");
                }
            }

            // save results
            const string & outFile = spec.getJsonFile();
            if (outFile.size()) { 
                string data;
                JsonFormatter * f = new JsonFormatter;
                TestResults * results = TestResults::GetInstance();
                results->getResults(f, data);
                delete f;

                ofstream file(outFile.c_str(), ios::out|ios::trunc);
                if (!file.is_open()) { 
                    throw runtime_error("Could not open [" + outFile + "]");
                }
                file << data;
                file.close();
            }
        } // end runTests

        int getErrorCount() const
        {
            return TestResults::GetInstance()->getErrorCount();
        }

    private:
        VectorType filterTests(const TestSpec & spec) const 
        { 
            const set<string> & include = spec.getTests();
            const set<string> & excludes = spec.getExcludedTests();
            VectorType selected;

            // if any includes were specified on the command line - add them now
            if (include.empty()) { 
                selected = tests_m; // copy all the tests
            } else { 
                set<string>::const_iterator i;
                bool found = false;
                for (i=include.begin(); i!=include.end(); ++i) { 
                    VectorType::const_iterator j;
                    for (j=tests_m.begin(); j!=tests_m.end(); ++j) { 
                        const ITest::Ptr tmp(*j); // make the underlying smart pointer easier to access
                        if (StringUtils::BeginsWith(*i, tmp->getName())) { 
                            selected.push_back(tmp);
                            found = true;
                        }
                    }

                    if (!found) { 
                        throw runtime_error("could not find test name specified from command line: " + *i);
                    }
                } // end for
            } // end if

            // apply the excludes specified on the command line
            set<string>::const_iterator i;
            for (i=excludes.begin(); i!=excludes.end(); ++i) {
                VectorType::iterator j = selected.begin();
                bool found = false;
                while(j != selected.end()) { 
                    const ITest::Ptr tmp(*j); 
                    if (StringUtils::BeginsWith(*i, tmp->getName())) { 
                        selected.erase(j);
                        found = true;
                        continue; // don't allow the iterator to be incremented
                    }
                    ++j;
                } // end while
                if (!found) { 
                    throw runtime_error("could not find excluded test name specified from command line: " + *i);
                }
            } // end for

            // check that there are tests to run
            if (selected.empty()) { 
                throw runtime_error("No tests to run");
            }

            return selected;
        }

        // return false for a duplicated name
        bool isUniqueName(const string & name)
        {
            VectorType::const_iterator i;
            for (i=tests_m.begin(); i!=tests_m.end(); ++i) { 
                ITest::Ptr tmp = *i;
                if (tmp->getName() == name) { 
                    return false;
                }
            }
            return true;
        }

        
        string badName_m;
        VectorType tests_m;
        static auto_ptr<impl> instance_m;
};

auto_ptr<impl> impl::instance_m;

bool TestRegistry::Register(ITest *ptr)
{
    impl * instance = impl::GetInstance();
    return instance->registerTest(ptr);
}

void TestRegistry::Run(const TestSpec & spec)
{
    impl::GetInstance()->runTests(spec);
}


int TestRegistry::GetErrorCount()
{
    return impl::GetInstance()->getErrorCount();
}
