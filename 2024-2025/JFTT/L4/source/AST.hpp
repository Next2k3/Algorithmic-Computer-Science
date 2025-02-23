#include <iostream>
#include <vector>
#include <memory>
#include "SymbolTable.hpp"
#include "CodeGenerator.hpp"

using namespace std;


class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
    virtual void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const {};
    virtual void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const {};
protected:
    void printIndent(int indent) const {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
    }
};

class ProcHeadNode : public ASTNode {
public:
    std::string pidentifier;
    
    ProcHeadNode(std::string pidentifier, std::unique_ptr<ASTNode> args_decl) 
        : pidentifier(std::move(pidentifier)), args_decl(std::move(args_decl)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ProcHeadNode\n";
        printIndent(indent);
        std::cout << "Pidentifier:" << pidentifier << "\n"; 
        
        printIndent(indent + 1);
        std::cout << "Args_decl:\n";
        if (args_decl) args_decl->print(indent + 2);  
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (args_decl) args_decl->traverseAndAnalyze(symbolTable, pidentifier);
    }
private:
    std::unique_ptr<ASTNode> args_decl;
};

class ProgramNode : public ASTNode {
public:
    ProgramNode(std::unique_ptr<ASTNode> procedures, std::unique_ptr<ASTNode> main)
        : procedures(std::move(procedures)), main(std::move(main)) {}

    void print(int indent = 0) const override {
        std::string indentStr(indent, ' ');
        std::cout << indentStr << "ProgramNode:" << std::endl;
        if (procedures) procedures->print(indent + 2);
        if (main) main->print(indent + 2);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (procedures) procedures->traverseAndAnalyze(symbolTable, "GLOBAL");
        if (main) main->traverseAndAnalyze(symbolTable, "MAIN");
    }
    
    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {

        if (procedures) {
            codeGenerator.emit("JUMP", 0);
            procedures->generateCode(codeGenerator, symbolTable, "GLOBAL");
        }
        int64_t mainLabel = codeGenerator.getCurrentLine();
        if (main) main->generateCode(codeGenerator, symbolTable, "MAIN");
        if (procedures && codeGenerator.getCommand(0).code == "JUMP"){
            codeGenerator.updateCommand(0, "JUMP", mainLabel);
        }
        codeGenerator.emit("HALT", 0);
    }
private:
    std::unique_ptr<ASTNode> procedures;
    std::unique_ptr<ASTNode> main;
};

class ProceduresNode : public ASTNode {
public:
    void addProcedure(std::unique_ptr<ASTNode> procedure) {
        procedures.push_back(std::move(procedure));
    }
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ProceduresNode\n";
        for (const auto& procedure : procedures) {
            procedure->print(indent + 1);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& procedure : procedures) {
            procedure->traverseAndAnalyze(symbolTable, scope);
        }
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& procedure : procedures) {
            procedure->generateCode(codeGenerator, symbolTable, scope);
        }
    }
private:
    std::vector<std::unique_ptr<ASTNode>> procedures;
};

class MainNode : public ASTNode {
public:
    MainNode(std::unique_ptr<ASTNode> declarations, std::unique_ptr<ASTNode> commands)
        : declarations(std::move(declarations)), commands(std::move(commands)) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "MainNode\n";
        if (declarations) declarations->print(indent + 1);
        if (commands) commands->print(indent + 1);
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (declarations) declarations->traverseAndAnalyze(symbolTable, scope);
        if (commands) commands->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (commands) commands->generateCode(codeGenerator, symbolTable, scope);
    }
private:
    std::unique_ptr<ASTNode> declarations;
    std::unique_ptr<ASTNode> commands;
};

class ProcedureNode : public ASTNode {
public:
    ProcedureNode(std::unique_ptr<ASTNode> procedures, std::unique_ptr<ProcHeadNode> name,
                  std::unique_ptr<ASTNode> declarations, std::unique_ptr<ASTNode> commands)
        : procedures(std::move(procedures)), proc_head(std::move(name)),
          declarations(std::move(declarations)), commands(std::move(commands)) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ProcedureNode: " << "\n";
        if (procedures) procedures->print(indent + 1);
        if (proc_head) proc_head->print(indent + 1);
        if (declarations) declarations->print(indent + 1);
        if (commands) commands->print(indent + 1);
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
       
        std::string newScope = scope;
        if (proc_head) {
              newScope = proc_head->pidentifier;
        }
        symbolTable.addProcedure(newScope, scope, {}); 
        if (procedures) procedures->traverseAndAnalyze(symbolTable, scope);
        if (proc_head) proc_head->traverseAndAnalyze(symbolTable, newScope);
        if (declarations) declarations->traverseAndAnalyze(symbolTable, newScope);
        if (commands) commands->traverseAndAnalyze(symbolTable, newScope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (procedures) procedures->generateCode(codeGenerator, symbolTable, scope);
        std::string newScope = scope;
        if (proc_head) {
            newScope = proc_head->pidentifier;
        }
        symbolTable.getProcedure(proc_head->pidentifier, scope)->jumpLabel = codeGenerator.getCurrentLine();
        if (commands) commands->generateCode(codeGenerator, symbolTable, newScope);
        codeGenerator.emit("RTRN", symbolTable.getProcedure(proc_head->pidentifier, scope)->returnVariable.memoryPosition);
    
    }
private:
    std::unique_ptr<ASTNode> procedures;
    std::unique_ptr<ProcHeadNode> proc_head;
    std::unique_ptr<ASTNode> declarations;
    std::unique_ptr<ASTNode> commands;
};

class CommandsNode : public ASTNode {
public:
    void addCommand(std::unique_ptr<ASTNode> command) {
        commands.push_back(std::move(command));
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "CommandsNode\n";
        for (const auto& command : commands) {
            command->print(indent + 1);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& command : commands) {
            command->traverseAndAnalyze(symbolTable, scope);
        }
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& command : commands) {
            command->generateCode(codeGenerator, symbolTable, scope);
        }
    }
private:
    std::vector<std::unique_ptr<ASTNode>> commands;
};

class IdentifierNode : public ASTNode {
public:
    enum IdentifierType {
        SIMPLE,
        INDEXED_ID,
        INDEXED_NUM
    };

    std::string getPidentifier() const {
        return pidentifier;
    }

    IdentifierNode(std::string identifier)
        : identifierType(SIMPLE), pidentifier(std::move(identifier)) {}

    IdentifierNode(std::string identifier, int64_t index)
        : identifierType(INDEXED_NUM), pidentifier(std::move(identifier)), index(index) {}

