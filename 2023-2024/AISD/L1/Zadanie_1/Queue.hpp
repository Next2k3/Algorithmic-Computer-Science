#ifndef L1_QUEUE_HPP
#define L1_QUEUE_HPP


class Queue {
public:
    static const int MAX_SIZE =1000;
    Queue(){}
    int pop();
    void push(int element);
private:
    int size=0;
    int firstElement=0;
    int lastElement=-1;
    int T[MAX_SIZE];

    bool isEmpty();
};


#endif //L1_QUEUE_HPP
