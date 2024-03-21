#include "Queue.hpp"

#include <iostream>

bool Queue::isEmpty() {
    return  size <= 0;
}
int Queue::pop(){
    if(isEmpty()){
        return 0;
    }
    int element = T[firstElement];
    firstElement = (firstElement+1)%MAX_SIZE;
    size--;
    std::cout<<element<<" ";
    return element;
}
void Queue::push(int element) {
    lastElement = (lastElement+1)%MAX_SIZE;
    size++;
    if(size>MAX_SIZE){
        return;
    }
    T[lastElement]=element;
}