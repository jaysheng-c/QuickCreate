#ifndef __JAYSHENG_CMD_PARSER_H__
#define __JAYSHENG_CMD_PARSER_H__

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace jaysheng {

class Command {
public:
    using LIST = std::vector<std::string>;
    using SET = std::unordered_set<std::string>;
    enum Type {
        JAYSHENG_NONE = -1,
        JAYSHENG_PATH = 0,
        JAYSHENG_FILE = 1,
        JAYSHENG_HEADER_FILE = 2,
        JAYSHENG_SOURCE_FILE = 3,
        JAYSHENG_CLASS = 4,
        JAYSHENG_PROJECT = 5
    };

    Command(const std::string &name,
            const std::string &path = "",
            const Type &type = JAYSHENG_NONE);
    virtual ~Command();
    bool exc();
    std::string getName() const { return m_name; }
    std::string getFullName() const { return m_fullName; }
    std::string getPath() const { return m_path; }

    void setName(const std::string &v) { m_name = v; }
    void setPath(const std::string &v) { m_path = v; }

protected:
    void setFullName(const std::string &v) { m_fullName = v; }
    bool isExit();
    bool isExit(std::string &name);
    void openFile(std::fstream &f, const std::string &name = "");
    virtual bool create() = 0;

    template <class T>
    T *delptr(T *&v) {
        if (v != nullptr) {
            delete v;
            v = nullptr;
        }
        return v;
    }

private:
    std::string m_fullName;
    std::string m_name;
    std::string m_path;
    Type m_type;
};

class CppClass : public Command {
public:
    CppClass(const std::string &name,
             const std::string &path = "",
             const Type &type = JAYSHENG_NONE);
    virtual ~CppClass();

    void setInclude(const std::string &v);
    void setInclude(const SET &v);
    void setPackage(const std::string &v);
    void setPackage(const LIST &v);
    void setParent(const std::string &v);
    void setParent(const LIST &v);

protected:
    // bool create() override;

protected:
    LIST m_packages;
    LIST m_parents;
    SET m_includes;
};

class SourceCreate : public CppClass {
public:
    SourceCreate(const std::string &name,
                 const std::string &path = "",
                 const Type &type = JAYSHENG_SOURCE_FILE);

protected:
    bool create() override;

private:
};

class HeaderCreate : public CppClass {
public:
    HeaderCreate(const std::string &name,
                 const std::string &path = "",
                 const Type &type = JAYSHENG_HEADER_FILE);

protected:
    bool create() override;

private:
};

class CMakeListsCreate : public Command {
public:
    CMakeListsCreate(const std::string &libs,
                     const std::string &name = "CMakeLists.txt",
                     const std::string &path = "",
                     const Type &type = JAYSHENG_FILE);

protected:
    bool create() override;

private:
    std::string m_libs;
};

class ClassCreate : public CppClass {
public:
    ClassCreate(const std::string &name,
                const std::string &path = "",
                const Type &type = JAYSHENG_CLASS);
    virtual ~ClassCreate();

protected:
    bool create() override;

private:
    CppClass *m_header;
    CppClass *m_source;
};

class DirCreate : public Command {
public:
    DirCreate(const std::string &name,
              const std::string &path = "",
              const Type &type = JAYSHENG_PATH);
    virtual ~DirCreate();

    std::string getSrc() const { return m_src; }
    std::string getBuild() const { return m_build; }
    std::string getBin() const { return m_bin; }
    std::string getTest() const { return m_test; }
    std::string getLib() const { return m_lib; }

protected:
    bool create() override;

private:
    std::string m_src;
    std::string m_build;
    std::string m_bin;
    std::string m_test;
    std::string m_lib;
};

class ProjectCreate : public Command {
public:
    using TUPLE = std::tuple<LIST, SET, LIST>;
    using CLASS = std::unordered_map<std::string, TUPLE>;
    ProjectCreate(const std::string &name,
                  const std::string &path = "",
                  const Type &type = JAYSHENG_PROJECT);
    virtual ~ProjectCreate();

    void setClass(const std::string &key, const TUPLE &value);
    void setClass(const CLASS &v);
    void setClass(const std::string &key, const LIST &parents, const SET &include, const LIST &packages);

protected:
    bool create() override;

private:
    Command *m_dir;
    CppClass *m_class;
    Command *m_cmake;

    std::string m_libs;
    // LIST m_class_s;
    CLASS m_class_s;
};

} // namespace jaysheng

#endif // !__JAYSHENG_CMD_PARSER_H__

// -project xx -class xxx -pre xxxx -package xxxxx