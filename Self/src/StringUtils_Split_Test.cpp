#include "Harness/src/ITest.h"
#include "Harness/src/TestUtils.h"
#include "Harness/src/TestRegistry.h"
#include "Basic/src/StringUtils.h"

#include <string>
#include <vector>

using namespace Unit;
using namespace std;

namespace { 

class StringUtils_Split_Test: public ITest
{
    public:
        void run();
        string getName() const { return "Self/StringUtils/Split"; }
};

static bool registered = TestRegistry::Register(new StringUtils_Split_Test);

void StringUtils_Split_Test::run()
{
    // test if Split handles empty data 
    {
        const string delim = " ";
        const string data = "";
        vector<string> expected;
        vector<string> actual = StringUtils::Split(delim, data);
        if (expected != actual) { 
            fail("failed to handle empty data properly");
        }
    }

    // test if Split handles empty delimiters
    {
        const string delim = "";
        const string data = "howdy joe";
        vector<string> expected;
        expected.push_back(data);
        vector<string> actual = StringUtils::Split(delim, data);
        if (expected != actual) { 
            fail("failed to handle empty delimiters properly");
        }
    }

    // test Split basic functionality
    {
        const string delim = " ";
        const string data = "a b c d e f";
        vector<string> expected;
        expected.push_back("a");
        expected.push_back("b");
        expected.push_back("c");
        expected.push_back("d");
        expected.push_back("e");
        expected.push_back("f");

        vector<string> actual = StringUtils::Split(delim, data);
        if (expected != actual) { 
            fail("basic functionality failed");
        }
    }

    // test if Split handles multi-character delimiters properly
    {
        const string delim = ",,";
        const string data = "a,,b,c,,d,,,,";
        vector<string> expected;
        expected.push_back("a");
        expected.push_back("b,c");
        expected.push_back("d");
        expected.push_back("");
        expected.push_back("");

        vector<string> actual = StringUtils::Split(delim, data);
        if (expected != actual) { 
            fail("multi-character delimiters failed");
        }
    }

}

} // end namespace