    IdentifierNode(std::string identifier, std::string index)
        : identifierType(INDEXED_ID), pidentifier(std::move(identifier)), indexIdentifier(index) {}


    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "IdentifierNode (" << pidentifier << ")";
        if (identifierType == INDEXED_ID) {
            std::cout << " [Indexed with Identifier]";
        } else if (identifierType == INDEXED_NUM) {
            std::cout << " [Indexed with Number]";
        }
        std::cout << "\n";
    }

    bool isInitialized(SymbolTable& symbolTable, const std::string& scope) const {
        switch (identifierType)
        {
        case SIMPLE:
            if (symbolTable.variableExists(pidentifier, scope)) {
                if (symbolTable.getVariable(pidentifier, scope)->isArgument) {
                    return true;
                }
                return symbolTable.getVariable(pidentifier, scope)->isInitialized;
            }
        case INDEXED_ID:
            return true;
        case INDEXED_NUM:
            if (symbolTable.arrayExists(pidentifier, scope)) {
                if (symbolTable.getArray(pidentifier, scope)->isArgument) {
                    return true;
                }
                if (index < symbolTable.getArray(pidentifier, scope)->startIndex || index > symbolTable.getArray(pidentifier, scope)->endIndex) {
                    std::cerr << "Error: Index out of bounds for array " << pidentifier << " in scope " << scope << "\n";
                    return false;
                }
                return symbolTable.getArray(pidentifier, scope)->isInitialized[index];
            }
        default:
            return false;
        }
    }
    
    void setInitialized(SymbolTable& symbolTable, const std::string& scope) const {
        switch (identifierType)
        {
        case SIMPLE:
            symbolTable.getVariable(pidentifier, scope)->isInitialized = true;
            break;
        case INDEXED_ID:
            if(!symbolTable.arrayExists(pidentifier, scope)){
                std::cerr << "Error: Array " << pidentifier << " not declared in scope " << scope << "\n";
            }
            if(!symbolTable.variableExists(indexIdentifier, scope)){
                std::cerr << "Error: Variable " << indexIdentifier << " not declared in scope " << scope << "\n";
            }
            if(!symbolTable.getVariable(indexIdentifier, scope)->isInitialized){
                std::cerr << "Error: Variable " << indexIdentifier << " not initialized in scope " << scope << "\n";
            }
            break;
        case INDEXED_NUM:
            if (symbolTable.arrayExists(pidentifier, scope)) {
                if (symbolTable.getArray(pidentifier, scope)->isArgument) {
                    return;
                }
                if (index < symbolTable.getArray(pidentifier, scope)->startIndex || index > symbolTable.getArray(pidentifier, scope)->endIndex) {
                    std::cerr << "Error: Index out of bounds for array " << pidentifier << " in scope " << scope << "\n";
                }
                symbolTable.getArray(pidentifier, scope)->isInitialized[index] = true;
            }
            break;
        default:
            break;
        }
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        switch (identifierType)
        {
        case SIMPLE:
            if(!symbolTable.variableExists(pidentifier, scope)){
                throw std::runtime_error("Variable "+ pidentifier+ " not declared in scope " + scope);
            }
            break;
        case INDEXED_ID:
            
            if(!symbolTable.arrayExists(pidentifier, scope)){
                throw std::runtime_error("Array "+ pidentifier+ " not declared in scope " + scope);
            }
            if(!symbolTable.variableExists(indexIdentifier, scope)){
                throw std::runtime_error("Variable "+ indexIdentifier+ " not declared in scope " + scope);
            }
            break;
        case INDEXED_NUM:
            if(!symbolTable.arrayExists(pidentifier, scope)){
                throw std::runtime_error("Array "+ pidentifier+ " not declared in scope " + scope);
            }
            if(!symbolTable.getArray(pidentifier, scope)->isArgument){
                if (index < symbolTable.getArray(pidentifier, scope)->startIndex || index > symbolTable.getArray(pidentifier, scope)->endIndex) {
                    throw std::runtime_error("Error: Index out of bounds for array " + pidentifier + " in scope " + scope);
                }
            }
            break;
        default:
            break;
        }
    }

    std::int64_t getMemoryPosition(SymbolTable& symbolTable, const std::string& scope) const {
        int64_t memoryPosition;
        switch (identifierType)
        {
        case SIMPLE:
            return symbolTable.getVariable(pidentifier, scope)->memoryPosition;
        case INDEXED_ID:
            return -1;
        case INDEXED_NUM:
            memoryPosition = symbolTable.getArray(pidentifier, scope)->memoryPosition;
            return memoryPosition + (index-symbolTable.getArray(pidentifier, scope)->startIndex);
        default:
            return -1;
        }
        return -1;
    }

    std::int64_t getStartMemoryPosition(SymbolTable& symbolTable, const std::string& scope) const {
        switch (identifierType)
        {
        case SIMPLE:
            return symbolTable.getVariable(pidentifier, scope)->memoryPosition;
        case INDEXED_ID:
            return symbolTable.getArray(pidentifier, scope)->memoryPosition;
        case INDEXED_NUM:
            return symbolTable.getArray(pidentifier, scope)->memoryPosition;
        default:
            return -1;
        }
        return -1;
    }

    IdentifierNode::IdentifierType getIdentifierType() const {
        return identifierType;
    }
    
    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {  
        int64_t memoryPosition;
        int64_t indexMemoryPosition;
        bool isArgument;
        switch (identifierType)
        {
        case SIMPLE:
            codeGenerator.emit("LOAD", symbolTable.getVariable(pidentifier, scope)->memoryPosition);     
            break;
        case INDEXED_ID:
            memoryPosition = symbolTable.getArray(pidentifier, scope)->memoryPosition;
            indexMemoryPosition = symbolTable.getVariable(indexIdentifier, scope)->memoryPosition;
            isArgument = symbolTable.getArray(pidentifier, scope)->isArgument;
            if (!isArgument){
                codeGenerator.emit("SET", memoryPosition - symbolTable.getArray(pidentifier, scope)->startIndex);
                codeGenerator.emit("ADD", indexMemoryPosition);
                codeGenerator.emit("LOADI", 0);
            } else {
                codeGenerator.emit("LOAD", indexMemoryPosition);
                codeGenerator.emit("ADD", memoryPosition);
                codeGenerator.emit("LOADI", 0);
            }
            break;
        case INDEXED_NUM:
            memoryPosition = symbolTable.getArray(pidentifier, scope)->memoryPosition;
            isArgument = symbolTable.getArray(pidentifier, scope)->isArgument;
            if (!isArgument){
                codeGenerator.emit("LOAD", memoryPosition + (index-symbolTable.getArray(pidentifier, scope)->startIndex));
            } else {
                codeGenerator.emit("SET", index);
                codeGenerator.emit("ADD", memoryPosition);
                codeGenerator.emit("LOADI", 0);
            }
             break;
        default:
            break;
        }
    }

    
    int64_t getIndex() const {
        return index;
    }
    
    std::string getIndexIdentifier() const {
        return indexIdentifier;
    }

    IdentifierType identifierType;
private:
    std::string pidentifier;
    int64_t index;
    std::string indexIdentifier;
};

class ValueNode : public ASTNode {
public:
    bool isIdentifier;

    ValueNode(int64_t value) 
        : isIdentifier(false),value(value) {}

    ValueNode(std::unique_ptr<ASTNode> identifierNode) 
        : isIdentifier(true), identifierNode(std::move(identifierNode)) {}

    void print(int indent = 0) const override {
        printIndent(indent);
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (isIdentifier) {
            if (identifierNode) {
                identifierNode->traverseAndAnalyze(symbolTable, scope);
            }
        }
    }

    bool isVariableInitialized(SymbolTable& symbolTable, const std::string& scope) const {
        if (isIdentifier) {
            if (identifierNode) {
                auto idNode = dynamic_cast<IdentifierNode*>(identifierNode.get());
                if(idNode){
                    if (idNode->isInitialized(symbolTable, scope)) {
                        return true;
                    }
                return false;
                }
            }
        } 
        return true;
    }

    std::string getPidentifier() const {
        if (isIdentifier) {
            auto idNode = dynamic_cast<IdentifierNode*>(identifierNode.get());
            if (idNode) {
                return idNode->getPidentifier();
            }
        }
        return "";
    }

    int64_t getValue() const {
        if(isIdentifier){
            return 0;
        }
        return value;
    }

    int64_t getMemoryPosition(SymbolTable& symbolTable, const std::string& scope) const {
        if (isIdentifier) {
            if (identifierNode) {
                auto idNode = dynamic_cast<IdentifierNode*>(identifierNode.get());
                if (idNode) {
                    return idNode->getMemoryPosition(symbolTable, scope);
                }
            }
        }
        return -1;
    }
    
    IdentifierNode* getIdentifierNode() const {
        return dynamic_cast<IdentifierNode*>(identifierNode.get());
    }
   
    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (isIdentifier) {
            if (identifierNode) {
                auto idNode = dynamic_cast<IdentifierNode*>(identifierNode.get());
                if (idNode ) {
                    idNode->generateCode(codeGenerator, symbolTable, scope);
                }
            }
        } else {
            codeGenerator.emit("SET", value);
        }
    }
private:
    int64_t value;
    mutable std::unique_ptr<ASTNode>  identifierNode;
};

