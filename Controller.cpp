#include "Controller.h"
#include <string>

void Controller::addSongToRepository(const std::string &artist, const std::string &title, const double minutes,
                                     const double seconds, const std::string &source) {
    const Song s{artist, title, Duration{minutes, seconds}, source};
    repo.addSong(s);
}

void Controller::addSongToPlaylist(const Song &song) {
    playlist.addSong(song);
}

void Controller::addAllSongsByArtistToPlaylist(const std::string &artist) {
    // get all the songs from the repository
    DynamicVector<Song> songs = repo.getSongs();

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
    std::for_each(songs.begin(), songs.end(), lambda);
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
