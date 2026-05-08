#pragma once

#include <utility>
#include "controller/Controller.h"

class UI {
private:
    Controller &ctrl;

public:
    explicit UI(Controller &controller) : ctrl(controller) {
    }

    void run();

private:
    static void printMenu();

    static void printRepositoryMenu();

    static void printPlayListMenu();

    void addSongToRepo();

    void displayAllSongsRepo();

    void addSongToPlaylist();

    void addAllSongsByArtistToPlaylist();

    void playSongsFromPlaylist();
};