class ExpressionNode : public ASTNode {
public:
    ExpressionNode(std::unique_ptr<ASTNode> leftValue, std::string op, std::unique_ptr<ASTNode> rightValue)
        : leftValue(std::move(leftValue)), op(std::move(op)), rightValue(std::move(rightValue)) {

        }
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ExpressionNode\n";
        printIndent(indent + 1);
        std::cout << "LeftValue:\n";
        if (leftValue) {
            leftValue->print(indent + 2);  
        }
        printIndent(indent + 1);
        std::cout << "Operator: " << op << "\n";
        printIndent(indent + 1);
        std::cout << "RightValue:\n";
        if (rightValue) {
            rightValue->print(indent + 2);
        }
    }

    bool isVariablesInitialized(SymbolTable& symbolTable, const std::string& scope) const {
        if (leftValue) {
            auto leftIdNode = dynamic_cast<ValueNode*>(leftValue.get());
            if (leftIdNode) {
                if (!leftIdNode->isVariableInitialized(symbolTable, scope)) {
                    throw std::runtime_error("Error: Variable is not initialized in scope " + scope);
                    return false;
                }
            }
        }
        if (rightValue) {
            auto rightIdNode = dynamic_cast<ValueNode*>(rightValue.get());
            if (rightIdNode) {
                if (!rightIdNode->isVariableInitialized(symbolTable, scope)) {
                    throw std::runtime_error("Error: Variable is not initialized in scope " + scope);
                    return false;
                }
            }
        }
        return true;
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (leftValue) leftValue->traverseAndAnalyze(symbolTable, scope);
        if (rightValue) rightValue->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        auto leftIdNode = dynamic_cast<ValueNode*>(leftValue.get());
        auto rightIdNode = dynamic_cast<ValueNode*>(rightValue.get());
        if (leftIdNode->isIdentifier && rightIdNode->isIdentifier) {
            int64_t leftMemoryPosition = leftIdNode->getMemoryPosition(symbolTable, scope);
            int64_t rightMemoryPosition = rightIdNode->getMemoryPosition(symbolTable, scope);
            auto leftId = leftIdNode->getIdentifierNode();
            auto rightId = rightIdNode->getIdentifierNode();
            if (!leftId->identifierType == IdentifierNode::IdentifierType::SIMPLE ){
                leftIdNode->generateCode(codeGenerator, symbolTable, scope);
                codeGenerator.emit("STORE", 6);
                leftMemoryPosition = 6;
            }
            if(!rightId->identifierType == IdentifierNode::IdentifierType::SIMPLE){
                rightIdNode->generateCode(codeGenerator, symbolTable, scope);
                codeGenerator.emit("STORE", 7);
                rightMemoryPosition = 7;
            }
            
            if(op == "+"){
                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("ADD", rightMemoryPosition);
            }
            if (op == "-"){
                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("SUB", rightMemoryPosition);
            }
            if (op == "*"){
                int64_t one;
                if(symbolTable.one){
                    one = 0;
                }else {
                    one = 1;
                }
                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("JZERO", 46 + one);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("STORE", 1);   
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JZERO", 40 + one);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("STORE", 2);
                codeGenerator.emit("SUB", 0);
                codeGenerator.emit("STORE", 3);             
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("JPOS", 2);
                if (one == 1){
                    codeGenerator.emit("JUMP", 20);
                } else {
                    codeGenerator.emit("JUMP", 19);
                }
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("ADD", 0);
                codeGenerator.emit("SUB", 2);
                codeGenerator.emit("STORE", 5);
                if (symbolTable.one){
                    codeGenerator.emit("LOAD", 10);
                } else {
                    codeGenerator.emit("SET", 1);
                    codeGenerator.emit("STORE", 10);
                    symbolTable.one = true;
                }
                codeGenerator.emit("ADD", 5);
                codeGenerator.emit("JZERO", 2);
                codeGenerator.emit("JUMP", 4);
                codeGenerator.emit("LOAD", 3);
                codeGenerator.emit("ADD", 1);
                codeGenerator.emit("STORE", 3);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("ADD", 1);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 2);
                if(one == 1){
                    codeGenerator.emit("JUMP", -21);
                } else {
                    codeGenerator.emit("JUMP", -20);
                }
                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("JPOS", 4);
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JNEG", 8);
                codeGenerator.emit("JUMP",3);
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JPOS", 5);
                codeGenerator.emit("LOAD", 3);
                codeGenerator.emit("SUB", 3);
                codeGenerator.emit("SUB", 3);
                codeGenerator.emit("JUMP", 2);
                codeGenerator.emit("LOAD", 3);
            }
            if (op == "/"){
                int64_t one;
                if(symbolTable.one){
                    one = 0;
                }else {
                    one = 1;
                }

                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JZERO", 51+one);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("STORE",5);
                codeGenerator.emit("STORE",1);

                codeGenerator.emit("LOAD",leftMemoryPosition);
                codeGenerator.emit("JZERO", 45+one);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("STORE",4 );

                if (!symbolTable.one){
                    codeGenerator.emit("SET", 1);
                    codeGenerator.emit("STORE", 10);
                    symbolTable.one = true;
                } else {
                    codeGenerator.emit("LOAD", 10);
                }
                codeGenerator.emit("STORE",2);

                codeGenerator.emit("SUB", 0);
                codeGenerator.emit("STORE",3);

                codeGenerator.emit("LOAD", 4);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("JNEG", 8);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("ADD", 0);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("ADD", 0);
                codeGenerator.emit("STORE", 2);
                codeGenerator.emit("JUMP", -9);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 2);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 1);              
                codeGenerator.emit("LOAD", 4);
                codeGenerator.emit("SUB", 5);
                codeGenerator.emit("JNEG", 17);
                codeGenerator.emit("LOAD", 4);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("JNEG", 7);
                codeGenerator.emit("LOAD", 4);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("STORE", 4);
                codeGenerator.emit("LOAD", 3);
                codeGenerator.emit("ADD", 2);
                codeGenerator.emit("STORE", 3);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 2);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("JUMP", -18);

                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("JPOS", 4);
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JPOS", 4);
                codeGenerator.emit("JUMP", 7);
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JPOS", 5);
                codeGenerator.emit("LOAD", 3);
                codeGenerator.emit("SUB", 3);
                codeGenerator.emit("SUB", 3);
                codeGenerator.emit("JUMP", 2);
                codeGenerator.emit("LOAD", 3);
            }
            if (op == "%"){
                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JZERO", 43);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("SUB", rightMemoryPosition);
                codeGenerator.emit("STORE",3);
                codeGenerator.emit("STORE",1);

                codeGenerator.emit("LOAD",leftMemoryPosition);
                codeGenerator.emit("JZERO", 30);
                codeGenerator.emit("JPOS", 3);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("SUB", leftMemoryPosition);
                codeGenerator.emit("STORE",2 );

                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("JNEG", 5);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("ADD", 0);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("JUMP", -6);

                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 1);          

                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("SUB", 3);
                codeGenerator.emit("JNEG", 11);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("JNEG", 4);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("SUB", 1);
                codeGenerator.emit("STORE", 2);
                codeGenerator.emit("LOAD", 1);
                codeGenerator.emit("HALF", 0);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("JUMP", -12);

                codeGenerator.emit("LOAD", rightMemoryPosition);
                codeGenerator.emit("JPOS", 5);
                codeGenerator.emit("LOAD", 2);
                codeGenerator.emit("SUB", 2);
                codeGenerator.emit("SUB", 2);
                codeGenerator.emit("JUMP", 2);
                codeGenerator.emit("LOAD", 2);
            }
        } else if (leftIdNode->isIdentifier && !rightIdNode->isIdentifier) {
            int64_t leftMemoryPosition = leftIdNode->getMemoryPosition(symbolTable, scope);
            int64_t rightValue = rightIdNode->getValue();
            auto leftId = leftIdNode->getIdentifierNode();
            if (!leftId->identifierType == IdentifierNode::IdentifierType::SIMPLE ){
                leftIdNode->generateCode(codeGenerator, symbolTable, scope);
                codeGenerator.emit("STORE", 6);
                leftMemoryPosition = 6;
            }

            if(op == "+"){
                codeGenerator.emit("SET", rightValue);
                codeGenerator.emit("ADD", leftMemoryPosition);
            }
            if (op == "-"){
                codeGenerator.emit("SET", rightValue);
                codeGenerator.emit("STORE", 1);
                codeGenerator.emit("LOAD", leftMemoryPosition);
                codeGenerator.emit("SUB", 1);
            }
            if (op == "*"){
                if (rightValue==0) {
                    codeGenerator.emit("SUB", 0);
                } else if (rightValue%2==0){
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                    while(rightValue!=-1 && rightValue!=1){
                        codeGenerator.emit("ADD", 0);
                        rightValue = rightValue/2;
                    }
                } else {
                    int64_t one;
                    if(symbolTable.one){
                        one = 0;
                    }else {
                        one = 1;
                    }
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                    codeGenerator.emit("JZERO", 37 + one);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("STORE", 1);   
                    if(rightValue<0){
                        codeGenerator.emit("SET", -rightValue);
                        codeGenerator.emit("STORE", 2);
                    } else {
                        codeGenerator.emit("SET", rightValue);
                        codeGenerator.emit("STORE",2);
                    }
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("STORE", 3);             
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("JPOS", 2);
                    if (one == 1){
                        codeGenerator.emit("JUMP", 20);
                    } else {
                        codeGenerator.emit("JUMP", 19);
                    }
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("SUB", 2);
                    codeGenerator.emit("STORE", 5);
                    if (symbolTable.one){
                        codeGenerator.emit("LOAD", 10);
                    } else {
                        codeGenerator.emit("SET", 1);
                        codeGenerator.emit("STORE", 10);
                        symbolTable.one = true;
                    }
                    codeGenerator.emit("ADD", 5);
                    codeGenerator.emit("JZERO", 2);
                    codeGenerator.emit("JUMP", 4);
                    codeGenerator.emit("LOAD", 3);
                    codeGenerator.emit("ADD", 1);
                    codeGenerator.emit("STORE", 3);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 1);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);
                    if(one == 1){
                        codeGenerator.emit("JUMP", -21);
                    } else {
                        codeGenerator.emit("JUMP", -20);
                    }
                    if(rightValue>0){
                        codeGenerator.emit("LOAD", leftMemoryPosition);
                        codeGenerator.emit("JPOS", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    } else {
                        codeGenerator.emit("LOAD", leftMemoryPosition);
                        codeGenerator.emit("JPOS", 3);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                    }
                }
            }
            if (op == "/"){
                int64_t one;
                if(symbolTable.one){
                    one = 0;
                }else {
                    one = 1;
                }
                if (rightValue == 0){
                    codeGenerator.emit("SUB", 0);
                } else if (rightValue == 1) {
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                } else if (rightValue == -1) {
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                }else if (rightValue == 2) {
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                    codeGenerator.emit("HALF", 0);
                } else if (rightValue == -2) {
                    codeGenerator.emit("LOAD", leftMemoryPosition);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("HALF", 0);
                } else {
                    if (rightValue<0){
                        codeGenerator.emit("SET", -rightValue);
                        codeGenerator.emit("STORE", 1);
                        codeGenerator.emit("STORE", 5);
                    } else {
                        codeGenerator.emit("SET", rightValue);
                        codeGenerator.emit("STORE",1);
                        codeGenerator.emit("STORE",5);
                    }
                    codeGenerator.emit("LOAD",leftMemoryPosition);
                    codeGenerator.emit("JZERO", 41+one);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("STORE",4 );
                    if (!symbolTable.one){
                        codeGenerator.emit("SET", 1);
                        codeGenerator.emit("STORE", 10);
                        symbolTable.one = true;
                    } else {
                        codeGenerator.emit("LOAD", 10);
                    }
                    codeGenerator.emit("STORE",2);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("STORE",3);

                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 8);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("JUMP", -9);

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);

                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 5);
                    codeGenerator.emit("JNEG", 17);
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 7);
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("STORE", 4);
                    codeGenerator.emit("LOAD", 3);
                    codeGenerator.emit("ADD", 2);
                    codeGenerator.emit("STORE", 3);

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -18);

                    if (rightValue > 0){
                        codeGenerator.emit("LOAD", leftMemoryPosition);
                        codeGenerator.emit("JPOS", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    } else {
                        codeGenerator.emit("LOAD", leftMemoryPosition);
                        codeGenerator.emit("JNEG", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    }
                }
            }
            if (op == "%"){
                if (rightValue == 0 || rightValue == 1 || rightValue == -1){
                    codeGenerator.emit("SUB", 0);
                } else {  
                    if (rightValue<0){
                        codeGenerator.emit("SET", -rightValue);
                        codeGenerator.emit("STORE", 1);
                        codeGenerator.emit("STORE", 3);
                    } else {
                        codeGenerator.emit("SET", rightValue);
                        codeGenerator.emit("STORE",1);
                        codeGenerator.emit("STORE",3);
                    }

                    codeGenerator.emit("LOAD",leftMemoryPosition);
                    codeGenerator.emit("JZERO", 30);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("SUB", leftMemoryPosition);
                    codeGenerator.emit("STORE",2 );

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 5);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -6);

                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);          

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 3);
                    codeGenerator.emit("JNEG", 11);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 4);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -12);

                    if(rightValue>0){
                        codeGenerator.emit("LOAD", 2);
                    } else {
                        codeGenerator.emit("LOAD", 2);
                        codeGenerator.emit("SUB", 2);
                        codeGenerator.emit("SUB", 2);
                    }
                }
            }
        } else if (!leftIdNode->isIdentifier && rightIdNode->isIdentifier) {
            int64_t rightMemoryPosition = rightIdNode->getMemoryPosition(symbolTable, scope);
            int64_t leftValue = leftIdNode->getValue();
            auto rightId = rightIdNode->getIdentifierNode();
            if(!rightId->identifierType == IdentifierNode::IdentifierType::SIMPLE){
                rightIdNode->generateCode(codeGenerator, symbolTable, scope);
                codeGenerator.emit("STORE", 7);
                rightMemoryPosition = 7;
            }

            if(op == "+"){
                codeGenerator.emit("SET", leftValue);
                codeGenerator.emit("ADD", rightMemoryPosition);
            }
            if (op == "-"){
                codeGenerator.emit("SET", leftValue);
                codeGenerator.emit("SUB", rightMemoryPosition);
            }
            if (op == "*"){
                if (leftValue==0) {
                    codeGenerator.emit("SET", 0);
                } else if (leftValue%2==0){
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    while(leftValue!=-1 && leftValue!=1){
                        codeGenerator.emit("ADD", 0);
                        leftValue = leftValue/2;
                    }
                } else {
                    int64_t one;
                    if(symbolTable.one){
                        one = 0;
                    }else {
                        one = 1;
                    }
                    codeGenerator.emit("SET", leftValue);
                    codeGenerator.emit("STORE", 1);   
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("JZERO", 35 + one);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("STORE", 3);             
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("JPOS", 2);
                    if (one == 1){
                        codeGenerator.emit("JUMP", 20);
                    } else {
                        codeGenerator.emit("JUMP", 19);
                    }
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("SUB", 2);
                    codeGenerator.emit("STORE", 5);
                    if (symbolTable.one){
                        codeGenerator.emit("LOAD", 10);
                    } else {
                        codeGenerator.emit("SET", 1);
                        codeGenerator.emit("STORE", 10);
                        symbolTable.one = true;
                    }
                    codeGenerator.emit("ADD", 5);
                    codeGenerator.emit("JZERO", 2);
                    codeGenerator.emit("JUMP", 4);
                    codeGenerator.emit("LOAD", 3);
                    codeGenerator.emit("ADD", 1);
                    codeGenerator.emit("STORE", 3);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 1);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);
                    if(one == 1){
                        codeGenerator.emit("JUMP", -21);
                    } else {
                        codeGenerator.emit("JUMP", -20);
                    }
                    if(leftValue>0){
                        codeGenerator.emit("LOAD", rightMemoryPosition);
                        codeGenerator.emit("JPOS", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    } else {
                        codeGenerator.emit("LOAD", rightMemoryPosition);
                        codeGenerator.emit("JPOS", 3);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("JUMP", 4);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                    }
                }
            }
            if (op == "/"){
                int64_t one;
                if(symbolTable.one){
                    one = 0;
                }else {
                    one = 1;
                }
                if (leftValue == 0){
                    codeGenerator.emit("SUB", 0);
                } else if (leftValue == 1) {
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                } else if (leftValue == -1) {
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                } else if (leftValue == 2) {
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("HALF", 0);
                } else if (leftValue == -2) {
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("HALF", 0);
                } else { 

                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("JZERO", 54+one);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("STORE",1);
                    codeGenerator.emit("STORE",5);

                    if (leftValue < 0){
                        codeGenerator.emit("SET", -leftValue);
                        codeGenerator.emit("STORE",4);   
                    } else {
                        codeGenerator.emit("SET", leftValue);
                        codeGenerator.emit("STORE",4);
                    }
                    if(!symbolTable.one){
                        codeGenerator.emit("SET", 1);
                        codeGenerator.emit("STORE",10);
                        symbolTable.one = true;
                    } else {
                        codeGenerator.emit("LOAD", 10);
                    }
                    codeGenerator.emit("STORE",2);
                    codeGenerator.emit("SUB", 0);
                    codeGenerator.emit("STORE",3);

                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 8);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("JUMP", -9);

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);

                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 5);
                    codeGenerator.emit("JNEG", 17);
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 7);
                    codeGenerator.emit("LOAD", 4);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("STORE", 4);
                    codeGenerator.emit("LOAD", 3);
                    codeGenerator.emit("ADD", 2);
                    codeGenerator.emit("STORE", 3);

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -18);

                    if ( leftValue > 0){
                        codeGenerator.emit("LOAD", rightMemoryPosition);
                        codeGenerator.emit("JPOS", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    } else {
                        codeGenerator.emit("LOAD", rightMemoryPosition);
                        codeGenerator.emit("JNEG", 5);
                        codeGenerator.emit("LOAD", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("SUB", 3);
                        codeGenerator.emit("JUMP", 2);
                        codeGenerator.emit("LOAD", 3);
                    }
                }
            }
            if (op == "%"){
                if (leftValue == 0){
                    codeGenerator.emit("SET", 0);
                } else {
                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("JZERO", 39);
                    codeGenerator.emit("JPOS", 3);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("SUB", rightMemoryPosition);
                    codeGenerator.emit("STORE",3);
                    codeGenerator.emit("STORE",1);

                    if ( leftValue<0){
                        codeGenerator.emit("SET", -leftValue);
                        codeGenerator.emit("STORE",2);   
                    } else {
                        codeGenerator.emit("SET", leftValue);
                        codeGenerator.emit("STORE",2);
                    }

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 5);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("ADD", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -6);

                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);          

                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 3);
                    codeGenerator.emit("JNEG", 11);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("JNEG", 4);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 1);
                    codeGenerator.emit("STORE", 2);
                    codeGenerator.emit("LOAD", 1);
                    codeGenerator.emit("HALF", 0);
                    codeGenerator.emit("STORE", 1);
                    codeGenerator.emit("JUMP", -12);

                    codeGenerator.emit("LOAD", rightMemoryPosition);
                    codeGenerator.emit("JPOS", 5);
                    codeGenerator.emit("LOAD", 2);
                    codeGenerator.emit("SUB", 2);
                    codeGenerator.emit("SUB", 2);
                    codeGenerator.emit("JUMP", 2);
                    codeGenerator.emit("LOAD", 2);
                }
            }

        } else {
            int64_t leftValue = leftIdNode->getValue();
            int64_t rightValue = rightIdNode->getValue();

            if(op == "+"){
                if(leftValue-rightValue==0){
                    codeGenerator.emit("SUB", 0);
                } else {
                    codeGenerator.emit("SET", leftValue + rightValue);
                }
            }
            if (op == "-"){
                if (leftValue-rightValue==0){
                    codeGenerator.emit("SUB", 0);
                } else {
                    codeGenerator.emit("SET", leftValue - rightValue);
                }
            }
            if (op == "*"){
                if (leftValue*rightValue==0){
                    codeGenerator.emit("SUB", 0);
                } else {
                    codeGenerator.emit("SET", leftValue * rightValue);
                }
            }
            if (op == "/"){
                if (rightValue == 0){
                    codeGenerator.emit("SUB", 0);
                } else if (rightValue < 0 && leftValue > 0 && leftValue / rightValue > 0) {
                    codeGenerator.emit("SET", -(leftValue / rightValue));
                }else{
                    codeGenerator.emit("SET", leftValue / rightValue);
                }
            }
            if (op == "%"){
                if (rightValue == 0){
                    codeGenerator.emit("SUB", 0);
                } else if (leftValue % rightValue != 0 && ((rightValue<0) != (leftValue%rightValue<0))){
                    codeGenerator.emit("SET", (leftValue % rightValue)+rightValue);
                } else {
                    codeGenerator.emit("SET", leftValue % rightValue);
                }

            }
        }
    }

