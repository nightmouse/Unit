#include "Harness/src/TestRegistry.h"
#include "Harness/src/TestSpec.h"
#include <iostream>

using namespace std;
using namespace Unit;

int main(int argc, char **argv)
{
    int ret = 0;
    try { 
        TestSpec spec = TestSpec::Create(argc, argv);
        TestRegistry::Run(spec);
        int count = TestRegistry::GetErrorCount();
        if(count) { 
            ret = 1;
        } 
        cout << count << " errors." << endl;
    } catch(const exception & e) { 
        cerr << "Error: " << e.what() << endl;
        ret = 1;
    } catch(...) { 
        cerr << "Caught unknown exception" << endl;
        ret = 1;
    }

    return ret;
}
