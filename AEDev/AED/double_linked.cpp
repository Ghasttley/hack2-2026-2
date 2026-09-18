//
// Created by LENOVO on 31/08/2026.
//
#include <iostream>
#include <string>

template <class T>
class double_linked_list
{
    struct node{
        T data;
        node * next = nullptr;
        node * prev = nullptr;
        node(T val, node * n = nullptr, node * p = nullptr) : data(val), next(n), prev(p) {}
    };

    node * head = nullptr;
    node * tail = nullptr;
    int size = 0;

public:
    double_linked_list() = default;

    int first() {
        return head == nullptr ? 0 : head->data;
    }

    int last() {
        return tail == nullptr ? 0 : tail->data;
    }

    void insert(const T & d) {
        if (size == 0) {
            head = tail = new node(d);
        } else {
            node * temp = new node(d, nullptr, tail);
            tail->next = temp;
            tail = temp;
        }
        size++;
    }

    void deletee(const T & d) {
        node * temp = head;
        while (temp != nullptr) {
            node * next_node = temp->next;
            if (temp->data == d) {
                if (temp == head) {
                    head = temp->next;
                } else {
                    temp->prev->next = temp->next;
                }

                if (temp == tail) {
                    tail = temp->prev;
                } else {
                    temp->next->prev = temp->prev;
                }

                delete temp;
                size--;
            }
            temp = next_node;
        }
    }

    void deleteFirst() {
        if (head == nullptr) return;
        node * temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List is now empty
        }

        delete temp;
        size--;
    }

    void deleteLast() {
        if (tail == nullptr) return;
        node * temp = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;
        size--;
    }

    size_t sizet() {
        return size;
    }

    void print() {
        node * temp = head;
        for (int i = 0; i < size; i++) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

/*
int main() {
double_linked_list<int> flop;

int funsize;
if (!(std::cin >> funsize)) return 0;

while (funsize > 0) {
    std::string fun;
    std::cin >> fun;

    if (fun == "insert") {
        int val;
        std::cin >> val;
        flop.insert(val);
    }
    else if (fun == "delete") {
        int val;
        std::cin >> val;
        flop.deletee(val);
    }
    else if (fun == "deleteFirst") {
        flop.deleteFirst();
    }
    else if (fun == "deleteLast") {
        flop.deleteLast();
    }

    funsize--;
}

flop.print();
return 0;
}*/