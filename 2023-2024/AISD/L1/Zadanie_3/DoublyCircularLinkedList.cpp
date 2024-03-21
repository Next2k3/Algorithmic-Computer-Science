//
// Created by p2 on 12.03.24.
//

#include "DoublyCircularLinkedList.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void DoublyCircularLinkedList::insert(int value) {
    DoublyCircularLinkedListNode* newNode = new DoublyCircularLinkedListNode(value);
    if(!head){
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else{
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    size++;
}
DoublyCircularLinkedList DoublyCircularLinkedList::merge(DoublyCircularLinkedList &l1, DoublyCircularLinkedList &l2) {
    if(!l1.head)return l2;
    if(!l2.head) return l1;

    DoublyCircularLinkedListNode* l1last = l1.head->prev;
    DoublyCircularLinkedListNode* l2last = l2.head->prev;

    l1last->next =l2.head;
    l2.head->prev=l1last;

    l2last->next = l1.head;
    l1.head->prev = l2last;

    l1.size +=l2.size;
    l2.head = nullptr;
    l2.size = 0;

    return l1;
}
int DoublyCircularLinkedList::search(int value) {
    int comparisons = 0;
    if(!head) return comparisons;

    bool direction = std::rand() % 2;

    DoublyCircularLinkedListNode* temp = head;
    do{
        comparisons++;
        if(temp->value == value) break;
        temp = direction ? temp->prev : temp->next;
    }while(temp!=head);
    return comparisons;
}
void DoublyCircularLinkedList::display() {
    if(this->head == nullptr){
        return;
    }
    DoublyCircularLinkedListNode* temp = this->head;
    do{
        std::cout<<temp->value<<" ";
        temp = temp->next;
    }while(temp != this->head);
    std::cout<<std::endl;
}