#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"

int main() {
    std::cout<<"Queue"<<std::endl;
    Queue queue;
    for(int i=1;i<=50;i++){
        queue.push(i);
    }
    for(int i=1;i<=50;i++){
        queue.pop();
    }
    std::cout<<" "<<std::endl;
    std::cout<<"Stack"<<std::endl;
    Stack stack;
    for(int i=1;i<=50;i++){
        stack.push(i);
    }
    for(int i=1;i<=50;i++){
        stack.pop();
    }
    return 0;
}
