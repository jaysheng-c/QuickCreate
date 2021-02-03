#include "manager.h"
#include <algorithm>

namespace jaysheng {

template <class T>
T *delptr(T *&v) {
    if (v != nullptr) {
        delete v;
        v = nullptr;
    }
    return v;
}

char g_splite = ' ';

Mananger::LIST g_commands;

void initCommand() {
    g_commands.push_back("-project");
    g_commands.push_back("-class");
    g_commands.push_back("-pre");
    g_commands.push_back("-package");
    g_commands.push_back("-help");
    g_commands.push_back("-version");
}

Mananger::Mananger(const int argc, const char **argv)
    : m_project(nullptr),
      m_class(nullptr),
      m_cmake(nullptr),
      m_path(""),
      m_help(""),
      m_version("") {
    for (int i = 1; i < argc; ++i) {
        m_ss += argv[i];
        m_ss += g_splite;
    }

    initCommand();
    // SRC_MAP empty;
    // for (auto &cmd : g_commands) {
    //     m_commands[cmd] = empty;
    // }
}

Mananger::Mananger(const int argc, const char **argv, const LIST &cmds)
    : m_project(nullptr),
      m_class(nullptr),
      m_cmake(nullptr),
      m_path(""),
      m_help(""),
      m_version("") {
    for (int i = 1; i < argc; ++i) {
        // ss << argv[i] << g_splite;
        m_ss += argv[i];
        m_ss += g_splite;
    }
    g_commands = cmds;
}

Mananger::~Mananger() {
    delptr(m_project);
    delptr(m_class);
    delptr(m_cmake);
}

bool Mananger::exc() {
    bool res = parserSingle(m_ss);
    // bool res = parser();
    if (!res) {
        return res;
    }

    while (!m_projects.empty()) {
        auto project = m_projects.front();
        m_projects.pop_front();
        if (!project.name.empty()) {
            createProject(project);
        } else {
            createClass(project);
        }
    }

    return res;
}

bool Mananger::parser() {
    // int block = 0;
    std::string target("");
    size_t pos = 0;

    if (m_ss.find("-help") == std::string::npos ||
        m_ss.find("-h") == std::string::npos) {
        // 输出help
        std::cout << m_help << std::endl;
        return false;
    }
    if (m_ss.find("-version") == std::string::npos ||
        m_ss.find("-v") == std::string::npos) {
        // 输出version
        std::cout << m_version << std::endl;
        return false;
    }

    while (pos < m_ss.length()) {
        size_t temp = pos;
        if (!parser(m_ss, pos, '{', '}')) {
            return false;
        }
        if (pos == temp) {
            // 没有括号
        }
    }

    return true;
}

bool Mananger::parserSingle(const std::string &cmd) {
    if (cmd.find("-help") != std::string::npos ||
        cmd.find("-h") != std::string::npos) {
        // 输出help
        std::cout << m_help << std::endl;
        return false;
    }
    if (cmd.find("-version") != std::string::npos ||
        cmd.find("-v") != std::string::npos) {
        // 输出version
        std::cout << m_version << std::endl;
        return false;
    }

    // -project x -class xx1 xx2 -pre xxx1 xxx2 -package xxxx1 xxxx2
    size_t start = 0;
    size_t pos = start;
    std::string key;

    LIST list;
    std::deque<Project> projects;
    while (pos < cmd.length()) {
        if (cmd[pos] == '-') {
            size_t pos2 = cmd.find_first_of(' ', pos);
            if (pos2 != std::string::npos) {
                key = cmd.substr(pos, pos2 - pos);
                // std::cout << "key: " << key << std::endl;
                // 查找指令是否存在
                auto it = std::find(g_commands.begin(), g_commands.end(), key);
                if (it == g_commands.end()) {
                    std::cerr << "Can not find command: " << key
                              << ".\nPlease use -help or -h to get command list." << std::endl;
                    return false;
                }

                if (key == "-project") {
                    pos2 = parser(cmd, '-', list, pos2 + 1);
                    // printVec("-project", list);
                    for (auto &name : list) {
                        Project p(name);
                        projects.push_back(p);
                    }
                } else if (key == "-package") {
                    pos2++;
                    std::cout << "-package\n";
                    parserPackage(cmd, '-', pos2, projects);
                } else if (key == "-class") {
                    pos2++;
                    parserClass(cmd, '-', pos2, projects);
                }
                pos = pos2;
                continue;
            }
        }
        ++pos;
    }
    // for (auto &p : projects) {
    //     p.print();
    // }
    // std::cout << "projects size= " << projects.size() << std::endl;
    m_projects.insert(m_projects.end(), projects.begin(), projects.end());

    return true;
}

bool Mananger::parser(const std::string &cmd,
                      size_t &pos,
                      const char skey,
                      const char ekey) {
    int block = 0;
    // 通过 '{' 找到区块
    // pos定位到 '}' 的下一位置
    if (cmd[pos] == skey) {
        size_t start = pos++;
        ++block;
        while (block) {
            if (pos == cmd.length()) {
                std::cerr << "Error to maching enough \'}\'\n";
                return false;
            }
            if (cmd[pos++] == skey) {
                ++block;
            }
            if (cmd[pos++] == ekey) {
                --block;
            }
        }
        std::string temp = cmd.substr(start, pos);
        std::string key = temp.substr(2, temp.length()); // 跳过 '{ ' 的空格
        key = key.substr(0, key.find(g_splite));
        // auto it = m_commands.find(key);
        // if (it != m_commands.end()) {
        //     auto it2 = it->second.find(m_path);
        //     if (it2 == it->second.end()) {
        //         LIST v(1, temp);
        //         it->second[m_path] = v;
        //     } else {
        //         it2->second.push_back(temp);
        //     }
        // } else {
        //     std::cerr << "ERROR : can not find command = " << key << std::endl;
        // }
    }

    return true;
}

size_t Mananger::parser(const std::string &cmd,
                        const char endKey,
                        LIST &vec,
                        const size_t pos) {
    size_t endPos = pos;
    while (endPos < cmd.length() &&
           cmd[endPos] != endKey) {
        size_t pos2 = cmd.find_first_of(' ', endPos);
        if (pos2 != std::string::npos) {
            std::string target = cmd.substr(endPos, pos2 - endPos);
            vec.push_back(target);
            endPos = pos2 + 1;
        }
    }
    return endPos;
}

bool Mananger::parserPackage(const std::string &cmd,
                             const char &endKey,
                             size_t &pos,
                             std::deque<Project> &projects) {
    LIST package;
    while (pos < cmd.length()) {
        if (cmd[pos] == endKey) {
            // 保存package
            size_t key = 0;
            if (!package.empty()) {

                if (projects.empty()) {
                    Project project("");
                    key = 1;
                    project.packages[key] = package;
                    projects.push_back(project);
                } else {
                    for (auto &p : projects) {
                        key = p.packages.size() + 1;
                        p.packages[key] = package;
                    }
                }
            } else {
                // std::cout << "package.empty()" << package.empty() << std::endl;
            }

            // 解析class
            if (judgeCmd(cmd, "-class", pos)) {
                // printVec("-package", package);
                return parserClass(cmd, '-', pos, projects, key);
            }
            break;
        }
        size_t pos2 = cmd.find_first_of(' ', pos);
        if (pos2 != std::string::npos) {
            std::string target = cmd.substr(pos, pos2 - pos);
            package.push_back(target);
            pos = pos2 + 1;
        }
    }
    // printf error
    // printVec("-package", package);
    std::cerr << "Analyze error. Can not find class in package.\n";
    return false;
}

bool Mananger::parserClass(const std::string &cmd,
                           const char &endKey,
                           size_t &pos,
                           std::deque<Project> &projects,
                           const size_t key) {
    bool res = false;
    LIST parent;
    SRC_MAP map;
    LIST empty;
    LIST classes;
    while (pos < cmd.length()) {
        if (cmd[pos] == '-') {
            // 解析 parent
            if (judgeCmd(cmd, "-pre", pos)) {
                while (pos < cmd.length()) {
                    size_t pos2 = cmd.find_first_of(' ', pos);
                    if (pos2 != std::string::npos) {
                        std::string target = cmd.substr(pos, pos2 - pos);
                        parent.push_back(target);
                        pos = pos2 + 1;
                    }
                }
                if (!parent.empty()) {
                    for (auto &pair : map) {
                        pair.second = parent;
                    }
                }
            }
        }
        size_t pos2 = cmd.find_first_of(' ', pos);
        if (pos2 != std::string::npos) {
            res = true;
            std::string target = cmd.substr(pos, pos2 - pos);
            classes.push_back(target);
            if (map.find(target) == map.end()) {
                map[target] = empty;
            }
            pos = pos2 + 1;
        }
    }
    for (auto &p : projects) {
        Project::TUPLE_V t(classes, parent);
        auto it = p.classes.find(key);
        if (it == p.classes.end()) {
            p.classes[key] = t;
        } else {
            auto &c = std::get<0>(it->second);
            c.insert(c.end(), classes.begin(), classes.end());
            auto &p = std::get<1>(it->second);
            p.insert(p.end(), parent.begin(), parent.end());
        }
    }
    // printMap(map);
    return res;
}
int i = 0;
void Mananger::createProject(Project &project) {
    // std::cout << "line: " << __LINE__ << std::endl;
    // project.print();
    // std::cout << "\n\n\n";
    if (!m_project) {
        m_project = new ProjectCreate(project.name);
    } else {
        m_project->setName(project.name);
    }

    for (auto &pair : project.packages) {
        ProjectCreate::SET include(0);
        auto &package = pair.second;
        auto it = project.classes.find(pair.first);
        if (it != project.classes.end()) {
            for (auto &c : std::get<0>(it->second)) {
                auto &parent = std::get<1>(it->second);
                for (auto &p : parent) {
                    std::string temp = "\"" + p + ".h\"";
                    include.insert(temp);
                }
                m_project->setClass(c, parent, include, package);
            }
        }
    }
    m_project->exc();
}

void Mananger::createClass(Project &project) {
    // std::cout << "line: " << __LINE__ << std::endl;
    // project.print();

    for (auto &pair : project.packages) {
        ProjectCreate::SET include(0);
        auto &package = pair.second;
        auto it = project.classes.find(pair.first);
        if (it != project.classes.end()) {
            for (auto &c : std::get<0>(it->second)) {
                if (!m_class) {
                    m_class = new ClassCreate(c);
                } else {
                    m_class->setName(c);
                }
                auto &parent = std::get<1>(it->second);
                for (auto &p : parent) {
                    std::string temp = "\"" + p + ".h\"";
                    include.insert(temp);
                }
                m_class->setInclude(include);
                m_class->setParent(parent);
                m_class->setPackage(package);
                m_class->exc();
            }
        }
    }
}

} // namespace jaysheng