private:
    std::unique_ptr<ASTNode> leftValue;
    std::string op;
    std::unique_ptr<ASTNode> rightValue;
};

class AssignmentNode : public ASTNode {
public:
    AssignmentNode(std::unique_ptr<ASTNode> identifier, std::unique_ptr<ASTNode> expression)
        : identifier(std::move(identifier)), expression(std::move(expression)) {}
  
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "AssignmentNode\n";
        if (identifier) identifier->print(indent + 1);
        if (expression) expression->print(indent + 1);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (identifier) {
            auto idNode = dynamic_cast<IdentifierNode*>(identifier.get());
            if (idNode) {
                std::string pidentifier = idNode->getPidentifier();
                if(pidentifier == symbolTable.iterator && pidentifier != ""){
                    throw std::runtime_error("Error: Cannot assign value to iterator " + pidentifier + " in scope " + scope);
                }
            }
        }
        if (identifier) identifier->traverseAndAnalyze(symbolTable, scope);
        if (expression) expression->traverseAndAnalyze(symbolTable, scope);

        if (expression && identifier) {
            auto idNode = dynamic_cast<IdentifierNode*>(identifier.get());
            auto exprNode = dynamic_cast<ExpressionNode*>(expression.get());
            if (exprNode && idNode) {
                if(exprNode->isVariablesInitialized(symbolTable, scope)){
                    idNode->setInitialized(symbolTable, scope);
                }
            }
            auto exprNode2 = dynamic_cast<ValueNode*>(expression.get());
            if (exprNode2 && idNode){
                if(exprNode2->isVariableInitialized(symbolTable, scope)){
                    idNode->setInitialized(symbolTable, scope);
                }
            } 
        }
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
            if (identifier && expression) {
                auto idNode = dynamic_cast<IdentifierNode*>(identifier.get());
                int64_t memoryPosition;
                int64_t indexMemoryPosition; 
                bool isArgument;
                switch(idNode->getIdentifierType()){
                    case IdentifierNode::IdentifierType::SIMPLE:
                        expression->generateCode(codeGenerator, symbolTable, scope);
                        codeGenerator.emit("STORE", idNode->getMemoryPosition(symbolTable, scope));
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_NUM:
                        isArgument = symbolTable.getArray(idNode->getPidentifier(), scope)->isArgument;
                        if (!isArgument){
                            expression->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("STORE", idNode->getMemoryPosition(symbolTable, scope));
                        } else{
                            memoryPosition = symbolTable.getArray(idNode->getPidentifier(), scope)->memoryPosition;
                            codeGenerator.emit("SET", idNode->getIndex());
                            codeGenerator.emit("ADD", memoryPosition);
                            codeGenerator.emit("STORE", 8);
                            expression->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("STOREI", 8);
                        }
                        
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_ID:
                        isArgument = symbolTable.getArray(idNode->getPidentifier(), scope)->isArgument; 
                        if (!isArgument){
                            memoryPosition = symbolTable.getArray(idNode->getPidentifier(), scope)->memoryPosition;
                            indexMemoryPosition = symbolTable.getVariable(idNode->getIndexIdentifier(),scope)->memoryPosition;
                            codeGenerator.emit("SET", memoryPosition);
                            codeGenerator.emit("ADD", indexMemoryPosition);
                            codeGenerator.emit("STORE", 8);
                            expression->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("STOREI", 8);
                        } else {
                            memoryPosition = symbolTable.getArray(idNode->getPidentifier(), scope)->memoryPosition;
                            indexMemoryPosition = symbolTable.getVariable(idNode->getIndexIdentifier(),scope)->memoryPosition;
                            codeGenerator.emit("LOAD", memoryPosition);
                            codeGenerator.emit("ADD", indexMemoryPosition);
                            codeGenerator.emit("STORE", 8);
                            expression->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("STOREI", 8);
                        }
                        break;
                }
            }
    }
