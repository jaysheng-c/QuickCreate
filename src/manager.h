#include "CommandParser.h"

#include <deque>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace jaysheng {

class Mananger {
public:
    using LIST = std::vector<std::string>;
    using SRC_MAP = std::unordered_map<std::string, LIST>; // parent list
    using MAP = std::unordered_map<std::string, SRC_MAP>;  // cmd src_map
    using DEQUE = std::deque<std::string>;

    Mananger(const int argc, const char **argv);
    Mananger(const int argc, const char **argv, const LIST &cmds);
    virtual ~Mananger();

    virtual bool exc();
    void setHelp(const std::string &v) { m_help = v; }
    void setVersion(const std::string &v) { m_version = v; }

protected:
    struct Project {
        using MAP_INT_V = std::unordered_map<size_t, LIST>;
        using TUPLE_V = std::tuple<LIST, LIST>;
        using MAP_INT_TUPE = std::unordered_map<size_t, TUPLE_V>;

        std::string name;
        MAP_INT_V packages;
        MAP_INT_TUPE classes; // package_id  class_list parent_list

        Project(const std::string &v) {
            name = v;
        }

        void print() {
            std::cout << "------------------------\n";
            std::cout << "project: " << name << std::endl;
            for (auto &pair : packages) {
                std::cout << "    namespace: ";
                for (auto &n : pair.second) {
                    std::cout << n << " ";
                }
                std::cout << "{" << std::endl;

                auto it = classes.find(pair.first);
                if (it != classes.end()) {
                    for (auto &c : std::get<0>(it->second)) {
                        std::cout << "        class " << c;
                        for (auto &p : std::get<1>(it->second)) {
                            std::cout << " public " << p << ",";
                        }
                        std::cout << std::endl;
                    }
                }
                std::cout << "}" << std::endl;
            }
            std::cout << "------------------------\n\n";
        }
    };

protected:
    virtual bool parser();
    bool parserSingle(const std::string &cmd);
    bool parser(const std::string &cmd,
                size_t &pos,
                const char skey,
                const char ekey);
    size_t parser(const std::string &cmd,
                  const char endKey,
                  LIST &vec,
                  const size_t pos = 0);
    bool parserPackage(const std::string &cmd,
                       const char &endKey,
                       size_t &pos,
                       std::deque<Project> &projects); // 应该传入一个project的名称list
    bool parserClass(const std::string &cmd,
                     const char &endKey,
                     size_t &pos,
                     std::deque<Project> &projects,
                     const size_t key = 0); // 应该传入一个namespace的id
private:
    void createProject(Project &project);
    void createClass(Project &project);

private:
    ProjectCreate *m_project;
    CppClass *m_class;
    Command *m_cmake;

    std::string m_ss;
    std::string m_path;

    std::deque<Project> m_projects;

    std::string m_help;
    std::string m_version;
};

inline void printVec(const std::string &name, const Mananger::LIST &vec,
                     const std::string tab = "    ") {
    std::cout << "----------------\n"
              << name << std::endl;
    for (auto &v : vec) {
        std::cout << tab << v << std::endl;
    }
    std::cout << "----------------\n";
}

inline void printMap(const Mananger::SRC_MAP &map, const std::string tab = "") {
    for (auto &pair : map) {
        std::string key = tab + "key: " + pair.first + "\nvalue: ";
        printVec(key, pair.second, tab);
    }
}

inline bool judgeCmd(const std::string &input, const std::string &cmd, size_t &startPos) {
    size_t pos = input.find_first_of(' ', startPos);
    if (pos != std::string::npos) {
        std::string key = input.substr(startPos, pos - startPos);
        if (key == cmd) {
            startPos = pos + 1;
            return true;
        }
    }
    return false;
}

} // namespace jaysheng

/*
parser command:
    { }    
    -project xxx
    -class xxx
    -pre xxx    
    -package xxx
    -cmake xxx
    -help / -h   
    -version / -v

eg.
    { -project test -package jaysheng -class child -pre parent1 parent2 }
    { -project test2 -package jaysheng -class child -pre parent1 parent2 }
    会创建两个project分别为 test 和 test2
eg.
    -project test { -package jaysheng -class child -pre parent1 parent2 } \ 
    { -package jaysheng2 -class child2 -pre parent3 parent4 }
    在工程test中创建两个class，他们所在的package和继承parent均不同
*/

/*
   1     :     n
project --> namespace(map<int, vector<string> >) ==> map<project, namespace>

    1      :   n
namespace --> class(vector<string>)  ==> map<namespace_id, class>

  1    :       n
class --> base_class(vector<string>) ==> map<class, base_class>


map<project_name, namespace_id> ==> map<string,int>

map<namespace_id, class_id>     ==
                                   ==> map<int,int>
map<class_id, base_class_id>    ==

namespace, class, base_class ==> map<int,string>
*/