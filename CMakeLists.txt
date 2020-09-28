cmake_minimum_required(VERSION 3.0.0)
project(Graph1 VERSION 0.1.0)

include(CTest)
enable_testing()
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/Src/*.h)
add_executable(Graph1 main.cpp ${SRC_FILES} ${HEADER_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
