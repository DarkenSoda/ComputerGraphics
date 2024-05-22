cmake_minimum_required(VERSION 3.29.2)
project(ComputerGraphics VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SRCS "*.cpp")
list(FILTER SRCS EXCLUDE REGEX "build/.*")

add_executable(ComputerGraphics
    ${SRCS}
)

include(CPack)
