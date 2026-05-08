cmake_minimum_required(VERSION 4.1)
project(song_manager)

set(CMAKE_CXX_STANDARD 23)

# Enable testing
enable_testing()

# -------------------------
# External dependencies
# -------------------------
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE
        ${CMAKE_SOURCE_DIR}/lib
)

# -------------------------
# Core library
# -------------------------
add_library(core
        src/controller/Controller.cpp
        src/domain/playlist/Playlist.cpp
        src/domain/Song.cpp
        src/repository/Repository.cpp
        src/ui/UI.cpp
        src/domain/list/List.h
        src/domain/list/LinkedList.h
        src/domain/playlist/FilePlaylist.h
        src/domain/playlist/JsonPlaylist.h
        src/domain/action/Action.h
        src/domain/action/AddAction.h
        src/domain/action/RemoveAction.h
)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(core PUBLIC nlohmann_json)

# -------------------------
# App executable
# -------------------------
add_executable(app
        src/main.cpp
)

target_link_libraries(app PRIVATE core)

# -------------------------
# Tests executable
# -------------------------
add_executable(tests
        test/Tests.cpp
        test/main.cpp
)

target_link_libraries(tests PRIVATE core)

# Register with CTest
add_test(NAME Tests COMMAND tests)
