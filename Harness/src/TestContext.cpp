#include "Harness/src/TestContext.h"
#include "Harness/src/TestResults.h"
#include <iostream>

using namespace std;
using namespace Unit;


TestContext::TestContext(const ITest::Ptr & test):
    test_m(test),
    failure_m(false)
{
}


void TestContext::run()
{
    try { 
        test_m->run();
    } catch(const exception & e) { 
        error(e.what());
    } catch(...) { 
        error("caught unknown exception");
    }

    if (!failure_m) { 
        TestResults * ptr = TestResults::GetInstance();
        ptr->addPassResult(test_m->getName());
        cout << "[PASS] [" << test_m->getName() << "] " << endl;
    }
}

void TestContext::error(const string & message)
{
    failure_m = true;
    TestResults * ptr = TestResults::GetInstance();
    ptr->addFailResult(test_m->getName(), message);
    cout << "[ERROR] [" << test_m->getName() << "] " << message << endl;
}


void TestContext::fail(const std::string & message)
{
    failure_m = true;
    TestResults * ptr = TestResults::GetInstance();
    ptr->addFailResult(test_m->getName(), message);
    cout << "[FAIL] [" << test_m->getName() << "] " << message << endl;
}
