#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>

struct Variable {
    std::string name;
    std::string scope;
    bool isInitialized = false;
    int64_t memoryPosition;
    bool isArgument = false;
};

// Struktura dla tablic
struct Array {
    std::string name;
    std::string scope;
    std::unordered_map<int64_t, int64_t> memoryPositions;
    std::unordered_map<int64_t, bool> isInitialized ;
    int64_t startIndex;                               
    int64_t endIndex;         
    int64_t memoryPosition;
    bool isArgument = false;
};

// Klasa bazowa dla parametrów
struct Param {
    virtual ~Param() = default;
};

// Klasa dla parametrów zmiennych
struct VariableParam : Param {
    Variable variable;
};

// Klasa dla parametrów tablic
struct ArrayParam : Param {
    Array array;
};

struct Procedure {
    std::string name;
    std::vector<std::shared_ptr<Param>> params;
    std::string scope;
    int64_t jumpLabel;
    int64_t returnLabel;
    Variable returnVariable;
};

class SymbolTable {
public:
    std::string iterator = "";
    bool one = false;
    SymbolTable() : currentMemoryPosition (11) {}
    // Dodawanie zmiennych, procedur i tablic
    void addVariable(const std::string& name, const std::string& scope);
    void addVariable(Variable variable);
    void addArray(const std::string& name, const std::string& scope, int64_t startIndex, int64_t endIndex);
    void addArray(Array array);
    void addProcedure(const std::string& name, const std::string& scope, const std::vector<std::shared_ptr<Param>>& params);
    void addProcedureParam(const std::string& procedureName, const std::string& scope, std::shared_ptr<Param> param);

    // Pobieranie zmiennych, procedur i tablic
    Variable* getVariable(const std::string& name, const std::string& scope);
    Array* getArray(const std::string& name, const std::string& scope);
    Procedure* getProcedure(const std::string& name, const std::string& scope);

    void removeVariable(const std::string& name, const std::string& scope);
    void removeArray(const std::string& name, const std::string& scope);
    void removeProcedure(const std::string& name, const std::string& scope);
    void removeProcedureParam(const std::string& procedureName, const std::string& scope, const std::string& paramName);

    // Sprawdzanie, czy istnieje zmienna, tablica lub procedura o podanej nazwie w danym zakresie
    bool variableExists(const std::string& name, const std::string& scope);
    bool arrayExists(const std::string& name, const std::string& scope);
    bool procedureExists(const std::string& name, const std::string& scope);
    
    // Wyświetlanie zawartości
    void printVariables();
    void printArrays();
    void printProcedures();

    bool isVariableInProcedureParams(const std::string& procedureName, const std::string& scope, const std::string& variableName);
    bool isParamsTypeCorrect(const std::string& procedureName, const std::string& scope, const std::vector<std::string>& params);
private:
    std::unordered_map<std::string, Variable> variables;
    std::unordered_map<std::string, Array> arrays;
    std::unordered_map<std::string, Procedure> procedures;
    int64_t currentMemoryPosition ;
};

#endif // SYMBOL_TABLE_HPP
