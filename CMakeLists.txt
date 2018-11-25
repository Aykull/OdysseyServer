cmake_minimum_required(VERSION 3.12)
project(TECMFSServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(TECMFSServer main.cpp SimpleList/SimpleList.cpp )