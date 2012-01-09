#include "Harness/src/TestResults.h"
#include "Harness/src/IFormatter.h"

using namespace std;
using namespace Unit;

auto_ptr<TestResults> TestResults::instance_m;

TestResults * TestResults::GetInstance()
{
    if (!instance_m.get()) { 
        instance_m.reset(new TestResults);
    }
    return instance_m.get();
}

TestResults::TestResults():
    results_m(),
    errorCount_m(0)
{ }


void TestResults::getResults(IFormatter * formatter, string & results) const
{
    results.clear();
    results += formatter->getHeader();

    ResultType::const_iterator i;
    for (i=results_m.begin(); i!=results_m.end(); ++i) {
        Result tmp = *i;
        bool last = (i+1 == results_m.end());
        results += formatter->formatResult(tmp, last); 
    }
    results += formatter->getFooter();
}

void TestResults::addPassResult(const string & name)
{
    results_m.push_back( Result(name, true, "") ); 
}

void TestResults::addFailResult(const string & name, const string & message)
{
    ++errorCount_m;
    results_m.push_back( Result(name, false, message) ); 
}

