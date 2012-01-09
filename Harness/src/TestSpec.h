#ifndef _test_spec_h_
#define _test_spec_h_

#include <set>
#include <string>
#include <vector>

namespace Unit {
    class TestSpec
    {
        public:

            static TestSpec Create(int argc, char **argv);

            const std::set<std::string> & getTests() const { return include_m; }
            const std::set<std::string> & getExcludedTests() const { return exclude_m; }
            const std::string & getJsonFile() const { return file_m; }

        private:
            // only allow this object to be created through a factory
            TestSpec():
                    include_m(),
                    exclude_m(),
                    file_m() { }

            TestSpec(
                const std::set<std::string> & include,
                const std::set<std::string> & exclude,
                const std::string & file):
                    include_m(include),
                    exclude_m(exclude),
                    file_m(file) { }

            static void showUsage();

            static void parseSingle(
                const std::string & opt,
                const std::string & val,
                std::string & result);

            static void parseMulti(
                const std::string & opt,
                const std::string & val,
                std::set<std::string> & result);

            static void validateTestNames(const std::vector<std::string> & names);

            std::string file_m;
            std::set<std::string> include_m;
            std::set<std::string> exclude_m; 
    };
}

#endif
