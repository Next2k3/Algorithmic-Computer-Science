#include <iostream>
#include "CircularLinkedList.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

int main() {
    CircularLinkedList l1,l2;

    for(int i=10;i<20;i++) {
        l1.insert(i);
        l2.insert(i + 10);
    }
    std::cout<<"List 1:"<<std::endl;
    l1.display();
    std::cout<<"List 2:"<<std::endl;
    l2.display();

    CircularLinkedList l3 = CircularLinkedList::merge(l1,l2);
    std::cout<<"Mered list: "<<std::endl;
    l3.display();

    //Eksperyment
    std::srand(std::time(0));

    CircularLinkedList list;
    std::vector<int> inserted;

    for(int i=0;i<10000;++i){
        int x = std::rand() % (100000+1);
        list.insert(x);
        inserted.push_back(x);
    }

    long long totalComparisons = 0, totalComparisonRandom = 0;

    for(int i=0;i<1000;++i){
        int index = std::rand()%10000;
        int value = inserted[index];

        totalComparisons += list.search(value);

        int randomNum = std::rand() % (100000+1);
        totalComparisonRandom += list.search(randomNum);
    }

    std::cout<<"Sredni koszt dla liczb z listy: "<<(double)totalComparisons/1000<<std::endl;
    std::cout<<"Sredni koszt dla liczb losowych: "<<(double)totalComparisonRandom/1000<<std::endl;

    return 0;
}
