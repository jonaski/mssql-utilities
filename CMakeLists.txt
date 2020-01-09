project(mssql-utilities)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -U__STRICT_ANSI__ -Wall -Wextra -Wpedantic -Woverloaded-virtual -fpermissive")

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8)
  set(EXPERIMENTAL_FILESYSTEM ON)
endif()

find_package(Boost REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

if(MSSQL_DETACH)
  add_executable(mssql-detach mssql-attach.cpp)
  if(EXPERIMENTAL_FILESYSTEM)
    target_link_libraries(mssql-detach stdc++fs)
  endif()
else(MSSQL_DETACH)
  add_executable(mssql-attach mssql-attach.cpp)
  if(EXPERIMENTAL_FILESYSTEM)
    target_link_libraries(mssql-attach stdc++fs)
  endif()
endif(MSSQL_DETACH)
