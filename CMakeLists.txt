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

set(LIBS src/CommandParser.cpp)
set(MLIBS src/manager.cpp ${LIBS})

# add_executable(QuickCreate test/main.cpp)
# add_executable(cmakeListsCreate test/test_cmakelists_create.cpp ${LIBS})
# add_executable(cppCreate test/test_cpp_create.cpp ${LIBS})
# add_executable(headerCreate test/test_header_create.cpp ${LIBS})
add_executable(classCreate test/test_class_create.cpp ${LIBS})
add_executable(ProjectCreate test/test_project_create.cpp ${LIBS})
add_executable(QuickCreate test/QuickCreate.cpp ${MLIBS})
