#include "Basic/src/DateUtils.h"
#include <ctime>

using namespace std;
using namespace Unit;

namespace { 
    struct tm getNow()
    {
        time_t t = time(NULL);
        struct tm *n = localtime(&t);
        return *n;
    }
}

string Unit::GetDate()
{
    const size_t size = 64;
    const string format("%d/%m/%Y"); // format the current date to dd/mm/yyyy
    struct tm now = getNow();
    char buffer[size];
    strftime(buffer, size, format.c_str(), &now);
    return buffer;
}

string Unit::GetTime()
{
    const size_t size = 64;
    const string format("%k:%M"); // format the current time to military time
    struct tm now = getNow();
    char buffer[size];
    strftime(buffer, size, format.c_str(), &now);
    return buffer;
}


