#include "Harness/src/ITest.h"
#include "Harness/src/TestUtils.h"
#include "Harness/src/TestRegistry.h"
#include "Basic/src/StringUtils.h"

#include <string>
#include <vector>

using namespace Unit;
using namespace std;

namespace { 

class StringUtils_Join_Test: public ITest
{
    public:
        void run();
        string getName() const { return "Self/StringUtils/Join"; }
};

static bool registered = TestRegistry::Register(new StringUtils_Join_Test);

void StringUtils_Join_Test::run()
{
    // test if Join handles empty data 
    {
        const string delim = " ";
        vector<string> data;
        string expected;
        string actual = StringUtils::Join(delim, data);
        if (expected != actual) { 
            fail("failed to handle empty data properly");
        }
    }

    // test if Join handles empty delimiters
    {
        const string delim = "";
        const string expected("howdy joe");;
        vector<string> data;
        data.push_back(expected);

        string actual = StringUtils::Join(delim, data);
        if (expected != actual) { 
            fail("failed to handle empty delimiters properly");
        }
    }

    // test Join basic functionality
    {
        const string delim = " ";
        const string expected = "a b c d e f";
        vector<string> data;
        data.push_back("a");
        data.push_back("b");
        data.push_back("c");
        data.push_back("d");
        data.push_back("e");
        data.push_back("f");

        string actual = StringUtils::Join(delim, data);
        if (expected != actual) { 
            fail("basic functionality failed");
        }
    }

    // test if Join handles multi-character delimiters properly
    {
        const string delim = ",,";
        string expected = "a,,b,c,,d,,,,";
        vector<string> data;
        data.push_back("a");
        data.push_back("b,c");
        data.push_back("d");
        data.push_back("");
        data.push_back("");

        string actual = StringUtils::Join(delim, data);
        if (expected != actual) { 
            fail("multi-character delimiters failed");
        }
    }

    // round trip join and split
    {
        const string delim = "=-=";
        vector<string> data;
        data.push_back("one");
        data.push_back("two");
        data.push_back("three");
        data.push_back("four");
        data.push_back("five");
        data.push_back("six");

        vector<string> expected = data;

        for (int i=0; i!=5; ++i) { 
            string joinTmp = StringUtils::Join(delim, data);
            data = StringUtils::Split(delim, joinTmp);
        }

        if (data != expected) { 
            fail("join-split round trip failed.");
        }
    }
}

} // end namespace
