#pragma once

template<typename T>
class LinkedList : public List<T> {
private:
    struct Node {
        T value;
        Node *next;

        explicit Node(const T &value, Node *next = nullptr)
            : value(value), next(next) {
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    // default constructor
    LinkedList() : head(nullptr), tail(nullptr), length(0) {
    }

    // copy constructor
    LinkedList(const LinkedList &other) {
        head = nullptr;
        tail = nullptr;
        length = 0;

        Node *current = other.head;
        while (current != nullptr) {
            LinkedList::add(current->value);
            current = current->next;
        }
    }

    // assignment operator
    LinkedList &operator=(const LinkedList &other) {
        if (this == &other)
            return *this;

        while (head != nullptr) {
            Node *old = head;
            head = head->next;
            delete old;
        }

        head = nullptr;
        tail = nullptr;
        length = 0;
        Node *current = other.head;
        while (current != nullptr) {
            add(current->value);
            current = current->next;
        }

        return *this;
    }

    void add(const T &t) override {
        Node *newNode = new Node{t};

        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
        ++length;
    }

    int getSize() const override {
        return length;
    }

    T &operator[](int index) override {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }

        Node *temp = head;
        for (std::size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }

        return temp->value;
    }

    ~LinkedList() override {
        while (head != nullptr) {
            Node *old = head;
            head = head->next;
            delete old;
        }
    }

    class iterator {
    private:
        Node *node;

    public:
        explicit iterator(Node *node) : node(node) {
        }

        iterator &operator++() {
            node = node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            node = node->next;
            return tmp;
        }

        bool operator==(const iterator &other) const {
            return node == other.node;
        }

        T &operator*() {
            return node->value;
        }

        bool operator!=(const iterator &other) const {
            return !operator==(other);
        }
    };

    iterator begin() {
        iterator it{head};
        return it;
    }

    iterator end() {
        iterator it{nullptr};
        return it;
    }
};
