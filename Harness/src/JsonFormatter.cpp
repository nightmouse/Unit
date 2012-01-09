#include "Basic/src/DateUtils.h"
#include "Harness/src/JsonFormatter.h"
#include "Harness/src/TestUtils.h"

using namespace std;
using namespace Unit;

string JsonFormatter::getHeader() const
{
    return "{\n\t\"Date\": \"" + GetDate() + "\",\n" + 
           "\t\"Time\": \"" + GetTime() + "\",\n" + 
           "\t\"ChangeSet\": \"" + GetChangeSet() + "\",\n";
}

string JsonFormatter::formatResult(const struct Result & result, bool last) const
{
    string tmp("\t\"Test\": {\n");
    tmp += "\t\t\"Name\": \"" + result.name + "\",\n";
    if (result.pass) { 
        tmp += "\t\t\"Pass\": true\n";
    } else { 
        tmp += "\t\t\"Pass\": false,\n";
        tmp += "\t\t\"Message\": \"" + result.message + "\"\n"; 
    }

    if (last) {  
        return tmp + "\t}\n";
    } else { 
        return tmp + "\t},\n";
    }
}

string JsonFormatter::getFooter() const
{
    return "}";
}
