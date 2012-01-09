#ifndef _test_results_h_
#define _test_results_h_

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace Unit
{

class IFormatter;

struct Result
{ 
    std::string name;
    bool pass;
    std::string message;
    Result(const std::string & n, bool p, std::string m = ""):
        name(n), pass(p), message(m)
    { }
};
typedef std::vector<struct Result> ResultType;

// implement a singleton object to get/set test results
class TestResults
{
    public:
        static TestResults * GetInstance();
        void addPassResult(const std::string & name);
        void addFailResult(
            const std::string & name,
            const std::string & message);

        void getResults(IFormatter * formatter, std::string & results) const;
        int getErrorCount() const { return errorCount_m; }
        

    private: 
        TestResults();
        static std::auto_ptr<TestResults> instance_m;
        ResultType results_m;
        int errorCount_m;
};

} // end namespace


#endif