private:
    std::unique_ptr<ASTNode> identifier;
    std::unique_ptr<ASTNode> expression;
};

class IfNode : public ASTNode {
public:
    IfNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> truecommands, std::unique_ptr<ASTNode> falsecommands) 
        : condition(std::move(condition)), truecommands(std::move(truecommands)), falsecommands(std::move(falsecommands)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "IfNode:" << std::endl;
        condition->print(indent + 2);
        truecommands->print(indent + 2);
        if (falsecommands) {
            printIndent(indent);
            std::cout << "Else:" << std::endl;
            falsecommands->print(indent + 2);
        }
    }

    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (condition) condition->traverseAndAnalyze(symbolTable, scope);
        if (truecommands) truecommands->traverseAndAnalyze(symbolTable, scope);
        if (falsecommands) falsecommands->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (condition && truecommands && falsecommands){
            condition->generateCode(codeGenerator, symbolTable, scope);
            int64_t jump = codeGenerator.getCurrentLine()-1;
            command cond = codeGenerator.getCommand(jump);
            if (cond.arg == 1){
                falsecommands->generateCode(codeGenerator, symbolTable, scope); 
                int64_t jump2 = codeGenerator.getCurrentLine();

                codeGenerator.updateCommand(jump, cond.code, jump2-jump+1);
                codeGenerator.emit("JUMP", 0);

                truecommands->generateCode(codeGenerator, symbolTable, scope); 
                int64_t jump3 = codeGenerator.getCurrentLine();

                cond = codeGenerator.getCommand(jump2);
                codeGenerator.updateCommand(jump2, cond.code, jump3-jump2);
            }
            if (cond.arg == 2){
                truecommands->generateCode(codeGenerator, symbolTable, scope); 
                int64_t jump2 = codeGenerator.getCurrentLine();

                codeGenerator.updateCommand(jump, cond.code, jump2-jump+1);
                codeGenerator.emit("JUMP", 0);

                falsecommands->generateCode(codeGenerator, symbolTable, scope); 
                int64_t jump3 = codeGenerator.getCurrentLine();

                cond = codeGenerator.getCommand(jump2);
                codeGenerator.updateCommand(jump2, cond.code, jump3-jump2);
            }
        } else {
            condition->generateCode(codeGenerator, symbolTable, scope);
            int64_t jump = codeGenerator.getCurrentLine()-1;
            command cond = codeGenerator.getCommand(jump);
            if (cond.arg == 1){
                codeGenerator.emit("JUMP", 0);
                int64_t jump2 = codeGenerator.getCurrentLine()-1;
                truecommands->generateCode(codeGenerator, symbolTable, scope);

                codeGenerator.updateCommand(jump, cond.code, jump2-jump+1);
                ino64_t jump3 = codeGenerator.getCurrentLine();

                cond = codeGenerator.getCommand(jump2);
                codeGenerator.updateCommand(jump2, cond.code, jump3-jump2);
            }
            if (cond.arg == 2){
                truecommands->generateCode(codeGenerator, symbolTable, scope); 
                int64_t jump2 = codeGenerator.getCurrentLine();

                codeGenerator.updateCommand(jump, cond.code, jump2-jump);
            }
        }
    }
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> truecommands;
    std::unique_ptr<ASTNode> falsecommands;
};

class WhileNode : public ASTNode {
public:
    WhileNode(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> commands) 
        : condition(std::move(condition)), commands(std::move(commands)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "WhileNode\n";

        printIndent(indent + 1);
        std::cout << "Condition:\n";
        if (condition) condition->print(indent + 2);

        printIndent(indent + 1);
        std::cout << "Commands:\n";
        if (commands) commands->print(indent + 2);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (condition) condition->traverseAndAnalyze(symbolTable, scope);
        if (commands) commands->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if(condition && commands){
            int64_t jump = codeGenerator.getCurrentLine();
            condition->generateCode(codeGenerator, symbolTable, scope);
            int64_t jump2 = codeGenerator.getCurrentLine();
            command cond = codeGenerator.getCommand(jump2-1);
            if (cond.arg == 1) {
                codeGenerator.updateCommand(jump2-1, cond.code, 2);
                codeGenerator.emit("JUMP", 0);

                commands->generateCode(codeGenerator, symbolTable, scope);
                int64_t jump3 = codeGenerator.getCurrentLine();
                codeGenerator.emit("JUMP", jump-jump3);
                codeGenerator.updateCommand(jump2, "JUMP", jump3+1-jump2);
            }
            if (cond.arg == 2) {
                commands->generateCode(codeGenerator, symbolTable, scope);
                int64_t jump3 = codeGenerator.getCurrentLine();
                codeGenerator.emit("JUMP", jump-jump3);
                codeGenerator.updateCommand(jump2-1, cond.code, jump3+1-jump2+1);
            }
        }

    }
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> commands;
};

