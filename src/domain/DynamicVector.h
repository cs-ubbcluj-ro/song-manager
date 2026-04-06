#pragma once

template<typename T>
class DynamicVector {
private:
    T *elems;
    int size;
    int capacity;

public:
    // default constructor for a DynamicVector
    explicit DynamicVector(int capacity = 10);

    // copy constructor for a DynamicVector
    DynamicVector(const DynamicVector &v);

    // destructor
    ~DynamicVector();

    // assignment operator for a DynamicVector
    DynamicVector &operator=(const DynamicVector &v);

    /*
        Overloading the subscript operator
        Input: pos - a valid position within the vector.
        Output: a reference to the element o position pos.
    */
    T &operator[](int index);

    // Adds an element to the current DynamicVector.
    void add(const T &e);

    int getSize() const;

private:
    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(double factor = 2);

public:
    class iterator {
    private:
        T *ptr;

    public:
        // constructor with parameter T*
        explicit iterator(T *ptr) : ptr{ptr} {
        }

        // operator ++pre
        iterator &operator++() {
            ++ptr;
            return *this;
        }

        // operator post++
        iterator operator++(int) {
            iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        // dereferencing operator
        T &operator*() {
            return *ptr;
        }

        // operator !=
        bool operator!=(const iterator &other) {
            return ptr != other.ptr;
        }

        // operator ==
        bool operator==(const iterator &other) {
            return ptr == other.ptr;
        }
    };

    iterator begin() {
        return iterator(elems);
    }

    iterator end() {
        return iterator(elems + size);
    }
};

template<typename T>
DynamicVector<T>::DynamicVector(const int capacity)
    : elems{new T[capacity]}, size{0}, capacity{capacity} {
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &v) {
    this->size = v.size;
    this->capacity = v.capacity;
    this->elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];
}

template<typename T>
DynamicVector<T>::~DynamicVector() {
    delete[] elems;
}

template<typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &v) {
    if (this == &v)
        return *this;

    size = v.size;
    capacity = v.capacity;

    delete[] elems;
    elems = new T[capacity];
    for (int i = 0; i < size; i++)
        elems[i] = v.elems[i];

    return *this;
}

template<typename T>
T &DynamicVector<T>::operator[](int index) {
    return elems[index];
}

template<typename T>
void DynamicVector<T>::add(const T &e) {
    if (size == capacity)
        resize();
    elems[size] = e;
    size++;
}

template<typename T>
void DynamicVector<T>::resize(const double factor) {
    capacity *= static_cast<int>(factor);

    T *tmp = new T[capacity];
    for (int i = 0; i < size; i++)
        tmp[i] = elems[i];

    delete[] elems;
    elems = tmp;
}

template<typename T>
int DynamicVector<T>::getSize() const {
    return size;
}
