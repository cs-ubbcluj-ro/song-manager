#include "Controller.h"
#include <algorithm>
#include "domain/action/AddAction.h"

void Controller::addSongToRepository(const std::string &artist, const std::string &title, const double minutes,
                                     const double seconds, const std::string &source) {
    const Song s{artist, title, Duration{minutes, seconds}, source};
    repo.addSong(s);

    undoActions.push_back(std::make_unique<AddAction>(s, repo));
    redoActions.clear();
}

void Controller::addSongToPlaylist(const Song &song) {
    playlist.addSong(song);
}

void Controller::addAllSongsByArtistToPlaylist(const std::string &artist) {
    // get all the songs from the repository
    std::vector<Song> songs = repo.getSongs();

    /*
    // I
    for (int i = 0; i < songs.getSize(); i++) {
        if (songs[i].getArtist() == artist) {
            addSongToPlaylist(songs[i]);
        }
    }

    // II
    for (auto it = songs.begin(); it != songs.end(); ++it) {
        auto song = *it;
        if (song.getArtist() == artist) {
            addSongToPlaylist(song);
        }
    }

    // III
    for (const Song &song: songs) {
        if (song.getArtist() == artist) {
            addSongToPlaylist(song);
        }
    }
    */

    // IV
    auto lambda = [artist, this](const Song &song) {
        if (song.getArtist() == artist) {
            this->addSongToPlaylist(song);
        }
    };
    std::ranges::for_each(songs, lambda);
}

void Controller::startPlaylist() {
    auto songOptional = playlist.getCurrentSong();
    if (songOptional.has_value()) {
        songOptional.value().play();
    }
}

void Controller::nextSongPlaylist() {
    playlist.next();
}

void Controller::undoRepositoryAction() {
    if (undoActions.empty()) {
        return;
    }

    auto action = std::move(undoActions.back());
    undoActions.pop_back();

    action->executeUndo();

    redoActions.push_back(std::move(action));
}

void Controller::redoRepositoryAction() {
    if (redoActions.empty()) {
        return;
    }

    auto action = std::move(redoActions.back());
    redoActions.pop_back();

    action->executeRedo();

    undoActions.push_back(std::move(action));
}
