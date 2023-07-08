cmake_minimum_required(VERSION 3.7...3.26)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    CustomStd
    VERSION 1.0
    DESCRIPTION "My take on the standard library"
    LANGUAGES CXX
)
add_library(Vector src/Vector.h src/UniquePtr.h src/String.h)

set_property(TARGET Vector 
    PROPERTY CXX_STANDARD 17)

set_property(TARGET Vector
    PROPERTY LINKER_LANGUAGE CXX)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
