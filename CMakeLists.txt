cmake_minimum_required(VERSION 3.15)

project(BigNum LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BigNum src/BigNum.cpp src/BigNumUtils.cpp)

target_include_directories(BigNum PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(BigNumTest test/BigNumTest.cpp)
target_link_libraries(BigNumTest PRIVATE BigNum gtest_main)
target_include_directories(BigNumTest PRIVATE ${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)