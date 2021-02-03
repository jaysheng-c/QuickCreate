#include "../src/CommandParser.h"

#include <sstream>

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cout << "please use command -help to get help list.\n";
        return 1;
    }
    // jaysheng::CmdManager mgr(argc, argv);
    jaysheng::ProjectCreate c(argv[1]);

    jaysheng::ProjectCreate::LIST parent;
    parent.push_back("123");

    jaysheng::ProjectCreate::SET include;
    include.insert("<iostream>");
    include.insert("<fstream>");
    include.insert("<unordered_set>");

    jaysheng::ProjectCreate::LIST packages;
    packages.push_back("jaysheng");
    packages.push_back("pTest");

    c.setClass("MyClass", parent, include, packages);
    c.exc();

    return 0;
}
