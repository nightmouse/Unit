#ifndef _unit_string_utils_h_
#define _unit_string_utils_h_

#include <string>
#include <vector>
#include <sstream>

namespace Unit {

    namespace StringUtils {  

        std::vector<std::string> Split(
            const std::string & delim,
            const std::string & input);

        std::string Join(
            const std::string & delim,
            const std::vector<std::string> & input);

        template <typename T>
        std::string ToString(const T & value) 
        { 
            std::stringstream tmp;
            tmp << value;
            return tmp.str();
        }

        bool BeginsWith(const std::string & prefix, const std::string & value);


    } // end namespace StringUtils;
    
} // end namespace Unit


#endif
