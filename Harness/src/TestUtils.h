// ------------------------------------------------------------------
// MISC funcitons for testing
// ------------------------------------------------------------------

#ifndef _unit_util_h_
#define _unit_util_h_

#include <string>

namespace Unit {
    #define BEGIN_EXPECTED_EXCEPTION_CHECK(reason)\
    {\
        bool _thrown_ = false;\
        const std::string _reason_((reason));\
        try {


    #define END_EXPECTED_EXCEPTION_CHECK()\
    } catch(...) { _thrown_ = true; }\
    if (!_thrown_) { fail(_reason_); }\
    }

    std::string GetChangeSet();
}

#endif
