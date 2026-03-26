cmake_minimum_required(VERSION 4.1)
project(song_manager)

set(CMAKE_CXX_STANDARD 23)

add_executable(song_manager
        main.cpp
        Controller.cpp
        Repository.cpp
        Song.cpp
        Tests.cpp
        UI.cpp)
