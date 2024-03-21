//
// Created by p2 on 11.03.24.
//

#ifndef L1_STACK_HPP
#define L1_STACK_HPP


class Stack {
public:
    static const int MAX_SIZE = 1000;
    Stack(){}
    int pop();
    void push(int element);
private:
    int height = 0;
    int T[MAX_SIZE];
    bool isEmpty();
};


#endif //L1_STACK_HPP
