#include "Harness/src/ITest.h"
#include "Harness/src/TestResults.h"
#include "Harness/src/TestContext.h"
#include <iostream>

using namespace std;
using namespace Unit;

void ITest::fail(const string & message)
{
    context_m->fail(message);
}
