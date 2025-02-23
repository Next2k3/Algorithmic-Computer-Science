#include <iostream>
#include <fstream>
#include <unordered_set>
#include "AST.hpp"

extern int yyparse();
extern std::unique_ptr<ASTNode> root;
SymbolTable symbolTable;
CodeGenerator codeGenerator;

int main(int argc, char** argv) {
    if (argc < 3 ) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Could not open input file: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Could not open output file: " << argv[2] << std::endl;
        return 1;
    }

    extern FILE* yyin;
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        std::cerr << "Failed to open input file for parsing.\n";
        return 1;
    }

    if (yyparse() == 0 && root) {
        try{
            root->traverseAndAnalyze(symbolTable,"GLOBAL");
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }

        root->generateCode(codeGenerator, symbolTable, "GLOBAL");
        codeGenerator.saveToFile(argv[2]);
    } 
    return 0;
}
