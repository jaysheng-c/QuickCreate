/*
 * @Author: Jaysheng
 * @Date: 2021-01-16 22:40:05
 * @LastEditTime: 2021-01-18 23:06:15
 * @LastEditors: Please set LastEditors
 * @Description: version 1.0 快速创建一个简单的cmake工程
 *                       1.1 添加C++类的创建功能
 * @FilePath: /root/workspace/quitCreate/main.cpp
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>

std::string g_cmake_file = "/CMakeLists.txt";
std::string g_main_file = "/src/main.cpp";
std::string g_path = "";

bool create_file(int argc, const char** argv);
bool create_cmake_lists();
bool create_main_cpp();
bool create_cpp_class(std::stringstream& ss);
bool create_header(const std::string& package, const std::string& name, const std::string& parents);
bool create_cpp(const std::string& package, const std::string& name);

std::string VERSION = "1.1";
std::string DESCRIP = 
"This program provides users a way to quickly create a simple CMake project, \
and also can quickly generate some default C++ class.";

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cout << "please use command -h to get help list.\n";
        return 1;
    }
    if(!strcmp(argv[1], "-h")) {
        std::cout << "-p : need create project.\n"
                << "-c : create C++ class, you can set multi class.\n\teg. \"./QuitCmake -c test1 test2 will create two class.\"\n"
                << "-pre : set class parent. if set multi parent class, the child will inherit all.\n     \
                    eg.\"./QuitCmake -c child -pre parent1 parent2, in \'child.h\'(class child: public parent1, public parent2).\"\n"
                << "-package : create namespace."
                << "-v : get QuitCmake version.\n"
                << "-description : get this executable file discription.\n";      
        return 0;
    }
    if(!strcmp(argv[1], "-description")) {
        std::cout << DESCRIP << std::endl;
        return 0;
    }
    if(!create_file(argc, argv)) {
        std::cerr << "create project error. \nyou can use command -h to get help list.\n";
    }
    return 0;
}

const char splite = '\t';

bool create_file(int argc, const char** argv) {
    std::fstream f;
    std::stringstream ss;

    std::string target("");

    for(int i = 1; i < argc; ++i) {
        ss << argv[i];
        ss << splite;
    }

    while(std::getline(ss, target, splite)) {
        if(target == "-v") {
            std::cout << "QuitCmake VERSION " << VERSION << std::endl;
            return true;
        }
        if(target == "-p") {
            std::getline(ss, target, splite);
            if(target.empty()) {
                std::cout << "parmater is null. please set parmater.\n";
                return false;
            }
            f.open(target, std::ios::in);
            if(!f) {
                std::cout << "create file.\n";
                std::system(std::string("mkdir " + target).c_str());
                std::system(std::string("mkdir " + target + "/bin").c_str());
                std::system(std::string("mkdir " + target + "/src").c_str());
                std::system(std::string("mkdir " + target + "/build").c_str());
                std::system(std::string("mkdir " + target + "/lib").c_str());
                std::system(std::string("mkdir " + target + "/test").c_str());
                g_path = target;
                bool flag = create_main_cpp();
                if(flag) {
                    flag = create_cmake_lists();
                }
                return flag;
            }
            else {
                std::cerr << target << " has exits!\n";
            }
        }
        if(target == "-c") {
            // std::cout << "create_cpp_class\n";
            return create_cpp_class(ss);
        }
    }
    return false;
}

bool create_cmake_lists() {
    std::fstream f;
    f.open(g_path + g_cmake_file, std::ios::out);
    if(f) {
        f << "cmake_minimum_required(VERSION 3.0)\n";
        f << "project(" + g_path +")\n\n";
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

        f << "#set(LIBS xxx)\n\n\n";

        f << "add_executable(" + g_path + " src/main.cpp)\n";

        f << "#target_link_libraries(" + g_path + " ${LIBS})\n";
    }
    else {
        std::cout << "create file: " << g_path + g_cmake_file << " error.\n";
        return false;
    }
    return true;
}

bool create_main_cpp() {
    std::fstream f;
    f.open(g_path + g_main_file, std::ios::out);
    if(f) {
        f << "#include <iostream>\n\n";
        f << "int main(int argc, char** argv) {\n";
        f << "    std::cout << \"Hello CMake Project.\" <<std::endl;\n";
        f << "    return 0;\n}";
    }
    else {
        std::cout << "create file: " << g_path + g_main_file << " error.\n";
        return false;
    }
    return true;
}


std::string get_parent_class(std::stringstream& ss, std::vector<std::string>& vec) {
    std::string target("");
    while(std::getline(ss, target, splite)) {
        if((int)target.find_first_of('-') == -1) {
            vec.push_back(target);
        }
        else {
            break;
        }
    }
    return target;
}

bool create_cpp_class(std::stringstream& ss) {
    std::vector<std::string> names;
    std::vector<std::string> parents;
    std::string target("");
    std::string space("");
    while(std::getline(ss, target, splite)) {
        // std::cout << target << std::endl;
        if(target == "-pre") {
           target = get_parent_class(ss, parents);
        }
        if(target == "-package") {
            std::getline(ss, space, splite);
            target = "";
        }
        if(!target.empty() && target != "-pre" && target != "-package") {
            names.push_back(target);
        }
    }
    if(names.empty()) {
        std::cerr << "not find class name. please set class after command.\n";
        return false;
    }

    for(auto n : names) {
        std::string content("");
        for(auto p : parents) {
            content += std::string("public " + p + ", ");
        }
        if(create_header(space, n, content.substr(0, content.length()-2))) {
            std::cout << "create header file : " + n + ".h successful.\n" ;
        }
        if(create_cpp(space, n)) {
            std::cout << "create source file : " + n + ".cpp successful.\n" ;
        }
    }
    return true;
}

bool create_header(const std::string& package, const std::string& name, const std::string& parents) {
    std::fstream f;
    std::string file_name = name;
    std::transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);
    f.open(file_name + ".h", std::ios::in);
    if(!f) {
        // do something
        f.open(file_name + ".h", std::ios::out);
        std::string header("");
        std::string last("");
        std::string Tab("");
        std::string upper = name;

        if(!package.empty()) {
            header = "namespace " + package + "{\n\n";
            last = "\n\n}\n";
            Tab = "\t";
            upper = package + "_" + upper;
        }
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

        f << "#ifndef __" + upper + "_H__\n";
        f << "#define __" + upper + "_H__\n\n";
        f << "#include <iostream>\n\n";
        f << header;

        if(parents.empty()) {
            f << Tab + "class " + name + parents + " {\n";
        }
        else {
            f << Tab + "class " + name + " : "+ parents + " {\n";
        }
        
        f << Tab + "public:\n";
        
        f << Tab + "    // 构造\n"; 
        f << Tab + "    " + name + "();\n";
        f << Tab + "    " + name + "(const " + name + "& " + file_name + ");\n";
        f << Tab + "    " + name + "(const " + name + "&& " + file_name + ");\n";
        f << Tab + "    virtual ~" + name + "();\n\n";
        f << Tab + "    // 重载\n";
        f << Tab + "    bool operator==(const " + name + "& rhs);\n";
        f << Tab + "    bool operator!=(const " + name + "& rhs);\n";
        f << Tab + "    bool operator<(const " + name + "& rhs);\n";

        f << "\n";
        f << Tab + "private:\n\n";
        f << Tab + "};\n";

        f << last;
        f << "#endif // !__" + upper + "_H__";
        return true;
    }
    else {
        std::cerr << file_name << ".h has exits!\n";
    }
    return false;
}

bool create_cpp(const std::string& package, const std::string& name) {
    std::fstream f;
    std::string file_name = name;
    std::transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);
    f.open(file_name + ".cpp", std::ios::in);
    if(!f) {
        // do something
        f.open(file_name + ".cpp", std::ios::out);
        std::string header("");
        std::string last("");
        std::string Tab("");
        if(!package.empty()) {
            header = "namespace " + package + "{\n\n";
            last = "\n\n}\n";
            Tab = "\t";
        }
        f << "#include \"" + file_name + ".h\"\n\n";
        f << header;

        f << Tab + "// 构造\n";
        f << Tab + name + "::" + name + "(){\n" + Tab + "}\n\n";
        f << Tab + name + "::" + name + "(const " + name + "&" + file_name + ") {\n" + Tab + "}\n\n";
        f << Tab + name + "::" + name + "(const " + name + "&&" + file_name + ") {\n" + Tab + "}\n\n";
        f << Tab + "// 重载\n";
        f << Tab + "bool " + name + "::operator==(const " + name + "& rhs) {\n" + Tab + "    return true;\n" + Tab + "}\n\n";
        f << Tab + "bool " + name + "::operator!=(const " + name + "& rhs) {\n" + Tab + "    return !(*this==rhs);\n" + Tab + "}\n\n";
        f << Tab + "bool " + name + "::operator<(const " + name + "& rhs) {\n" + Tab + "    return true;\n" + Tab + "}\n";
        
        f << last;
        return true;
    }
    else {
        std::cerr << file_name << ".cpp has exits!\n";
    }
    return false;
}






