#include "CommandParser.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string.h>

namespace jaysheng {

#define LENGTH 10

char g_help_cmd[] = "-help";
char g_cmake_cmd[][LENGTH] = {"-cmake"};
char g_project_cmd[][LENGTH] = {"-project"};
char g_projects_cmd[][LENGTH] = {"-projects"};
char g_class_cmd[][LENGTH] = {"-class", "-pre", "-package"};
char g_key = '-';

/*---------------------------------------------------------------------------------------------------
            Command
---------------------------------------------------------------------------------------------------*/

Command::Command(const std::string &name,
                 const std::string &path,
                 const Type &type)
    : m_name(name),
      m_path(path),
      m_type(type) {
    m_fullName = "";
}

Command::~Command() {
}

bool Command::exc() {
    if (isExit()) {
        return false;
    }
    bool res = this->create();
    return res;
}

bool Command::isExit() {
    bool res = false;
    switch (m_type) {
    case JAYSHENG_PATH:
        res = isExit(m_name);
        break;
    case JAYSHENG_FILE: {
        std::string name = "";
        if (m_path.empty()) {
            name = m_name;
        } else {
            name = m_path + "/" + m_name;
        }
        res = isExit(name);
        m_fullName = name;
        break;
    }
    case JAYSHENG_HEADER_FILE: {
        std::string name = "";
        name = m_name;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (m_path.empty()) {
            name += ".h";
        } else {
            name = m_path + "/" + name + ".h";
        }
        res = isExit(name);
        m_fullName = name;
        break;
    }
    case JAYSHENG_SOURCE_FILE: {
        std::string name = "";
        name = m_name;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (m_path.empty()) {
            name += ".cpp";
        } else {
            name = m_path + "/" + name + ".cpp";
        }
        res = isExit(name);
        m_fullName = name;
        break;
    }
    case JAYSHENG_CLASS:
    case JAYSHENG_PROJECT:
        std::cout << "type=" << m_type << std::endl;
        break;
    case JAYSHENG_NONE:
    default:
        std::cerr << "unkown type: type=" << m_type << std::endl;
        break;
    }
    return res;
}

bool Command::isExit(std::string &name) {
    std::fstream f;
    f.open(name, std::ios::in);
    if (f) {
        std::cerr << name << " is exit.\n";
        return true;
    }
    return false;
}

void Command::openFile(std::fstream &f, const std::string &name) {
    std::string n;
    if (name.empty()) {
        n = m_fullName;
    } else {
        n = name;
    }

    f.open(n, std::ios::out);
    if (!f) {
        std::cerr << "create file \"" << n << "\" error.\n";
    }
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            CppClass
---------------------------------------------------------------------------------------------------*/

CppClass::CppClass(const std::string &name,
                   const std::string &path,
                   const Type &type)
    : Command(name, path, type) {
}

CppClass::~CppClass() {
}

void CppClass::setInclude(const std::string &v) {
    m_includes.insert(v);
}

void CppClass::setInclude(const SET &v) {
    m_includes.insert(v.begin(), v.end());
}

void CppClass::setPackage(const std::string &v) {
    auto it = std::find(m_packages.begin(), m_packages.end(), v);
    if (it == m_packages.end()) {
        m_packages.push_back(v);
    }
}

void CppClass::setPackage(const LIST &v) {
    if (m_packages.empty()) {
        m_packages = v;
    } else {
        for (auto &i : v) {
            setPackage(i);
        }
    }
}

void CppClass::setParent(const std::string &v) {
    auto it = std::find(m_parents.begin(), m_parents.end(), v);
    if (it == m_parents.end()) {
        m_parents.push_back(v);
    }
}

void CppClass::setParent(const LIST &v) {
    if (m_parents.empty()) {
        m_parents = v;
    } else {
        for (auto &i : v) {
            setParent(i);
        }
    }
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            SourceCreate
---------------------------------------------------------------------------------------------------*/

SourceCreate::SourceCreate(const std::string &name,
                           const std::string &path,
                           const Type &type)
    : CppClass(name, path, type) {
}

bool SourceCreate::create() {
    std::fstream f;
    openFile(f);
    if (f) {
        std::string upper = getName();
        std::string name = getName();
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

        if (!m_includes.empty()) {
            for (auto &i : m_includes) {
                f << "#include " << i << "\n";
            }
            f << "\n";
        }

        if (!m_packages.empty()) {
            for (auto &i : m_packages) {
                f << "namespace " + i + " {\n";
            }
            f << "\n";
        }

        f << "// Construct\n";
        f << name << "::" << name << "() {\n}\n\n";
        f << name << "::" << name << "(const " << name << "& self)  {\n}\n\n";
        f << name << "::" << name << "(const " << name << "&& self)  {\n}\n\n";
        f << "// Destruct\n";
        f << name << "::~" << name << "() {\n}\n\n";

        f << "// Override\n";
        f << "bool " + name + "::operator==(const " + name + "& rhs) {\n    return true;\n}\n\n";
        f << "bool " + name + "::operator!=(const " + name + "& rhs) {\n    return !(*this == rhs);\n}\n\n";
        f << "bool " + name + "::operator<(const " + name + "& rhs) {\n    return true;\n}\n\n";

        for (size_t i = 0; i < m_packages.size(); ++i) {
            f << "}\n";
        }
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            HeaderCreate
---------------------------------------------------------------------------------------------------*/

HeaderCreate::HeaderCreate(const std::string &name,
                           const std::string &path,
                           const Type &type)
    : CppClass(name, path, type) {
}

bool HeaderCreate::create() {
    std::fstream f;
    openFile(f);
    if (f) {
        std::string upper = getName();
        std::string name = upper;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

        f << "#ifndef __" << upper << "_H__\n";
        f << "#define __" << upper << "_H__\n\n";

        for (auto &i : m_includes) {
            f << "#include " << i << "\n";
        }
        if (m_includes.find("<memory>") == m_includes.end()) {
            f << "#include <memory>\n";
        }
        f << "\n";

        if (!m_packages.empty()) {
            for (auto &i : m_packages) {
                f << "namespace " << i << " {\n";
            }
            f << "\n";
        }

        std::string parent("");
        if (!m_parents.empty()) {
            parent = " : ";
            for (auto &i : m_parents) {
                parent += ("public " + i + ", ");
            }
            parent = parent.substr(0, parent.length() - 2);
        }
        f << "class " << name << parent << " {\n";

        f << "public:\n";
        f << "    using ptr = std::shared_ptr<" + name + ">;\n\n";
        f << "    // Construct\n";
        f << "    " + name + "();\n";
        f << "    " + name + "(const " + name + "& self);\n";
        f << "    " + name + "(const " + name + "&& self);\n";
        f << "    // Destruct\n";
        f << "    virtual ~" + name + "();\n\n";

        f << "    // Override\n";
        f << "    bool operator==(const " + name + "& rhs);\n";
        f << "    bool operator!=(const " + name + "& rhs);\n";
        f << "    bool operator<(const " + name + "& rhs);\n\n";

        f << "private:\n\n";

        f << "};\n\n";
        for (size_t i = 0; i < m_packages.size(); ++i) {
            f << "}\n";
        }

        f << "#endif // !__" + upper + "_H__\n";
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            CMakeListsCreate
---------------------------------------------------------------------------------------------------*/

CMakeListsCreate::CMakeListsCreate(const std::string &libs,
                                   const std::string &name,
                                   const std::string &path,
                                   const Type &type)
    : Command(name, path, type),
      m_libs(libs) {
}

bool CMakeListsCreate::create() {
    std::fstream f;
    openFile(f);
    if (f) {
        f << "cmake_minimum_required(VERSION 3.0)\n";
        f << "project(project)\n\n";
        f << "set(PROJECT_ROOT \"${PROJECT_SOURCE_DIR}\")\n";
        f << "set(PROJECT_SOURCE_DIR \"${PROJECT_SOURCE_DIR}/src\")\n";
        f << "set(PROJECT_BINARY_DIR \"${PROJECT_ROOT}/build\")\n";
        f << "set(EXECUTABLE_OUTPUT_PATH \"${PROJECT_ROOT}/bin\")\n";
        f << "set(LIBRARY_OUTPUT_PATH \"${PROJECT_ROOT}/lib\")\n\n";

        f << "set(CMAKE_VERBOSE_MAKEFILE ON)\n";
        f << "set(CMAKE_CXX_FLAGS \"$ENV{CXXFLAGS} -O3 -ggdb -fPIC -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations\")\n";
        f << "set(CMAKE_C_FLAGS \"$ENV{CXXFLAGS} -O3 -ggdb -fPIC -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations\")\n\n\n";

        f << "include_directories(/apps/yoshino/include)\n";
        f << "link_directories(/apps/yoshino/lib)\n";
        f << "link_directories(/apps/yoshino/lib64)\n\n\n";

        if (m_libs.empty()) {
            f << "#set(LIBS_SRC xxx)\n\n\n";
            f << "#add_library(LIBS STATIC ${LIBS_SRC})\n\n\n";
        } else {
            f << "set (LIBS_SRC " + m_libs + ")\n";
            f << "add_library(LIBS STATIC ${LIBS_SRC})\n\n\n";
        }

        if (getPath().empty()) {
            f << "#add_executable(project main.cpp)\n";
            f << "#target_link_libraries(project ${LIBS})\n";
        } else if (m_libs.empty()) {
            f << "add_executable(project test/main.cpp)\n";
            f << "#target_link_libraries(project ${LIBS})\n";
        } else {
            f << "add_executable(project test/main.cpp)\n";
            f << "target_link_libraries(project ${LIBS})\n";
        }

        return true;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            ClassCreate
---------------------------------------------------------------------------------------------------*/
ClassCreate::ClassCreate(const std::string &name,
                         const std::string &path,
                         const Type &type)
    : CppClass(name, path, type),
      m_header(nullptr),
      m_source(nullptr) {
}

ClassCreate::~ClassCreate() {
    delptr(m_header);
    delptr(m_source);
}

bool ClassCreate::create() {
    bool res = false;
    m_header = new HeaderCreate(getName(), getPath());
    m_header->setInclude(m_includes);
    m_header->setParent(m_parents);
    m_header->setPackage(m_packages);
    res = m_header->exc();

    if (!res) {
        // create header file fiald
        return false;
    }

    m_source = new SourceCreate(getName(), getPath());
    m_source->setPackage(m_packages);
    std::string include = getName();
    std::transform(include.begin(), include.end(), include.begin(), ::tolower);
    include = "\"" + include + ".h\"";
    m_source->setInclude(include);
    res = m_source->exc();
    if (res) {
        std::string fullName = m_source->getFullName();
        size_t pos = fullName.find_first_of("/");
        fullName = fullName.substr(pos + 1);
        setFullName(fullName);
    }

    return res;
}
//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            DirCreate
---------------------------------------------------------------------------------------------------*/

DirCreate::DirCreate(const std::string &name,
                     const std::string &path,
                     const Type &type)
    : Command(name, path, type),
      m_src(name + "/src"), m_build(name + "/build"), m_bin(name + "/bin"),
      m_test(name + "/test"), m_lib(name + "/lib") {
}

DirCreate::~DirCreate() {
}

bool DirCreate::create() {
    std::system(std::string("mkdir " + getName()).c_str());
    std::system(std::string("mkdir " + m_src).c_str());
    std::system(std::string("mkdir " + m_build).c_str());
    std::system(std::string("mkdir " + m_bin).c_str());
    std::system(std::string("mkdir " + m_test).c_str());
    std::system(std::string("mkdir " + m_lib).c_str());
    return true;
}

//---------------------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------------------------
            ProjectCreate
---------------------------------------------------------------------------------------------------*/

ProjectCreate::ProjectCreate(const std::string &name,
                             const std::string &path,
                             const Type &type)
    : Command(name, path, type),
      m_dir(nullptr),
      m_class(nullptr),
      m_cmake(nullptr),
      m_libs("") {
}

ProjectCreate::~ProjectCreate() {
    delptr(m_dir);
    delptr(m_class);
    delptr(m_cmake);
}

void ProjectCreate::setClass(const std::string &key, const TUPLE &value) {
    auto it = m_class_s.find(key);
    if (it == m_class_s.end()) {
        m_class_s[key] = value;
    } else {
        it->second = value;
    }
}

void ProjectCreate::setClass(const CLASS &v) {
    for (auto &pair : v) {
        setClass(pair.first, pair.second);
    }
}

void ProjectCreate::setClass(const std::string &key,
                             const LIST &parents,
                             const SET &include,
                             const LIST &packages) {
    TUPLE t(parents, include, packages);
    setClass(key, t);
}

bool ProjectCreate::create() {
    bool res = true;
    std::string project_name = getName();
    // create dir
    m_dir = new DirCreate(project_name, getPath());
    res = m_dir->exc();
    if (!res) {
        return res;
    }
    setPath(project_name);
    // create class
    DirCreate *dir = dynamic_cast<DirCreate *>(m_dir);
    m_class = new ClassCreate("", dir->getSrc());

    for (auto &pair : m_class_s) {
        m_class->setName(pair.first);
        m_class->setParent(std::get<0>(pair.second));
        m_class->setInclude(std::get<1>(pair.second));
        m_class->setPackage(std::get<2>(pair.second));
        res = m_class->exc();
        if (!res) {
            continue;
        }
        m_libs += m_class->getFullName();
        m_libs += " ";
    }

    // create cmakelists
    m_cmake = new CMakeListsCreate(m_libs.substr(0, m_libs.length() - 1),
                                   "CMakeLists.txt", getPath());
    res = m_cmake->exc();
    if (!res) {
        return false;
    }

    std::fstream f;
    std::string mainCpp = dir->getTest() + "/main.cpp";
    openFile(f, mainCpp);
    if (f) {
        f << "#include <iostream>\n\n";
        f << "int main(int argc, char** argv) {\n";
        f << "    std::cout << \"hello my " << project_name << " project.\";\n";
        f << "    return 0;\n}";
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------

// void CmdManager::getHelp() {
//     std::cout << "-p : need create project.\n"
//               << "-c : create C++ class, you can set multi class.\n\teg. \"./QuitCmake -c test1 test2 will create two class.\"\n"
//               << "-pre : set class parent. if set multi parent class, the child will inherit all.\n
//                     eg.\"./QuitCmake -c child -pre parent1 parent2, in \'child.h\'(class child: public parent1, public parent2).\"\n"
//               << "-package : create namespace."
//               << "-v : get QuitCmake version.\n"
//               << "-description : get this executable file discription.\n";
// }

} // namespace jaysheng