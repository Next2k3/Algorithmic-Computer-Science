//
// Created by p2 on 12.03.24.
//

#ifndef ZADANIE_3_DOUBLYCIRCULARLINKEDLIST_HPP
#define ZADANIE_3_DOUBLYCIRCULARLINKEDLIST_HPP
struct DoublyCircularLinkedListNode{
public:
    int value;
    DoublyCircularLinkedListNode* next;
    DoublyCircularLinkedListNode* prev;

    DoublyCircularLinkedListNode(int value) : value(value),next(nullptr),prev(nullptr){}
};

class DoublyCircularLinkedList {
public:
    DoublyCircularLinkedListNode* head;
    int size;

    DoublyCircularLinkedList() : head(nullptr), size(0){}

    void insert(int value);
    static DoublyCircularLinkedList merge(DoublyCircularLinkedList& l1,DoublyCircularLinkedList& l2);
    int search(int value);
    void display();
};


#endif //ZADANIE_3_DOUBLYCIRCULARLINKEDLIST_HPP
