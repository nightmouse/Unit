#ifndef _test_runner_h_
#define _test_runner_h_

#include "Harness/src/TestSpec.h"

namespace Unit { 

class ITest;

class TestRegistry { 
    public:
        static bool Register(ITest * ptr);
        static void Run(const TestSpec & spec); 
        static int GetErrorCount();
};

} // end namespace

#endif

