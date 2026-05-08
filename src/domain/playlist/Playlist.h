#pragma once

#include <optional>
#include "domain/Song.h"
#include "domain/list/DynamicVector.h"

class Playlist {
protected:
    DynamicVector<Song> songs;
    DynamicVector<Song>::iterator it;

public:
    Playlist();

    void addSong(const Song &s);

    void next();

    std::optional<Song> getCurrentSong();

    [[nodiscard]] bool isEmpty() const;
};
