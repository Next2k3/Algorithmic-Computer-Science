
#ifndef A_CONSOLEHANDLER_HPP
#define A_CONSOLEHANDLER_HPP

#include "BinaryTree.hpp"
#include "StringOperations.hpp"

#include <iostream>
#include <sstream>

template<typename T>
class ConsoleHandler {
private:
    BinaryTree<T> tree;
public:
    void run() {
        std::cout << "Wybierz komende: insert / delete / search / print\n";
        std::cout << "Kazda z koment potrzebuje jednego argumentu poza print\n ";
        std::cout << "Program mozna zakonczyc wpisujac exit\n";

        std::string input;
        unsigned int wordCount;
        while(true){
            try{
                std::getline(std::cin,input);
                wordCount = StringOperations::countWords(input);

                if(wordCount <1 || wordCount > 2)
                    throw std::invalid_argument("Max 2 slowa, nie: "+std::to_string(wordCount));

                std::stringstream inputStream(input);
                std::string action;
                std::string argument = "";

                inputStream >> action;
                if (wordCount == 2) inputStream >> argument;

                if (action == "insert") {
                    if (wordCount != 2)
                        throw std::invalid_argument("Insert requires 2 arguments, not " + std::to_string(wordCount));

                    tree.insertValue(StringOperations::stringToVal<T>(argument));
                }
                else if (action == "delete") {
                    if (wordCount != 2)
                        throw std::invalid_argument("Delete requires 2 arguments, not " + std::to_string(wordCount));

                    tree.deleteValue(StringOperations::stringToVal<T>(argument));
                }
                else if (action == "search") {
                    if (wordCount != 2)
                        throw std::invalid_argument("Search requires 2 arguments, not " + std::to_string(wordCount));

                    if (tree.searchValue(StringOperations::stringToVal<T>(argument)) == true) std::cout << "The element IS in the tree\n";
                    else std::cout << "The element IS NOT in the tree\n";
                }
                else if (action == "print") {
                    if (wordCount != 1)
                        throw std::invalid_argument("Print requires only 1 argument, not " + std::to_string(wordCount));

                    tree.printTree();
                }
                else if (action == "exit") {
                    return;
                }
                else {
                    std::cout << action << " is not on of the allowed actions!\n";
                }
            }
            catch (const std::invalid_argument &e) {
                std::cout << e.what() << '\n';
            }
        }
    }
};
#endif //A_CONSOLEHANDLER_HPP
