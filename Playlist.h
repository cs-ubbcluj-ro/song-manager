#pragma once

#include "DynamicVector.h"
#include "Song.h"

class Playlist {
private:
    DynamicVector<Song> songs;
    DynamicVector<Song>::iterator it;

public:
    Playlist();

    void addSong(const Song &s);

    void next();

    std::optional<Song> getCurrentSong();

    bool isEmpty() const;
};
