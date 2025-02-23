#include "SymbolTable.hpp"
#include <algorithm>

// Dodanie zmiennej do tabeli symboli
void SymbolTable::addVariable(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope;
    if (variableExists(name, scope)) {
        throw std::runtime_error("Zmienna o tej nazwie już istnieje w tym zakresie!");
    }
    variables[key] = {name, scope, false, currentMemoryPosition++};
}

void SymbolTable::addVariable(Variable variable){
    std::string key = variable.name + ":" + variable.scope;
    if (variableExists(variable.name, variable.scope)) {
        throw std::runtime_error("Zmienna o tej nazwie już istnieje w tym zakresie!");
    }
    variables[key] = {variable.name, variable.scope, true, currentMemoryPosition++};
}

// Dodanie tablicy do tabeli symboli
void SymbolTable::addArray(const std::string& name, const std::string& scope, int64_t startIndex, int64_t endIndex) {
    std::string key = name + ":" + scope;
    if (arrayExists(name, scope)) {
        throw std::runtime_error("Tablica o tej nazwie już istnieje w tym zakresie!");
    }
    Array newArray = {name, scope, {},{},startIndex, endIndex};
    for (int64_t i = startIndex; i <= endIndex; ++i) {
        newArray.memoryPositions[i] = currentMemoryPosition++;
        newArray.isInitialized[i] = false;
        if (i == startIndex){
            newArray.memoryPosition = newArray.memoryPositions[i];
        }
    }
    arrays[key] = newArray;
}

void SymbolTable::addArray(Array array){
    std::string key = array.name + ":" + array.scope;
    if (arrayExists(array.name, array.scope)) {
        throw std::runtime_error("Tablica o tej nazwie już istnieje w tym zakresie!");
    }
    Array newArray = {array.name, array.scope, {},{},array.startIndex, array.endIndex};
    for (int64_t i = array.startIndex; i <= array.endIndex; ++i) {
        newArray.memoryPositions[i] = currentMemoryPosition++;
        newArray.isInitialized[i] = true;
        if (i == array.startIndex){
            newArray.memoryPosition = newArray.memoryPositions[i];
        }
    }
    arrays[key] = newArray;
}

// Dodanie procedury do tabeli symboli
void SymbolTable::addProcedure(const std::string& name, const std::string& scope, const std::vector<std::shared_ptr<Param>>& params) {
    std::string key = name + ":" + scope;
    if (procedureExists(name, scope)) {
        throw std::runtime_error("Procedura o tej nazwie już istnieje w tym zakresie!");
    }
    Procedure procedure;
    procedure.name = name;
    procedure.scope = scope;
    procedure.params = params;
    Variable returnVariable;
    returnVariable.name = "return";
    returnVariable.scope = scope;
    returnVariable.isInitialized = true;
    returnVariable.memoryPosition = currentMemoryPosition++;
    procedure.returnVariable = returnVariable;
    procedures[key] = procedure;
}

void SymbolTable::addProcedureParam(const std::string& procedureName, const std::string& scope, std::shared_ptr<Param> param) {
    std::string key = procedureName + ":" + scope;
    if (!procedureExists(procedureName, scope)) {
        throw std::runtime_error("Procedura o tej nazwie nie istnieje w tym zakresie!");
    }
    procedures[key].params.push_back(param);
}

// Pobieranie zmiennej z tabeli symboli
Variable* SymbolTable::getVariable(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope;
    auto it = variables.find(key);
    if (it != variables.end()) {
        return &it->second;
    }
    return nullptr;
}

// Pobieranie tablicy z tabeli symboli
Array* SymbolTable::getArray(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope;
    auto it = arrays.find(key);
    if (it != arrays.end()) {
        return &it->second;
    }
    return nullptr;
}

// Pobieranie procedury z tabeli symboli
Procedure* SymbolTable::getProcedure(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope;
    auto it = procedures.find(key);
    if (it != procedures.end()) {
        return &it->second;
    }
    return nullptr;
}

void SymbolTable::removeVariable(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope; 
    auto it = variables.find(key);
    if (it != variables.end()) {
        variables.erase(it);
    } else {
        throw std::runtime_error("Variable not found in the specified scope.");
    }
}

void SymbolTable::removeArray(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope; 
    auto it = arrays.find(key);
    if (it != arrays.end()) {
        arrays.erase(it);
    } else {
        throw std::runtime_error("Array not found in the specified scope.");
    }
}

