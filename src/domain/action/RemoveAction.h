#pragma once

#include <utility>
#include "Action.h"
#include "domain/Song.h"
#include "repository/Repository.h"

class RemoveAction : public Action {
private:
    Song song;
    Repository &repository;

public:
    RemoveAction(Song song, Repository &repository)
        : song(std::move(song)), repository(repository) {
    }

    void executeUndo() override {
        repository.addSong(song);
    }

    void executeRedo() override {
        repository.removeSong(song);
    }
};
