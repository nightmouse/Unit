#include "Harness/src/TestSpec.h"
#include "Basic/src/StringUtils.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace Unit;

namespace { 
    set<string> makeSet(const vector<string> & val)
    {
        set<string> ret;
        vector<string>::const_iterator i;
        for (i=val.begin(); i!=val.end(); ++i) { 
            ret.insert(*i);
        }
        return ret; 
    }
}

void TestSpec::validateTestNames(const vector<string> & names)
{
    if (!names.size()) { 
        cerr << "no test name specified" << endl;
        showUsage();
    }

    vector<string>::const_iterator i;
    for (i=names.begin(); i!=names.end(); ++i) { 
        if (!i->size()) { 
            cerr << "empty test name specified" << endl;
            showUsage();
        }
    }
}

void TestSpec::parseSingle(const string & opt, const string & val, string & result)
{
    vector<string> parts = StringUtils::Split("=", val);
    if (parts.size() != 2 || parts[0] != opt) {  
        cerr << "Invalid command line option: [" + val + "]" << endl;
        showUsage();
    }
    result = parts[1];
}

void TestSpec::parseMulti(const string & opt, const string &val, set<string> & result)
{
    vector<string> parts = StringUtils::Split("=", val);
    if (parts.size() != 2 || parts[0] != opt) {  
        cerr << "Invalid command line option: [" + val + "]" << endl;
        showUsage();
    }

    // extract the comma delimited test names
    vector<string> tests = StringUtils::Split(",", parts[1]);
    validateTestNames(tests); // control does not return if one of the names is "bad"
    result = makeSet(tests);
}

TestSpec TestSpec::Create(int argc, char **argv)
{
    if (argc == 1) { // no command line args, run everything, don't save to file
        return TestSpec();
    }

    // values we need to know about
    set<string> include;
    set<string> exclude;
    string file;

    // convert all the command line arguments into a vector of strings
    vector<string> args;
    for (int i=0; i!=argc; ++i) { 
        args.push_back( string(argv[i]) );
    }

    vector<string>::const_iterator i; 

    // add +1 to the beginning iterator to move past the file name
    for (i=args.begin() +1 ; i!=args.end(); ++i) { 
       
        if (StringUtils::BeginsWith("--run", *i)) {   // parse --run option
            parseMulti("--run", *i, include);
        } else if (StringUtils::BeginsWith("--exclude", *i)) {  // parse --exclude option
            parseMulti("--exclude", *i, exclude);
        } else if (StringUtils::BeginsWith("--json", *i)) {  // parse --json option
            parseSingle("--json", *i, file);
        } else if (*i == "--help") { 
            showUsage();
        } else { 
            cerr << "Invalid option [" << *i << "]" << endl;
            showUsage();
        }
    } // end for

    return TestSpec(include, exclude, file);
}

void TestSpec::showUsage()
{
    cerr << "Usage:" << endl;
    cerr << "Valid command line options: " << endl;
    cerr << "--help:\n\t Display this help" << endl;
    cerr << "--run=test1,test2,...:\n\tspecify which tests to run" << endl;
    cerr << "--exclude=test1,test2...:\n\nspecify which tests not to run" << endl << endl;
    cerr << "--json=file_name\n\tspecify a file to store the results in" << endl << endl;
    cerr << "Note: test names are evaluated as such:" << endl;
    cerr << "- Given several tests registered under 'Self', specifying" << endl;
    cerr << "--run=Self on the command line will cause only those test to run." << endl;

    exit(-1);
}
