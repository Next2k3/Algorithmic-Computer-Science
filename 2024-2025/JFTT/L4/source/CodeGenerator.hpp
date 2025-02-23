#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <fstream>

struct command {
    std::string code;
    int64_t arg;
};


class CodeGenerator {
public:
    CodeGenerator() : currentLine(0),labelCounter(0){}

    int64_t createLabel() {
        return labelCounter++;
    }


    void emit(const std::string& code, int64_t arg) {
        generatedCode.push_back(command{code, arg});
        currentLine++;
    }

    command getCommand(u_int64_t line) {
        if(line >= generatedCode.size()){
            return command{"", 0};
        }
        return generatedCode[line];
    }

    void updateCommand(u_int64_t line, const std::string& code, int64_t arg) {
        if(line >= generatedCode.size()){
            return;
        }
        generatedCode[line] = command{code, arg};
    }

    void print() {
        for (const auto& code : generatedCode) {
            if(code.code == "HALT" || code.code == "HALF") {
                std::cout << code.code << "\n";
            } else{ 
                std::cout << code.code << " " << code.arg << "\n";
            }
        }
    }
    
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }
        for (const auto& code : generatedCode) {
            if(code.code == "HALT" || code.code == "HALF") {
                file << code.code << "\n";
            } else{ 
                file << code.code << " " << code.arg << "\n";
            }
        }
    }

    void removeLastCommand(){
        generatedCode.pop_back();
        currentLine--;
    }

    int64_t getCurrentLine() const {
        return currentLine;
    }

    std::vector<command> getGeneratedCode() const {
        return generatedCode;
    }
private:
    mutable std::vector<command> generatedCode;
    u_int64_t currentLine;
    int64_t labelCounter;
};