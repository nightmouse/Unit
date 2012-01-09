#ifndef _json_formatter_h_
#define _json_formatter_h_

#include "Harness/src/IFormatter.h"

namespace Unit { 

    class JsonFormatter: public IFormatter
    {
        public:
            JsonFormatter() { }
            std::string getHeader() const;
            std::string formatResult(const Result & result, bool last) const;
            std::string getFooter() const;
    };

} // end namespace Unit

#endif

