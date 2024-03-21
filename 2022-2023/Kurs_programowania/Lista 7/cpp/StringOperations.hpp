//
// Created by Paweł on 25.06.2023.
//

#ifndef A_STRINGOPERATIONS_HPP
#define A_STRINGOPERATIONS_HPP

#include <iostream>
#include <sstream>

class StringOperations{
public:
    StringOperations() = delete;

    ~StringOperations() = delete;
    StringOperations(const StringOperations&) = delete;
    StringOperations(StringOperations&&) = delete;
    StringOperations& operator = (const StringOperations&) = delete;
    StringOperations& operator = (StringOperations&&) = delete;

    static  unsigned int countWords(const std::string& s){
        std::stringstream stream(s);
        unsigned int count=0;
        std::string word;
        while(stream >> word)count++;
        return count;
    }

    template<typename T>
    static T stringToVal(const std::string& s) noexcept(false) {
        std::stringstream stream(s);
        char c;
        T val;

        stream >> val;
        if (stream.fail() || stream.get(c))
            throw std::invalid_argument("Wrong type!");

        return val;
    }
};
#endif //A_STRINGOPERATIONS_HPP
