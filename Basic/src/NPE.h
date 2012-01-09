#ifndef _null_pointer_exception_h_
#define _null_pointer_exception_h_

#include <stdexcept>
#include <string>

namespace Unit
{

class NullPointerException: public std::runtime_error
{
    public: 
        NullPointerException() throw(): 
            std::runtime_error("")
        { }
};

} // end namespace

#endif
