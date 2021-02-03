#include "../src/CommandParser.h"

#include <sstream>

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cout << "please use command -help to get help list.\n";
        return 1;
    }
    // jaysheng::CmdManager mgr(argc, argv);
    jaysheng::HeaderCreate c(argv[1]);
    std::stringstream ss;
    ss << "<iostream>";
    c.setInclude(ss.str());
    std::string pa = "jaysheng";
    c.setPackage(pa);
    c.exc();

    return 0;
}
