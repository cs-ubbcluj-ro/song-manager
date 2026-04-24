#pragma once

#include <string>

class Tests {
public:
    static void testSong();

    static void testDynamicVector();

    static void testRepository();

    static void testPlaylist();

    static void testController();

    static void testLinkedList();

    static void testJsonPlaylist();

    static void testAll();

    static std::string generateRandomFilename(const std::string &prefix);
};
