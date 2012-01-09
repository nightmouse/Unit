// ------------------------------------------------------------------------
// This is a template for creaing a new test.
// 1) Rename the class
// 2) Change the registration name in the constructor
// 3) Implement  the run method inherited from ITest
// 4) Compile and run 'unit <testname>' 
// ------------------------------------------------------------------------

#include "Harness/src/ITest.h"
#include "Harness/src/TestUtils.h"
#include "Harness/src/TestRegistry.h"

using namespace Unit;
using namespace std;

namespace { 

class Template: public ITest
{
    public:
        void run();
        string getName() const { return "<test_name_here>"; }
};

// this is how the test registry becomes aware of the new test
static bool registered = TestRegistry::Register(new Template);

void Template::run()
{
    // Implement this method
    // Use the fail(const string & message) method to fail a test.
    // A test passes automatically when there are no failures.
}

} // end namespace
