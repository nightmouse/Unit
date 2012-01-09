#ifndef _i_formatter_h_
#define _i_formatter_h_

#include "Harness/src/TestResults.h"
#include <string>

namespace Unit
{

    class IFormatter
    {
        public:
            IFormatter() {}
            virtual ~IFormatter() {}
            virtual std::string getHeader() const = 0;
            virtual std::string formatResult(
                const struct Result & result,
                bool last) const = 0;  // set last to true if the result is the 
                                       // last one to be formatted
            virtual std::string getFooter() const = 0;
    };

} // end namespace Unit

#endif
