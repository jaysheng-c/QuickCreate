cmake_minimum_required(VERSION 3.0)
project(QuickCreate)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(/apps/yoshino/include)
link_directories(/apps/yoshino/lib)
link_directories(/apps/yoshino/lib64)


set(ROOT "${PROJECT_SOURCE_DIR}")
set(PROJECT_BINARY_DIR "${ROOT}/build")
set(LIBRARY_OUTPUT_PATH "${ROOT}/lib")
set(EXECUTABLE_OUTPUT_PATH "${ROOT}/bin")


add_executable(QuickCreate test/main.cpp)
