cmake_minimum_required(VERSION 3.24)
project(LibraryBookManageSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(LibraryBookManageSystem
        include/book.h
        include/rbTree.h
        include/user.h
        include/userManager.h
        src/book.cpp
        src/main.cpp
        src/user.cpp
        src/userManager.cpp
        src/bookManager.cpp
        include/bookManager.h
        src/menu.cpp
        include/menu.h)
