#include "Stack.hpp"
#include <iostream>

bool Stack::isEmpty() {
    return height <= 0;
}
int Stack::pop(){
     if(isEmpty()){
         return 0;
     }
     int element = T[height-1];
     height--;
     std::cout<<element<<" ";
     return element;
}
void Stack::push(int element){
    height++;
    if(height>MAX_SIZE){
        return;
    }
    T[height-1] = element;

}