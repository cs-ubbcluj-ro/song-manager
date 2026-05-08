#pragma once

#include <vector>
#include <memory>
#include <string>
#include "domain/action/Action.h"
#include "domain/playlist/Playlist.h"
#include "repository/Repository.h"

class Controller {
private:
    Repository repo;
    Playlist playlist;
    std::vector<std::unique_ptr<Action> > undoActions;
    std::vector<std::unique_ptr<Action> > redoActions;

public:
    explicit Controller(Repository r)
        : repo{std::move(r)} {
    }

    Repository &getRepo() {
        return repo;
    }

    Playlist &getPlaylist() {
        return playlist;
    }

    // Adds a song with the given data to the song repository.
    void addSongToRepository(const std::string &artist, const std::string &title, double minutes, double seconds,
                             const std::string &source);

    /*
        Adds a given song to the current playlist.
        Input: song - Song, the song must belong to the repository.
        Output: the song is added to the playlist.
    */
    void addSongToPlaylist(const Song &song);

    // Adds all the songs from the repository, that have the given artist, to the current playlist.
    void addAllSongsByArtistToPlaylist(const std::string &artist);

    void startPlaylist();

    void nextSongPlaylist();

    void undoRepositoryAction();

    void redoRepositoryAction();
};