class RepeatNode : public ASTNode {
public:
    RepeatNode(std::unique_ptr<ASTNode> commands, std::unique_ptr<ASTNode> condition) 
        : commands(std::move(commands)), condition(std::move(condition)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "RepeatNode\n";
        
        printIndent(indent + 1);
        std::cout << "Commands:\n";
        if (commands) commands->print(indent + 2);  
        
        printIndent(indent + 1);
        std::cout << "Condition:\n";
        if (condition) condition->print(indent + 2);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (commands) commands->traverseAndAnalyze(symbolTable, scope);
        if (condition) condition->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if(commands && condition){
            int64_t jump = codeGenerator.getCurrentLine();
            commands->generateCode(codeGenerator, symbolTable, scope);
            condition->generateCode(codeGenerator, symbolTable, scope);
            int64_t jump2 = codeGenerator.getCurrentLine();
            command cond = codeGenerator.getCommand(jump2-1);

            if (cond.arg == 1){
                codeGenerator.updateCommand(jump2-1, cond.code, 2);
                codeGenerator.emit("JUMP", jump-jump2);
            }
            if (cond.arg == 2){
                codeGenerator.updateCommand(jump2-1, cond.code, jump-jump2+1);
            }
        }
    }
private:
    std::unique_ptr<ASTNode> commands;
    std::unique_ptr<ASTNode> condition;
};

class ForToNode : public ASTNode {
public:
    ForToNode(std::string pidentifier,
              std::unique_ptr<ASTNode> fromvalue,
              std::unique_ptr<ASTNode> tovalue,
              std::unique_ptr<ASTNode> commands)
        : pidentifier(pidentifier),
          fromvalue(std::move(fromvalue)),
          tovalue(std::move(tovalue)),
          commands(std::move(commands)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ForToNode\n";
        printIndent(indent);
        std::cout << "Pidentifier:" << pidentifier << "\n";
        
        printIndent(indent + 1);
        std::cout << "Fromvalue:\n";
        if (fromvalue) fromvalue->print(indent + 2);
        
        printIndent(indent + 1);
        std::cout << "Tovalue:\n";
        if (tovalue) tovalue->print(indent + 2);
        
        printIndent(indent + 1);
        std::cout << "Commands:\n";
        if (commands) commands->print(indent + 2);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if(!symbolTable.variableExists(pidentifier, scope)){
            symbolTable.addVariable(pidentifier, scope);
        }
        symbolTable.getVariable(pidentifier, scope)->isInitialized = true;
        symbolTable.iterator = pidentifier;
        if (fromvalue) fromvalue->traverseAndAnalyze(symbolTable, scope);
        if (tovalue) tovalue->traverseAndAnalyze(symbolTable, scope);
        if (commands) commands->traverseAndAnalyze(symbolTable, scope);
        symbolTable.iterator = ""; 
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        int64_t iteratorMemoryPosition = symbolTable.getVariable(pidentifier, scope)->memoryPosition;

        if(fromvalue && tovalue && commands){

         if (!symbolTable.one){
                codeGenerator.emit("SET", 1);
                codeGenerator.emit("STORE", 10);
            }
            tovalue->generateCode(codeGenerator, symbolTable, scope);

            codeGenerator.emit("ADD", 10);
            codeGenerator.emit("STORE", 9);
            fromvalue->generateCode(codeGenerator, symbolTable, scope);
            codeGenerator.emit("STORE", iteratorMemoryPosition);
            int64_t jump = codeGenerator.getCurrentLine();
            codeGenerator.emit("SUB", 9);
            int64_t jump2 = codeGenerator.getCurrentLine();
            codeGenerator.emit("JZERO", 0);

            commands->generateCode(codeGenerator, symbolTable, scope);
            codeGenerator.emit("LOAD", iteratorMemoryPosition);
            codeGenerator.emit("ADD", 10);
            codeGenerator.emit("STORE", iteratorMemoryPosition);
            int64_t jump3 = codeGenerator.getCurrentLine();
            codeGenerator.emit("JUMP", jump-jump3);
            codeGenerator.updateCommand(jump2, "JZERO", jump3-jump2+1);
        }
    }
private:
    std::string pidentifier;
    std::unique_ptr<ASTNode> fromvalue;
    std::unique_ptr<ASTNode> tovalue;
    std::unique_ptr<ASTNode> commands;
};

class ForDownToNode : public ASTNode {
public:
    ForDownToNode(std::string pidentifier,
                  std::unique_ptr<ASTNode> fromvalue,
                  std::unique_ptr<ASTNode> downtovalue,
                  std::unique_ptr<ASTNode> commands)
        : pidentifier(pidentifier),
          fromvalue(std::move(fromvalue)),
          downtovalue(std::move(downtovalue)),
          commands(std::move(commands)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ForDownToNode\n";
        printIndent(indent);
        std::cout << "Pidentifier:" << pidentifier << "\n";
        
        printIndent(indent + 1);
        std::cout << "Fromvalue:\n";
        if (fromvalue) fromvalue->print(indent + 2);
        
        printIndent(indent + 1);
        std::cout << "Downtovalue:\n";
        if (downtovalue) downtovalue->print(indent + 2);
        
        printIndent(indent + 1);
        std::cout << "Commands:\n";
        if (commands) commands->print(indent + 2);
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if(!symbolTable.variableExists(pidentifier, scope)){
            symbolTable.addVariable(pidentifier, scope);
        }
        symbolTable.getVariable(pidentifier, scope)->isInitialized = true;
        symbolTable.iterator = pidentifier;
        if (fromvalue) fromvalue->traverseAndAnalyze(symbolTable, scope);
        if (downtovalue) downtovalue->traverseAndAnalyze(symbolTable, scope);
        if (commands) commands->traverseAndAnalyze(symbolTable, scope);
        symbolTable.iterator = "";
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if(fromvalue && downtovalue && commands){
            if (!symbolTable.one){
                codeGenerator.emit("SET", 1);
                codeGenerator.emit("STORE", 10);
            }
            downtovalue->generateCode(codeGenerator, symbolTable, scope);
            codeGenerator.emit("SUB", 10);
            codeGenerator.emit("STORE", 9);
            fromvalue->generateCode(codeGenerator, symbolTable, scope);
            codeGenerator.emit("STORE", symbolTable.getVariable(pidentifier, scope)->memoryPosition);
            int64_t jump = codeGenerator.getCurrentLine();
            codeGenerator.emit("SUB", 9);
            int64_t jump2 = codeGenerator.getCurrentLine();
            codeGenerator.emit("JZERO", 0);

            commands->generateCode(codeGenerator, symbolTable, scope);
            codeGenerator.emit("LOAD", symbolTable.getVariable(pidentifier, scope)->memoryPosition);
            codeGenerator.emit("SUB", 10);
            codeGenerator.emit("STORE", symbolTable.getVariable(pidentifier, scope)->memoryPosition);
            codeGenerator.emit("LOAD", symbolTable.getVariable(pidentifier, scope)->memoryPosition);
            int64_t jump3 = codeGenerator.getCurrentLine();
            codeGenerator.emit("JUMP", jump-jump3);
            codeGenerator.updateCommand(jump2, "JZERO", jump3-jump2+1);
        }

    
    }
private:
    std::string pidentifier;
    std::unique_ptr<ASTNode> fromvalue;
    std::unique_ptr<ASTNode> downtovalue;
    std::unique_ptr<ASTNode> commands;
};

class ProcallCommandNode : public ASTNode {
public:
    ProcallCommandNode(std::unique_ptr<ASTNode> proc_call) : proc_call(std::move(proc_call)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ProcallCommandNode\n";
        
        printIndent(indent + 1);
        std::cout << "Proc_call:\n";
        if (proc_call) proc_call->print(indent + 2);  
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (proc_call) proc_call->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (proc_call) proc_call->generateCode(codeGenerator, symbolTable, scope);
    }
private:
    std::unique_ptr<ASTNode> proc_call;
};

