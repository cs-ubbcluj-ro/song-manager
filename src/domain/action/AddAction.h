#pragma once

#include <utility>
#include "Action.h"
#include "domain/Song.h"
#include "repository/Repository.h"

class AddAction : public Action {
private:
    Song song;
    Repository &repository;

public:
    AddAction(Song song, Repository &repository)
        : song(std::move(song)), repository(repository) {
    }

    void executeUndo() override {
        repository.removeSong(song);
    }

    void executeRedo() override {
        repository.addSong(song);
    }
};
