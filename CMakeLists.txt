cmake_minimum_required(VERSION 3.12)
project(TECMFSServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(TECMFSServer main.cpp SimpleList/SimpleList.cpp Raid5/Existence_controller.cpp Raid5/Existence_controller.h Raid5/file_controller.cpp Raid5/file_controller.h Raid5/GOD_controller.cpp Raid5/GOD_controller.h)