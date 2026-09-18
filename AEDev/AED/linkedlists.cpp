/*
//
// Created by LENOVO on 28/08/2026.
//

#include <iostream>

template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;
    };
    node * head = nullptr;
    node * tail = nullptr;
    size_t size = 0;
public:
    linked_list() = default;
    void push_front(const T & d)
    {
        if (size == 0 && tail == nullptr)
            tail = new node (d, nullptr);
        else
            head = new node(d, head);
        size++;
    }
    node ** search(const T & d){
        node ** n = &head;
        while(*n && (*n)->dato != d)
            n = &(*n)->next;
        return n;
    }
    node ** remove(node ** n){
        node * nt = *n;
        *n = nt->next;
        delete nt;
        return n;
    }
    node ** insert(node ** n, const T & d){
        *n = new node(d, *n);
        return n;
    }
    friend std::ostream & operator << (std::ostream & os, const
    linked_list<T> & ll){
        os << "head -> ";
        for(node * n = ll.head; n; n = n->next)
            os << n->dato << " -> ";
        return os;
    }
    void reverse(){
        node * current=head;
        node * temp=nullptr;
        while (current!= nullptr) {
            node * next = current->next;
            current->next = temp;
            temp = current;

            current = next;
        }
        head = temp;
    }
    //understand the reverse function !!!!

};


/*
int main()
{
    linked_list<int> ll;
    for(int i = 1; i < 11; ++i)
        ll.push_front(i);
    std::cout << ll << std::endl;
    ll.remove(ll.search(5));
    std::cout << ll << std::endl;
    ll.insert(ll.search(8), 88);
    std::cout << ll << std::endl;
    ll.reverse();
    std::cout << ll << std::endl;
    return 0;
}
#1#
*/
