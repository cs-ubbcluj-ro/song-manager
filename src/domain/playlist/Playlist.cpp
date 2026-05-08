#include "Playlist.h"

Playlist::Playlist() : it{songs.begin()} {
}

void Playlist::addSong(const Song &s) {
    if (isEmpty()) {
        songs.add(s);
        it = songs.begin();
    } else {
        songs.add(s);
    }
}

void Playlist::next() {
    if (isEmpty()) {
        return;
    }
    ++it;
    if (it == songs.end()) {
        it = songs.begin();
    }
}

std::optional<Song> Playlist::getCurrentSong() {
    if (isEmpty()) {
        return std::nullopt;
    }
    return std::optional{*it};
}

bool Playlist::isEmpty() const {
    return songs.getSize() == 0;
}
