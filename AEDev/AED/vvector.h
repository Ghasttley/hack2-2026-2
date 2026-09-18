#pragma once
#include <initializer_list>
#include <iostream>
#include <utility>

template <typename T>

class vvector {
    T* dat_= nullptr;
    size_t size_ = 0;
    size_t cap_= 0;

    void change_cap(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(dat_[i]);
        }
        delete[] dat_;
        dat_ = new_data;
        cap_ = new_cap;
    }

public:
    // default
    vvector() : dat_(nullptr), size_(0), cap_(0) {}

    explicit vvector(size_t count, const T& value = T()) : size_(count), cap_(count) {
        dat_ = new T[cap_];
        for (size_t i = 0; i < size_; ++i) {
            dat_[i] = value;
        }
    }

    // init with list {}
    vvector(std::initializer_list<T> init) : size_(init.size()), cap_(init.size()) {
        dat_ = new T[cap_];
        size_t i = 0;
        for (const auto& item : init) {
            dat_[i++] = item;
        }
    }

    // copy constructor
    vvector(const vvector& other) : size_(other.size_), cap_(other.cap_) {
        dat_ = new T[cap_];
        for (size_t i = 0; i < size_; ++i) {
            dat_[i] = other.dat_[i];
        }
    }

    // move constructor
    vvector(vvector&& other) noexcept : dat_(other.dat_), size_(other.size_), cap_(other.cap_) {
        other.dat_ = nullptr;
        other.size_= 0;
        other.cap_= 0;
    }

    // destructor
    ~vvector() {
        delete[] dat_;
    }

    // copy
    vvector& operator=(const vvector& other) {
        if (this != &other) {
            delete[] dat_;
            size_ = other.size_;
            cap_ = other.cap_;
            dat_ = new T[cap_];
            for (size_t i = 0; i < size_; ++i) {
                dat_[i] = other.dat_[i];
            }
        }
        return *this;
    }

    // move
    vvector& operator=(vvector&& other) noexcept {
        if (this != &other) {
            delete[] dat_;
            dat_ = other.dat_;
            size_ = other.size_;
            cap_ = other.cap_;

            other.dat_ = nullptr;
            other.size_ = 0;
            other.cap_ = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
            change_cap(new_cap);
        }
        dat_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
            change_cap(new_cap);
        }
        dat_[size_++]= std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            dat_[size_].~T();
        }
    }

    T& operator[](size_t index) {
        return dat_[index];
    }
    const T& operator[](size_t index) const {
        return dat_[index];
    }

    T* begin() {
        return dat_;
    }
    T* end() {
        return dat_ + size_;
    }
    const T* begin() const {
        return dat_;
    }
    const T* end() const {
        return dat_ + size_;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }
    [[nodiscard]] size_t capacity() const {
        return cap_;
    }
    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }
};
template<typename S>
std::ostream& operator<<(std::ostream& os, const vvector<S>& s) {
    for (S c : s) {
        os<<c<<" ";
    }
    return os;
}