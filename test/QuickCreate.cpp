#include "../src/manager.h"

#include <sstream>

class CmdHelp {
public:
    CmdHelp() {
        m_version = "1.0";
        m_ss << "-project : create project.\n"
             << "-package : create namespace.\n"
             << "-class create C++ class.\n"
             << "-pre : set class parent. if set multi parent class, the child will inherit all.\n"
             << "-v/-version : get version.\n"
             << "    eg. \"-project test_project1 test_project2 -package namespace1 namespace2 "
             << "-class class1 class2 -pre parent1 parent2\" will create. \n"
             << "    test_project1 and test_project2\n    |---build\n    |---bin\n    |---lib\n    |---test\n    |---src\n"
             << "         |---class1.h\n         |---class1.cpp\n         |---class2.h\n         |---class2.cpp\n\n"
             << "in class.h\n"
             << "    namespace namespace1 {\n    namespace namespace2 {\n    class class1 : public parent1, parent2 {    \n    ...\n    };\n    }\n    }";
    }

    CmdHelp(const CmdHelp &self) {
        this->m_version = self.getVersion();
        this->m_ss << self.toString();
    }

    std::string toString() const { return m_ss.str(); }
    std::string getVersion() const { return m_version; }

private:
    std::stringstream m_ss;
    std::string m_version;
};

static CmdHelp getHelp() {
    static CmdHelp help;
    return help;
}

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cout << "please use command -help to get help list.\n";
        return 1;
    }
    jaysheng::Mananger mgr(argc, argv);
    mgr.setHelp(getHelp().toString());
    mgr.setVersion(getHelp().getVersion());
    mgr.exc();

    return 0;
}
