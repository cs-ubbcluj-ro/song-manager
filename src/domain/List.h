#pragma once

template<typename T>
class List {
public:
    virtual void add(const T &t) =0;

    virtual int getSize() const =0;

    virtual T &operator[](int i) =0;

    virtual ~List() = default;
};
