#include <iostream>
#include "ConsoleHandler.hpp"

int main(int argc, char const *argv[]) {
    std::cout<<"Wybierz typ drzewa:\n";
    std::cout<<"Integer / Double / String\n";

    std::string type;

    while(true){
        getline(std::cin,type);
        if(type=="Integer"){
            ConsoleHandler<int> handler;
            handler.run();
            return 0;
        }else if (type == "double") {
            ConsoleHandler<double> handler;
            handler.run();
            return 0;
        }
        else if (type == "string") {
            ConsoleHandler<std::string> handler;
            handler.run();
            return 0;
        }
        else {
            std::cout << "Typ " << type << " jest niepoprawny. Wybierz ponownie\n";
        }
    }

    return 0;
}

