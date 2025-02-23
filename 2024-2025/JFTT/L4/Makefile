# Makefile for parser and lexer in C++

# Tools
CXX = g++
LEX = flex
YACC = bison
CXXFLAGS = -Wall -std=c++17 -g -I$(SRC_DIR)

# Directories
SRC_DIR = source
BUILD_DIR = build
BIN_DIR = bin

# Source files
LEXER_SRC = $(SRC_DIR)/lexer.l
PARSER_SRC = $(SRC_DIR)/parser.y
COMPILER = $(SRC_DIR)/compiler.cpp  
SYMBOLTABLE_SRC = $(SRC_DIR)/SymbolTable.cpp

# Headers
AST_HEADER = $(SRC_DIR)/AST.hpp
SYMBOLTABLE_HEADER = $(SRC_DIR)/SymbolTable.hpp
CODEGENERATOR_HEADER = $(SRC_DIR)/CodeGenerator.hpp

# Generated files
LEXER_CPP = $(BUILD_DIR)/lexer.cpp
PARSER_TAB_CPP = $(BUILD_DIR)/parser.tab.cpp
PARSER_TAB_HPP = $(BUILD_DIR)/parser.tab.hpp

# Object files
LEXER_OBJ = $(BUILD_DIR)/lexer.o
PARSER_OBJ = $(BUILD_DIR)/parser.o
AST_OBJ = $(BUILD_DIR)/AST.o
SYMBOLTABLE_OBJ = $(BUILD_DIR)/SymbolTable.o

# Output binary
OUTPUT = $(BIN_DIR)/kompilator

# Build rules
all: $(OUTPUT)

$(OUTPUT): $(PARSER_OBJ) $(LEXER_OBJ) $(AST_OBJ) $(SYMBOLTABLE_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PARSER_OBJ): $(PARSER_SRC) $(PARSER_TAB_CPP) $(PARSER_TAB_HPP) $(AST_HEADER) $(SYMBOLTABLE_HEADER)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $(PARSER_TAB_CPP) -o $@

$(LEXER_OBJ): $(LEXER_SRC) $(PARSER_TAB_HPP)
	@mkdir -p $(BUILD_DIR)
	$(LEX) -o $(LEXER_CPP) $<
	$(CXX) $(CXXFLAGS) -c $(LEXER_CPP) -o $@

$(AST_OBJ): $(COMPILER) $(AST_HEADER) $(SYMBOLTABLE_HEADER) $(CODEGENERATOR_HEADER)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SYMBOLTABLE_OBJ): $(SYMBOLTABLE_SRC) $(SYMBOLTABLE_HEADER)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PARSER_TAB_CPP) $(PARSER_TAB_HPP): $(PARSER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(YACC) -d -o $(PARSER_TAB_CPP) $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

