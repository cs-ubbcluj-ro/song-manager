#pragma once

class Action {
public:
    virtual ~Action() = default;

    virtual void executeUndo() = 0;

    virtual void executeRedo() = 0;
};
