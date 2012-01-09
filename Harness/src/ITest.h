#ifndef _unit_test_h_
#define _unit_test_h_

#include <string>
#include "Basic/src/rc_ptr.h"

namespace Unit { 

    class TestContext;

    class ITest
    {
        public:
            typedef rc_ptr<ITest> Ptr;
            ITest() {}
            virtual ~ITest() {}
            virtual void run() = 0;
            virtual std::string getName() const = 0;
            void setContext(const TestContext * context);

        protected:
            void fail(const std::string & message);

        private:
            TestContext * context_m;
    };
}

#endif