void SymbolTable::removeProcedure(const std::string& name, const std::string& scope) {
    std::string key = name + ":" + scope; 
    auto it = procedures.find(key);
    if (it != procedures.end()) {
        procedures.erase(it);
    } else {
        throw std::runtime_error("Procedure not found in the specified scope.");
    }
}


// Sprawdzanie istnienia zmiennej
bool SymbolTable::variableExists(const std::string& name, const std::string& scope) {
    return variables.find(name + ":" + scope) != variables.end();
}

// Sprawdzanie istnienia tablicy
bool SymbolTable::arrayExists(const std::string& name, const std::string& scope) {
    return arrays.find(name + ":" + scope) != arrays.end();
}

// Sprawdzanie istnienia procedury
bool SymbolTable::procedureExists(const std::string& name, const std::string& scope) {
    return procedures.find(name + ":" + scope) != procedures.end();
}

// Wyświetlenie wszystkich zmiennych w tabeli symboli
void SymbolTable::printVariables() {
    std::cout << "ZMIENNE:\n";
    for (const auto& [key, variable] : variables) {
        std::cout << "Nazwa: " << variable.name
                  << ", Zakres: " << variable.scope
                  << ", Pozycja w pamięci: " << variable.memoryPosition
                  << ", Zainicjalizowana: " << (variable.isInitialized ? "TAK" : "NIE") 
                  << ", Argument: " << (variable.isArgument ? "TAK" : "NIE") << "\n";
    }
}

// Wyświetlenie wszystkich tablic w tabeli symboli
void SymbolTable::printArrays() {
    std::cout << "TABLICE:\n";
    for (const auto& [key, array] : arrays) {
        std::cout << "Nazwa: " << array.name
                  << ", Zakres: " << array.scope
                  << ", Zakres indeksów: [" << array.startIndex << ", " << array.endIndex << "]"
                  << ", Pozycja w pamięci: " << array.memoryPosition << "\n";
        for (int64_t i = array.startIndex; i <= array.endIndex; ++i) {
            std::cout << "  Indeks " << i
                    << ", Pozycja w pamięci: " << array.memoryPositions.at(i)
                    << ",  Zainicjalizowana: " << (array.isInitialized.at(i) ? "TAK" : "NIE") 
                    << ", Argument: " << (array.isArgument ? "TAK" : "NIE") << "\n";
        }
    }
}

// Wyświetlenie wszystkich procedur w tabeli symboli
void SymbolTable::printProcedures() {
    std::cout << "PROCEDURY:\n";
    for (const auto& [key, procedure] : procedures) {
        std::cout << "Nazwa: " << procedure.name
                  << ", Zakres: " << procedure.scope
                  << ", Parametry: [";
        for (size_t i = 0; i < procedure.params.size(); ++i) {
            if (auto varParam = std::dynamic_pointer_cast<VariableParam>(procedure.params[i])) {
                std::cout << varParam->variable.name << "(variable)";
            } else if (auto arrParam = std::dynamic_pointer_cast<ArrayParam>(procedure.params[i])) {
                std::cout << arrParam->array.name << "(array)";
            }
            if (i != procedure.params.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
}

bool SymbolTable::isVariableInProcedureParams(const std::string& procedureName, const std::string& scope, const std::string& variableName) {
    Procedure* procedure = getProcedure(procedureName, scope);
    if (procedure == nullptr) {
        return false;
    }
    for (const auto& param : procedure->params) {
        if (auto varParam = std::dynamic_pointer_cast<VariableParam>(param)) {
            if (varParam->variable.name == variableName) {
                return true;
            }
        }
        // Możemy również sprawdzić tablice, jeśli chcemy
        else if (auto arrParam = std::dynamic_pointer_cast<ArrayParam>(param)) {
            if (arrParam->array.name == variableName) {
                return true;
            }
        }
    }
    return false;
}

bool SymbolTable::isParamsTypeCorrect(const std::string& procedureName, const std::string& scope, const std::vector<std::string>& params) {
    Procedure* procedure = getProcedure(procedureName, "GLOBAL");
    if (procedure == nullptr) {
        return false;
    }
    if (procedure->params.size() != params.size()) {
        return false;
    }
    for (size_t i = 0; i < procedure->params.size(); ++i) {
        const std::string& paramName = params[i];
        if (variableExists(paramName, scope)) {
            auto variableParam = std::dynamic_pointer_cast<VariableParam>(procedure->params[i]);
            if (!variableParam) {
                return false;
            } 
        } else if (arrayExists(paramName, scope)) {
            auto arrayParam = std::dynamic_pointer_cast<ArrayParam>(procedure->params[i]);
            if (!arrayParam) {
                return false;
            } 
        } else {
            return false;
        }
    }
    return true;
}
