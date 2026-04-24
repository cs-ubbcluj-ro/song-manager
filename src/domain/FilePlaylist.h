#pragma once
#include "Playlist.h"
#include <utility>

class FilePlaylist : public Playlist {
protected:
    std::string path;

public:
    explicit FilePlaylist(std::string path) : path(std::move(path)) {
    }

    ~FilePlaylist() = default;
};