class ReadNode : public ASTNode {
public:
    ReadNode(std::unique_ptr<ASTNode> identifier) : identifier(std::move(identifier)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ReadNode\n";
        
        if (identifier) identifier->print(indent + 1);  
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if(identifier){
            auto idNode = dynamic_cast<IdentifierNode*>(identifier.get());
            if (idNode) {
                IdentifierNode::IdentifierType idType = idNode->getIdentifierType();
                std::string pidentifier;
                switch(idType){
                    case IdentifierNode::IdentifierType::SIMPLE:
                        pidentifier = idNode->getPidentifier();
                        if(pidentifier == symbolTable.iterator && pidentifier != ""){
                            throw std::runtime_error("Error: Cannot read value to iterator " + pidentifier + " in scope " + scope);
                        }
                        if(!symbolTable.variableExists(pidentifier, scope)){
                            throw std::runtime_error("Error: Variable " + pidentifier + " not declared in scope " + scope);
                        } else {
                            symbolTable.getVariable(pidentifier, scope)->isInitialized = true;
                        }
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_NUM:
                        pidentifier = idNode->getPidentifier();
                        if(pidentifier == ""){
                            throw std::runtime_error("Error: Cannot read value to iterator " + pidentifier + " in scope " + scope);
                        }else {
                            if(!symbolTable.arrayExists(pidentifier, scope)){
                                throw std::runtime_error("Error: Variable " + pidentifier + " not declared in scope " + scope);
                            } else {
                                symbolTable.getArray(pidentifier, scope)->memoryPositions[idNode->getIndex()] = true;
                            }
                        }
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_ID:
                        break;
                }
            }
        }   
        if (identifier) identifier->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
            if (identifier) {
                auto idNode = dynamic_cast<IdentifierNode*>(identifier.get());
                int64_t memoryPosition;
                int64_t indexMemoryPosition;
                bool isArgument;
                switch(idNode->getIdentifierType()){
                    case IdentifierNode::IdentifierType::SIMPLE:
                        codeGenerator.emit("GET", idNode->getMemoryPosition(symbolTable, scope));
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_NUM:
                        isArgument = symbolTable.getArray(idNode->getPidentifier(), scope)->isArgument;
                        if (!isArgument){
                            codeGenerator.emit("GET", idNode->getMemoryPosition(symbolTable, scope));
                        } else {
                            memoryPosition = symbolTable.getArray(idNode->getPidentifier(), scope)->memoryPosition + idNode->getIndex();
                            codeGenerator.emit("GET", memoryPosition);
                        }
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_ID:
                        isArgument = symbolTable.getArray(idNode->getPidentifier(), scope)->isArgument;
                        if (!isArgument){
                            identifier->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("STORE", 6);
                            codeGenerator.emit("GET", 0);
                            codeGenerator.emit("STOREI", 6);
                        } else {
                            memoryPosition = symbolTable.getArray(idNode->getPidentifier(), scope)->memoryPosition;
                            indexMemoryPosition = symbolTable.getVariable(idNode->getIndexIdentifier(),scope)->memoryPosition;
                            codeGenerator.emit("LOAD", memoryPosition);
                            codeGenerator.emit("ADD", indexMemoryPosition);
                            codeGenerator.emit("STORE", 6);
                            codeGenerator.emit("GET", 0);
                            codeGenerator.emit("STOREI", 6);
                        }
                        break;

                }
            }
    }
private:
    std::unique_ptr<ASTNode> identifier;
};

class WriteNode : public ASTNode {
public:
    WriteNode(std::unique_ptr<ASTNode> value) : value(std::move(value)) {}
    
    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "WriteNode\n";
        
        printIndent(indent + 1);
        std::cout << "Value:\n";
        if (value) value->print(indent + 2);  
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (value) {
            auto valNode = dynamic_cast<ValueNode*>(value.get());
            if (valNode && valNode->isIdentifier){
                auto idNode = dynamic_cast<IdentifierNode*>(valNode->getIdentifierNode());
                idNode->traverseAndAnalyze(symbolTable, scope);
            }
        }
        if (value) value->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        if (value) {
            auto valNode = dynamic_cast<ValueNode*>(value.get());
            if (valNode) {
                if (valNode->isIdentifier){
                    auto idNode = dynamic_cast<IdentifierNode*>(valNode->getIdentifierNode());
                    bool isArgument;
                    switch(idNode ->getIdentifierType()){
                        case IdentifierNode::IdentifierType::SIMPLE:
                            codeGenerator.emit("PUT", idNode->getMemoryPosition(symbolTable, scope));
                            break;
                        case IdentifierNode::IdentifierType::INDEXED_NUM:
                            isArgument = symbolTable.getArray(idNode->getPidentifier(), scope)->isArgument;
                            if (!isArgument){
                                codeGenerator.emit("PUT", idNode->getMemoryPosition(symbolTable, scope));
                            } else {
                                valNode->getIdentifierNode()->generateCode(codeGenerator, symbolTable, scope);
                                codeGenerator.emit("PUT", 0); 
                            }
                            break;
                        case IdentifierNode::IdentifierType::INDEXED_ID:
                            valNode->getIdentifierNode()->generateCode(codeGenerator, symbolTable, scope);
                            codeGenerator.emit("PUT", 0);
                            break;
                    }
                } else {
                    codeGenerator.emit("SET", valNode->getValue());
                    codeGenerator.emit("PUT", 0);
                }
            }
        }
    }
private:
    std::unique_ptr<ASTNode> value;
};

class DeclarationsNode : public ASTNode {
public:
    DeclarationsNode() = default;

    void addDeclaration(std::unique_ptr<ASTNode> declaration) {
        declarations.push_back(std::move(declaration));
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "DeclarationsNode\n";
        for (const auto& declaration : declarations) {
            declaration->print(indent + 1);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& declaration : declarations) {
            declaration->traverseAndAnalyze(symbolTable, scope);
        }
    }
private:
    std::vector<std::unique_ptr<ASTNode>> declarations; 
};

class DeclarationNode : public ASTNode {
public:

    DeclarationNode(std::string pidentifier)
        : pidentifier(std::move(pidentifier)), isArray(false), lowerBound(0), upperBound(0) {}

    DeclarationNode(std::string pidentifier, int64_t lowerBound, int64_t upperBound)
        : pidentifier(std::move(pidentifier)), isArray(true), lowerBound(lowerBound), upperBound(upperBound) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "DeclarationNode\n";
        
        printIndent(indent + 1);
        std::cout << "Pidentifier: " << pidentifier << "\n";
        
        if (isArray) {
            printIndent(indent + 1);
            std::cout << "Array: [" << lowerBound << ":" << upperBound << "]\n";
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if(isArray){
            symbolTable.addArray(pidentifier, scope, lowerBound, upperBound);
        } else { 
            symbolTable.addVariable(pidentifier, scope);
        }
    }

private:
    std::string pidentifier;   
    bool isArray;              
    int64_t lowerBound;     
    int64_t upperBound;    
};

class ArgsdeclsNode : public ASTNode {
public:
    ArgsdeclsNode() = default;

    void addArgsdecl(std::unique_ptr<ASTNode> args_decl) {
        args_decls.push_back(std::move(args_decl));
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ArgsdeclsNode\n";
        for (const auto& args_decl : args_decls) {
            args_decl->print(indent + 1);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        for (const auto& args_decl : args_decls) {
            args_decl->traverseAndAnalyze(symbolTable, scope);
        }
    }

private:
    std::vector<std::unique_ptr<ASTNode>> args_decls; 
};

class ArgsdeclNode : public ASTNode {
public:
    ArgsdeclNode(std::string pidentifier)
        : pidentifier(std::move(pidentifier)), isArray(false) {}

    ArgsdeclNode(std::string pidentifier, bool isArray)
        : pidentifier(std::move(pidentifier)), isArray(isArray) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ArgsdeclNode\n";
        printIndent(indent + 1);
        std::cout << "Pidentifier: " << pidentifier << "\n";
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (isArray) {
            auto arrayParam = std::make_shared<ArrayParam>();
            arrayParam->array.name = pidentifier;
            arrayParam->array.scope = scope;
            arrayParam->array.startIndex = 0;
            arrayParam->array.endIndex = 0;
            symbolTable.addProcedureParam(scope,"GLOBAL",arrayParam);
            symbolTable.addArray(pidentifier, scope, 0, 0);
            symbolTable.getArray(pidentifier, scope)->isInitialized[0] = true;
            symbolTable.getArray(pidentifier, scope)->isArgument = true;
        } else {
            auto variableParam = std::make_shared<VariableParam>();
            variableParam->variable.name = pidentifier;
            variableParam->variable.scope = scope; 
            variableParam->variable.isInitialized = true;
            symbolTable.addProcedureParam(scope,"GLOBAL",variableParam);
            symbolTable.addVariable(variableParam->variable);
            symbolTable.getVariable(pidentifier, scope)->isArgument = true;
        }     
    }

private:
    std::string pidentifier;   
    bool isArray;              
};

class ArgNode : public ASTNode {
public:
    ArgNode(std::string pidentifier)
        : pidentifier(std::move(pidentifier)) {}

    std::string getPidentifier() const {
        return pidentifier;
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ArgNode\n";
        printIndent(indent + 1);
        std::cout << "Pidentifier: " << pidentifier << "\n";
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const {
        if(!symbolTable.variableExists(pidentifier, scope)){
            if(!symbolTable.arrayExists(pidentifier, scope)){
                throw std::runtime_error("Error: " + pidentifier + " not declared in scope " + scope);
            }
        }else{
            symbolTable.getVariable(pidentifier, scope)->isInitialized = true;
        }
        
    }
private:
    std::string pidentifier;              
};

class ArgsNode : public ASTNode {
public:
    ArgsNode() = default;

    const std::vector<std::unique_ptr<ASTNode>>& getArgs() const {
        return args;
    }

