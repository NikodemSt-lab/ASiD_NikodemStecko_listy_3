#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>
#include <cstddef>

template <typename T>
class ArrayList {
    T* tab;
    std::size_t msize;
    std::size_t last;
public:
    ArrayList(std::size_t s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    }
    ~ArrayList() { delete [] tab; }

    ArrayList(const ArrayList& other);
    ArrayList(ArrayList&& other);

    ArrayList& operator=(const ArrayList& other);
    ArrayList& operator=(ArrayList&& other);

    bool empty() const { return last == 0; }
    bool full() const { return last == msize; }
    std::size_t size() const { return last; }
    std::size_t max_size() const { return msize; }
    void push_front(const T& item);
    void push_front(T&& item);
    void push_back(const T& item);
    void push_back(T&& item);
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void pop_front();
    void pop_back();
    void clear();
    void display();
    void reverse();
    void sort();
    void merge(ArrayList& other);

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;
    void erase(std::size_t pos);
    int index(const T& item);
    void insert(std::size_t pos, const T& item);
    void insert(std::size_t pos, T&& item);

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i=0; i < L.last; ++i) {
            os << L.tab[i] << " ";
        }
        return os;
    }
};

// Konstruktor kopiujacy
template <typename T>
ArrayList<T>::ArrayList(const ArrayList& other)
    : tab(new T[other.msize]), msize(other.msize), last(other.last) {
    assert(tab != nullptr);
    for (std::size_t i = 0; i < last; ++i) {
        tab[i] = other.tab[i];
    }
}

// Konstruktor przenoszacy
template <typename T>
ArrayList<T>::ArrayList(ArrayList&& other)
    : tab(other.tab), msize(other.msize), last(other.last) {
    other.tab = nullptr;
    other.msize = 0;
    other.last = 0;
}

// Kopiujacy operator przypisania
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
    if (this != &other) {
        delete [] tab;
        msize = other.msize;
        last = other.last;
        tab = new T[msize];
        assert(tab != nullptr);
        for (std::size_t i = 0; i < last; ++i) {
            tab[i] = other.tab[i];
        }
    }
    return *this;
}

// Przenoszacy operator przypisania
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other) {
    if (this != &other) {
        delete [] tab;
        tab = other.tab;
        msize = other.msize;
        last = other.last;
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    }
    return *this;
}

// push_front
template <typename T>
void ArrayList<T>::push_front(const T& item) {
    assert(!full());
    std::copy_backward(tab, tab + last, tab + last + 1);
    tab[0] = item;
    ++last;
}

template <typename T>
void ArrayList<T>::push_front(T&& item) {
    assert(!full());
    std::copy_backward(tab, tab + last, tab + last + 1);
    tab[0] = std::move(item);
    ++last;
}

// push_back
template <typename T>
void ArrayList<T>::push_back(const T& item) {
    assert(!full());
    tab[last] = item;
    ++last;
}

template <typename T>
void ArrayList<T>::push_back(T&& item) {
    assert(!full());
    tab[last] = std::move(item);
    ++last;
}

// front
template <typename T>
T& ArrayList<T>::front() {
    assert(!empty());
    return tab[0];
}

template <typename T>
const T& ArrayList<T>::front() const {
    assert(!empty());
    return tab[0];
}

// back
template <typename T>
T& ArrayList<T>::back() {
    assert(!empty());
    return tab[last - 1];
}

template <typename T>
const T& ArrayList<T>::back() const {
    assert(!empty());
    return tab[last - 1];
}

// pop_front
template <typename T>
void ArrayList<T>::pop_front() {
    assert(!empty());
    std::copy(tab + 1, tab + last, tab);
    --last;
}

// pop_back
template <typename T>
void ArrayList<T>::pop_back() {
    assert(!empty());
    --last;
}

// clear
template <typename T>
void ArrayList<T>::clear() {
    last = 0;
}

// display
template <typename T>
void ArrayList<T>::display() {
    for (std::size_t i = 0; i < last; ++i) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

// reverse
template <typename T>
void ArrayList<T>::reverse() {
    for (std::size_t i = 0; i < last / 2; ++i) {
        std::swap(tab[i], tab[last - 1 - i]);
    }
}

// sort
template <typename T>
void ArrayList<T>::sort() {
    std::sort(tab, tab + last);
}

// merge
template <typename T>
void ArrayList<T>::merge(ArrayList& other) {
    if (this == &other) {
        return;
    }
    assert(last + other.last <= msize);
    for (std::size_t i = 0; i < other.last; ++i) {
        tab[last + i] = std::move(other.tab[i]);
    }
    std::inplace_merge(tab, tab + last, tab + last + other.last);
    last += other.last;
    other.clear();
}

// operator[]
template <typename T>
T& ArrayList<T>::operator[](std::size_t pos) {
    assert(pos < last);
    return tab[pos];
}

template <typename T>
const T& ArrayList<T>::operator[](std::size_t pos) const {
    assert(pos < last);
    return tab[pos];
}

// erase
template <typename T>
void ArrayList<T>::erase(std::size_t pos) {
    assert(pos < last);
    std::copy(tab + pos + 1, tab + last, tab + pos);
    --last;
}

// index
template <typename T>
int ArrayList<T>::index(const T& item) {
    for (std::size_t i = 0; i < last; ++i) {
        if (tab[i] == item) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// insert
template <typename T>
void ArrayList<T>::insert(std::size_t pos, const T& item) {
    assert(pos <= last);
    assert(!full());
    std::copy_backward(tab + pos, tab + last, tab + last + 1);
    tab[pos] = item;
    ++last;
}

template <typename T>
void ArrayList<T>::insert(std::size_t pos, T&& item) {
    assert(pos <= last);
    assert(!full());
    std::copy_backward(tab + pos, tab + last, tab + last + 1);
    tab[pos] = std::move(item);
    ++last;
}

#endif

// EOF

