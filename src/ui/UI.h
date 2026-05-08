#pragma once

#include <utility>
#include "controller/Controller.h"

class UI {
private:
    Controller ctrl;

public:
    explicit UI(Controller c) : ctrl(std::move(c)) {
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

    void nextSongFromPlaylist();

    void undoRepositoryAction();

    void redoRepositoryAction();
};
