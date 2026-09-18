
#include <cstring>
#include <iostream>

class sstring {
    char* n = nullptr;
    size_t size_ = 0;

public:
    // default one
    sstring(const char* c = nullptr) {
        if (c) {
            size_=std::strlen(c);
            n = new char[size_ + 1];
            std::strcpy(n, c);
        } else {
            size_ = 0;
            n = new char[1]{'\0'};
        }
    }

    // copy constructor (using new memory and then copying the characters)
    sstring(const sstring& s) : size_(s.size_) {
        n = new char[size_ + 1];
        std::strcpy(n, s.n);
    }

    // move constructor
    sstring(sstring&& s) noexcept : n(s.n), size_(s.size_) {
        s.n = nullptr;
        s.size_=0;
    }

    // destructor
    ~sstring() {
        delete[] n;
    }

    //copy
    sstring& operator=(const sstring &s) {
        if (this != &s) {
            delete[] n;
            size_ = s.size_;
            n = new char[size_+1];
            std::strcpy(n, s.n);
        }
        return *this;
    }
    //assign
    sstring& operator=(const char* c) {
        delete[] n;
        if (c) {
            size_ = std::strlen(c);
            n = new char[size_ + 1];
            std::strcpy(n, c);
        } else {
            size_ = 0;
            n = new char[1]{'\0'};
        }
        return *this;
    }

    sstring& operator+=(const sstring& rhs) {
        size_t new_len = size_ + rhs.size_;
        char* new_n = new char[new_len + 1];

        if (n) std::strcpy(new_n, n);
        if (rhs.n) std::strcpy(new_n + size_, rhs.n);

        delete[] n;
        n = new_n;
        size_ = new_len;
        return *this;
    }

    friend sstring operator+(sstring lhs, const sstring& rhs) {
        lhs += rhs;
        return lhs;
    }

    char operator[](size_t i) const { return n[i]; }
    char& operator[](size_t i) { return n[i]; }

    auto begin() const {
        return n;
    }
    auto end() const {
        return n + size_;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

};

inline std::ostream& operator<<(std::ostream& os, const sstring& s) {
    for (char c : s) {
        os << c;
    }
    return os;
}