#ifndef _test_context_h_
#define _test_context_h_

#include "Harness/src/ITest.h"

namespace Unit {

    class TestContext
    {
        public:
            explicit TestContext(const ITest::Ptr & test);
            void run();

            void fail(const std::string & message);
            void error(const std::string & message);

        private:
            bool failure_m;
            ITest::Ptr test_m;

    };
}


#endif

