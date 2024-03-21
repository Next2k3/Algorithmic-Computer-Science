#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "DoublyCircularLinkedList.hpp"

int main() {
    std::srand(std::time(0));

    DoublyCircularLinkedList l1,l2;
    for(int i=10;i<20;i++){
        l1.insert(i);
        l2.insert(i+10);
    }

    std::cout<<"List 1: "<<std::endl;
    l1.display();
    std::cout<<"List 2: "<<std::endl;
    l2.display();

    DoublyCircularLinkedList l3 = DoublyCircularLinkedList::merge(l1,l2);
    std::cout<<"Merged: "<<std::endl;
    l3.display();
    //Eksperyment
    DoublyCircularLinkedList search;
    std::vector<int> numbers;

    for(int i=0;i<10000;++i){
        int x = std::rand() % (100000+1);
        numbers.push_back(x);
        search.insert(x);
    }

    long long totalComparisons = 0, totalComparisonsRandom = 0;

    for(int i=0;i<1000;++i){
        int index = std::rand() % numbers.size();
        int value = numbers[index];
        totalComparisons += search.search(value);

        int x = std::rand() % (10000+1);
        totalComparisonsRandom += search.search(x);
    }
    std::cout<<"Sredni koszt wyszukiwania z listy: "<<(double)totalComparisons/1000<<std::endl;
    std::cout<<"Sredni koszt wysukiwania losowej: "<<(double)totalComparisonsRandom/1000<<std::endl;

    return 0;
}