    void addArg(std::unique_ptr<ASTNode> arg) {
        args.push_back(std::move(arg));
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ArgsNode\n";
        for (const auto& arg : args) {
            arg->print(indent + 1);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const {
        for (const auto& arg : args) {
            arg->traverseAndAnalyze(symbolTable, scope);
        }
    }

private:
    std::vector<std::unique_ptr<ASTNode>> args;
};

class ProcCallNode : public ASTNode {
public:
    ProcCallNode(std::string pidentifier, std::unique_ptr<ASTNode> args) 
        : pidentifier(std::move(pidentifier)), args(std::move(args)) {}
    
    std::vector<std::string> getArgsPidentifiers() const {
        std::vector<std::string> argsPidentifiers;
        collectArgsPidentifiers(args.get(), argsPidentifiers);
        return argsPidentifiers;
    }

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ProcCallNode\n";
        printIndent(indent);
        std::cout << "Pidentifier:" << pidentifier << "\n";
        
        printIndent(indent + 1);
        std::cout << "Args:\n";
        if (args) args->print(indent + 2);  
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {

        if(!symbolTable.procedureExists(pidentifier, "GLOBAL") || scope == pidentifier) {
            throw std::runtime_error("Error: Procedure " + pidentifier + " not declared in scope " + scope);
        }

        std::vector<std::string> argsString = getArgsPidentifiers();
        if(!symbolTable.isParamsTypeCorrect(pidentifier, scope, argsString)){
            throw std::runtime_error("Error: Incorrect type of arguments in procedure " + pidentifier + " in scope " + scope);
        }
        if (args) args->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        std::vector<std::string> argsString = getArgsPidentifiers();
        std::vector<std::string> paramsString;
        std::vector<std::shared_ptr<Param>> params = symbolTable.getProcedure(pidentifier, "GLOBAL")->params;

        for (const auto& param : params) {
            auto variableParam = dynamic_cast<VariableParam*>(param.get());
            if (variableParam) {
                paramsString.push_back(variableParam->variable.name);
          }
            auto arrayParam = dynamic_cast<ArrayParam*>(param.get());
            if (arrayParam) {
                paramsString.push_back(arrayParam->array.name);
            }
        }
        for (std::size_t i = 0; i < argsString.size(); i++) {
            if (symbolTable.variableExists(argsString[i], scope) && symbolTable.variableExists(paramsString[i], pidentifier)) {
                auto variable = symbolTable.getVariable(argsString[i], scope);
                auto variableParam = symbolTable.getVariable(paramsString[i], pidentifier);
                codeGenerator.emit("LOAD", variable->memoryPosition);
                codeGenerator.emit("STORE", variableParam->memoryPosition);
            } else if (symbolTable.arrayExists(argsString[i], scope) && symbolTable.arrayExists(paramsString[i], pidentifier)) {
                auto array = symbolTable.getArray(argsString[i], scope);
                auto arrayParam = symbolTable.getArray(paramsString[i], pidentifier);
                bool isArgument = array->isArgument;
                if (!isArgument){
                    codeGenerator.emit("SET", array->memoryPosition - array->startIndex);
                } else {
                    codeGenerator.emit("LOAD", array->memoryPosition - array->startIndex);
                }
                codeGenerator.emit("STORE", arrayParam->memoryPosition);
                arrayParam->startIndex = array->startIndex;
                arrayParam->endIndex = array->endIndex;
            }
        }
        
        codeGenerator.emit("SET",codeGenerator.getCurrentLine()+3);
        codeGenerator.emit("STORE", symbolTable.getProcedure(pidentifier, "GLOBAL")->returnVariable.memoryPosition);
        if (symbolTable.getProcedure(pidentifier, "GLOBAL")->jumpLabel != -1){
            codeGenerator.emit("JUMP",symbolTable.getProcedure(pidentifier, "GLOBAL")->jumpLabel-codeGenerator.getCurrentLine());
        }

        
        for (std::size_t i = 0; i < argsString.size(); i++) {
            if (symbolTable.variableExists(argsString[i], scope) && symbolTable.variableExists(paramsString[i], pidentifier)) {
                auto variable = symbolTable.getVariable(argsString[i], scope);
                auto variableParam = symbolTable.getVariable(paramsString[i], pidentifier);
                codeGenerator.emit("LOAD", variableParam->memoryPosition);
                codeGenerator.emit("STORE", variable->memoryPosition);
            } 
        }
        
    }
private:
    std::string pidentifier;
    std::unique_ptr<ASTNode> args;

    void collectArgsPidentifiers(const ASTNode* node, std::vector<std::string>& pidentifiers) const {
        if (!node) return;

        auto argsNode = dynamic_cast<const ArgsNode*>(node);
        if (argsNode) {
            for (const auto& arg : argsNode->getArgs()) {
                collectArgsPidentifiers(arg.get(), pidentifiers);
            }
        } else {
            auto argNode = dynamic_cast<const ArgNode*>(node);
            if (argNode) {
                pidentifiers.push_back(argNode->getPidentifier());
            }
        }
    }
};

class ConditionNode : public ASTNode {
public:
    ConditionNode(std::unique_ptr<ASTNode> leftValue, std::string op, std::unique_ptr<ASTNode> rightValue)
        : leftValue(std::move(leftValue)), op(std::move(op)), rightValue(std::move(rightValue)) {}

    void print(int indent = 0) const override {
        printIndent(indent);
        std::cout << "ConditionNode\n";
        printIndent(indent + 1);
        std::cout << "LeftValue:\n";
        if (leftValue) {
            leftValue->print(indent + 2);  
        }
        printIndent(indent + 1);
        std::cout << "Operator: " << op << "\n";
        printIndent(indent + 1);
        std::cout << "RightValue:\n";
        if (rightValue) {
            rightValue->print(indent + 2);
        }
    }
    
    void traverseAndAnalyze(SymbolTable& symbolTable, const std::string& scope) const override {
        if (leftValue) leftValue->traverseAndAnalyze(symbolTable, scope);
        if (rightValue) rightValue->traverseAndAnalyze(symbolTable, scope);
    }

    void generateCode(CodeGenerator& codeGenerator, SymbolTable& symbolTable, const std::string& scope) const override {
        auto leftVal = dynamic_cast<ValueNode*>(leftValue.get());
        auto rightVal = dynamic_cast<ValueNode*>(rightValue.get());
        if(leftVal->isIdentifier && rightVal->isIdentifier){
            leftVal->generateCode(codeGenerator, symbolTable, scope);
            if (rightVal->isIdentifier){
                auto rightId = dynamic_cast<IdentifierNode*>(rightVal->getIdentifierNode());
                switch (rightId->getIdentifierType()){
                    case IdentifierNode::IdentifierType::SIMPLE:
                        codeGenerator.emit("SUB", rightVal->getMemoryPosition(symbolTable, scope));
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_NUM:
                        codeGenerator.emit("SUB", rightVal->getMemoryPosition(symbolTable, scope));
                        break;
                    case IdentifierNode::IdentifierType::INDEXED_ID:
                        codeGenerator.emit("STORE", 6);
                        rightVal->generateCode(codeGenerator, symbolTable, scope);
                        codeGenerator.emit("SUBI", 6);
                        break;
                }
            }
        } else if (leftVal->isIdentifier && !rightVal->isIdentifier){
            int64_t rightValue = rightVal->getValue();
            if ( rightValue == 0){
                leftVal->generateCode(codeGenerator, symbolTable, scope);
            } else {
                codeGenerator.emit("SET", rightValue);
                codeGenerator.emit("STORE", 1);
                leftVal->generateCode(codeGenerator, symbolTable, scope);
                codeGenerator.emit("SUB", 1);
            }
        } else if (!leftVal->isIdentifier && rightVal->isIdentifier){
            int64_t leftValue = leftVal->getValue();
            codeGenerator.emit("SET", leftValue);
            auto righId = dynamic_cast<IdentifierNode*>(rightVal->getIdentifierNode());
            switch (righId->getIdentifierType()){
                case IdentifierNode::IdentifierType::SIMPLE:
                    codeGenerator.emit("SUB", rightVal->getMemoryPosition(symbolTable, scope));
                    break;
                case IdentifierNode::IdentifierType::INDEXED_NUM:
                    codeGenerator.emit("SUB", rightVal->getMemoryPosition(symbolTable, scope));
                    break;
                case IdentifierNode::IdentifierType::INDEXED_ID:
                    codeGenerator.emit("STORE", 6);
                    rightVal->generateCode(codeGenerator, symbolTable, scope);
                    codeGenerator.emit("SUBI", 6);
                    break;
            }
            
        } else {
            int64_t leftMemoryPosition = leftVal->getValue();
            int64_t rightMemoryPosition = rightVal->getValue();
            codeGenerator.emit("SET", leftMemoryPosition-rightMemoryPosition);
        }
        if(op == "="){
            codeGenerator.emit("JZERO", 1);
        }else if (op == "!="){
            codeGenerator.emit("JZERO", 2);
        } else if(op == "<"){
            codeGenerator.emit("JNEG", 1);
        } else if(op == ">"){
            codeGenerator.emit("JPOS", 1);
        } else if(op == "<="){
            codeGenerator.emit("JPOS", 2);
        } else if(op == ">="){
            codeGenerator.emit("JNEG", 2);
        }
        
    }
    std::string getOp() const {
        return op;
    }
private:
    std::unique_ptr<ASTNode> leftValue;
    std::string op;
    std::unique_ptr<ASTNode> rightValue;
};




