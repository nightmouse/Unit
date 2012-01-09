#include "Harness/src/TestUtils.h"

using namespace std;
using namespace Unit;

// GIT_CHANGESET must be defined for this to work
#ifndef GIT_CHANGESET
#define GIT_CHANGESET "UNDEFINED"
#endif

string Unit::GetChangeSet()
{
    return GIT_CHANGESET;
}
