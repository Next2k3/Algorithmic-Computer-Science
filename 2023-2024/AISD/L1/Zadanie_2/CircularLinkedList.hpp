//
// Created by p2 on 12.03.24.
//

#ifndef ZADANIE_2_CIRCULARLINKEDLIST_HPP
#define ZADANIE_2_CIRCULARLINKEDLIST_HPP

struct CircularLinkedListNode{
    int value;
    CircularLinkedListNode* next;

    CircularLinkedListNode(int value) : value(value), next(nullptr){}
};
class CircularLinkedList {
public:
    CircularLinkedListNode* head;
    int size;

    CircularLinkedList() : head(nullptr), size(0) {}
    void insert(int value);
    static CircularLinkedList merge(CircularLinkedList& l1, CircularLinkedList& l2);
    int search(int value);
    void display();
};


#endif //ZADANIE_2_CIRCULARLINKEDLIST_HPP
