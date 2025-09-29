cmake_minimum_required(VERSION 3.26)
project(C__)

set(CMAKE_CXX_STANDARD 17)

add_executable(C__
        main.cpp
        functions.h
        User.cpp
        User.h
        HashTable.cpp
        HashTable.h
        Post.cpp
        Post.h
        Message.cpp
        Message.h
        Chat.cpp
        Chat.h)
