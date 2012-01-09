#include "Basic/src/StringUtils.h"
#include <iostream>

using namespace std;
using namespace Unit;

vector<string> StringUtils::Split(const string & delim, const string & input)
{
    vector<string> ret;
    const string::size_type delimSize = delim.size();
    const string::size_type inputSize = input.size();
    if (!inputSize) { 
        return ret;
    }

    string::size_type last = 0;
    if (delimSize) { 
        string::size_type pos = input.find(delim, 0);
        while (pos != string::npos) { 
            string tmp = input.substr(last, pos-last);
            ret.push_back(tmp);

            last = pos + delimSize; // add one to move past the delimiter before searching for the next one
            pos = input.find(delim, last);
        }
    }

    string tmp = input.substr(last, inputSize - last);
    ret.push_back(tmp);
    
    return ret;
}

string StringUtils::Join(const string & delim, const vector<string> & input)
{
    string ret;
    if (input.size() == 1) { 
        ret = input[0];
    } else { 
        
        vector<string>::const_iterator i;
        vector<string>::const_iterator last = input.end() - 1;
        for (i = input.begin(); i != input.end(); ++i) { 
            ret += *i;
            if (i != last) { // don't append a delimiter to the string
                ret += delim; 
            }
        }
    }
    return ret;
}

bool StringUtils::BeginsWith(const string & prefix, const string & value)
{
    if (prefix.size() > value.size()) { 
        return false;
    } else if (prefix == value) { 
        return true;
    }

    const string tmp = value.substr(0, prefix.size());
    if (tmp == prefix) { 
        return true;
    }
    return false;
}
