#include "../src/CommandParser.h"

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cout << "please use command -help to get help list.\n";
        return 1;
    }
    std::string libs;
    libs = "test.cpp";
    jaysheng::CMakeListsCreate c(libs);
    c.exc();

    return 0;
}
