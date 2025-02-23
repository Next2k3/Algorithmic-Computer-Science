%{
#include <iostream>
#include <memory>
#include "AST.hpp"
#include <cstdint>

extern int yylex();
extern void yyerror(const char *s);
extern int yylineno;
extern std::string currentLine;
extern char* yytext;

std::unique_ptr<ASTNode> root;

inline ASTNode* cast(void* ptr) { return static_cast<ASTNode*>(ptr); }
inline void* to_void(ASTNode* node) { return static_cast<void*>(node); }

%}

%union {
    char* str;
    int64_t num;
    void* node;
}

%token <str> pidentifier 
%token <num> NUM
%token PROGRAM PROCEDURE PROGRAM_BEGIN END IS IF ELSE ENDIF THEN 
%token FROM WHILE DO ENDWHILE REPEAT UNTIL FOR TO DOWNTO ENDFOR 
%token READ WRITE EQUAL NOTEQUAL GREATER LESS GREATEREQUAL LESSEQUAL 
%token PLUS MINUS MULTIPLY DIVIDE MODULO ASSIGN COLON SEMICOLON COMMA 
%token LPAREN RPAREN LBRACKET RBRACKET
%token T

%type <num> NUM_T
%type <node> proc_head args 
%type <node> program_all procedures declarations commands command identifier main expression condition value proc_call args_decl

%start program_all 
%%

program_all:
    procedures main {
        auto programNode = new ProgramNode(
            std::unique_ptr<ASTNode>(cast($1)),
            std::unique_ptr<ASTNode>(cast($2))
        );
        root = std::unique_ptr<ASTNode>(programNode);
    }
    ;

procedures:
    procedures PROCEDURE proc_head IS declarations PROGRAM_BEGIN commands END {
        auto procedureNode = new ProcedureNode(
            std::unique_ptr<ASTNode>(cast($1)),
            std::unique_ptr<ProcHeadNode>(static_cast<ProcHeadNode*>($3)),
            std::unique_ptr<ASTNode>(cast($5)),
            std::unique_ptr<ASTNode>(cast($7))
        );
        $$ = to_void(procedureNode);
    }
    | procedures PROCEDURE proc_head IS PROGRAM_BEGIN commands END {
        auto procedureNode = new ProcedureNode(
            std::unique_ptr<ASTNode>(cast($1)),
            std::unique_ptr<ProcHeadNode>(static_cast<ProcHeadNode*>($3)),
            nullptr,
            std::unique_ptr<ASTNode>(cast($6))
        );
        $$ = to_void(procedureNode);
    }
    | /* pusty */ {
        $$ = to_void(nullptr);
    }
    ;

main:
    PROGRAM IS declarations PROGRAM_BEGIN commands END { 
        auto mainNode = new MainNode(
            std::unique_ptr<ASTNode>(cast($3)),
            std::unique_ptr<ASTNode>(cast($5))
        );
        $$ = to_void(mainNode);
    }
    | PROGRAM IS PROGRAM_BEGIN commands END {
        auto mainNode = new MainNode(
            std::unique_ptr<ASTNode>(cast(nullptr)),
            std::unique_ptr<ASTNode>(cast($4))
        );
        $$ = to_void(mainNode);
    }
    ;

commands:
    commands command {
        auto commandsNode = dynamic_cast<CommandsNode*>(cast($1));
        if (!commandsNode) {
            yyerror("Invalid cast to CommandsNode");
            YYABORT;
        }
        commandsNode->addCommand(std::unique_ptr<ASTNode>(cast($2)));
        $$ = to_void(commandsNode);
    }
    | command {
        auto commandsNode = new CommandsNode();
        commandsNode->addCommand(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(commandsNode);
    }
    ;

command:
    identifier ASSIGN expression SEMICOLON {
        auto assignmentNode = new AssignmentNode(
            std::unique_ptr<ASTNode>(cast($1)),
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(assignmentNode);
    }
    | IF condition THEN commands ELSE commands ENDIF {
        auto ifNode = new IfNode(
            std::unique_ptr<ASTNode>(cast($2)),
            std::unique_ptr<ASTNode>(cast($4)),
            std::unique_ptr<ASTNode>(cast($6))
        );
        $$ = to_void(ifNode);
    }
    | IF condition THEN commands ENDIF {
        auto ifNode = new IfNode(
            std::unique_ptr<ASTNode>(cast($2)),
            std::unique_ptr<ASTNode>(cast($4)),
            std::unique_ptr<ASTNode>(cast(nullptr))
        );
        $$ = to_void(ifNode);
    }
    | WHILE condition DO commands ENDWHILE {
        auto whileNode = new WhileNode(
            std::unique_ptr<ASTNode>(cast($2)),
            std::unique_ptr<ASTNode>(cast($4))
        );
        $$ = to_void(whileNode);
    }
    | REPEAT commands UNTIL condition SEMICOLON {
        auto repeatNode = new RepeatNode(
            std::unique_ptr<ASTNode>(cast($2)),
            std::unique_ptr<ASTNode>(cast($4))
        );
        $$ = to_void(repeatNode);
    }
    | FOR pidentifier FROM value TO value DO commands ENDFOR {
        auto forToNode = new ForToNode(
            $2,
            std::unique_ptr<ASTNode>(cast($4)),
            std::unique_ptr<ASTNode>(cast($6)),
            std::unique_ptr<ASTNode>(cast($8))
        );
        $$ = to_void(forToNode);
    }
    | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR {
        auto forDownToNode = new ForDownToNode(
            $2,
            std::unique_ptr<ASTNode>(cast($4)),
            std::unique_ptr<ASTNode>(cast($6)),
            std::unique_ptr<ASTNode>(cast($8))
        );
        $$ = to_void(forDownToNode);
    }
    | proc_call SEMICOLON {
        auto procallCommandNode = new ProcallCommandNode(
            std::unique_ptr<ASTNode>(cast($1))
        );
        $$ = to_void(procallCommandNode);
    }
    | READ identifier SEMICOLON {
        auto readNode = new ReadNode(
            std::unique_ptr<ASTNode>(cast($2))
        );
        $$ = to_void(readNode);
    }
    | WRITE value SEMICOLON {
        auto writeNode = new WriteNode(
            std::unique_ptr<ASTNode>(cast($2))
        );
        $$ = to_void(writeNode);  
    }
    ;

proc_head:
    pidentifier LPAREN args_decl RPAREN {
        auto procHeadNode = new ProcHeadNode(
            $1,
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(procHeadNode);  
    }
    ;

proc_call:
    pidentifier LPAREN args RPAREN {
        auto procCallNode  = new ProcCallNode (
            $1,
            std::unique_ptr<ASTNode>(cast($3))       
        );
        $$ = to_void(procCallNode );  
    }
    ;

declarations:
    declarations COMMA pidentifier {
        auto declarationsNode = new DeclarationsNode();
        auto declarationNode = new DeclarationNode($3);
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast(declarationNode)));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(declarationsNode);
    }
    | declarations COMMA pidentifier LBRACKET NUM_T COLON NUM_T RBRACKET {
        auto declarationsNode = new DeclarationsNode();
        auto declarationNode = new DeclarationNode($3, $5, $7);
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast(declarationNode)));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(declarationsNode);
    }
    | pidentifier {
        auto declarationNode = new DeclarationNode($1);
        $$ = to_void(declarationNode);
    }   
    | pidentifier LBRACKET NUM_T COLON NUM_T RBRACKET {
        auto declarationNode = new DeclarationNode($1, $3, $5);
        $$ = to_void(declarationNode);
    }
    ;

args_decl:
    args_decl COMMA pidentifier {
        auto argsdeclsNode = new ArgsdeclsNode();
        auto argsdeclNode = new ArgsdeclNode($3);
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast(argsdeclNode)));
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(argsdeclsNode);
    }
    | args_decl COMMA T pidentifier {
        auto argsdeclsNode = new ArgsdeclsNode();
        auto argsdeclNode = new ArgsdeclNode($4, true);
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast(argsdeclNode)));
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(argsdeclsNode);
    }
    | pidentifier {
        auto argsdeclNode = new ArgsdeclNode($1);
        $$ = to_void(argsdeclNode);
    }
    | T pidentifier {
        auto argsdeclNode = new ArgsdeclNode($2, true);
        $$ = to_void(argsdeclNode);
    }
    ;
    
args:
    args COMMA pidentifier{
        auto argsNode = new ArgsNode();
        auto argNode = new ArgNode($3);
        argsNode->addArg(std::unique_ptr<ASTNode>(cast(argNode)));
        argsNode->addArg(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(argsNode);
    }
    | pidentifier {
        auto argNode = new ArgNode($1);
        $$ = to_void(argNode);
    }
    ;

expression:
    value {
        $$ = $1; 
    }
    | value PLUS value {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "+", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
    | value MINUS value {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "-", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
    | value MULTIPLY value {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "*", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
    | value DIVIDE value {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "/", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
    | value MODULO value {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "%", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
    ;


condition:
    value EQUAL value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "=", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    | value NOTEQUAL value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "!=", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    | value GREATER value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            ">", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    | value LESS value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "<", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    | value GREATEREQUAL value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            ">=", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    | value LESSEQUAL value {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast($1)), 
            "<=", 
            std::unique_ptr<ASTNode>(cast($3))
        );
        $$ = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
    ;

value:
    NUM_T {
        auto valueNode = new ValueNode($1);
        $$ = to_void(valueNode);
    }
    | identifier {
        auto valueNode = new ValueNode(std::unique_ptr<ASTNode>(cast($1)));
        $$ = to_void(valueNode);
    }
    ;

identifier:
    pidentifier {
        auto identifierNode = new IdentifierNode($1);
        $$ = to_void(identifierNode);
    }
    | pidentifier LBRACKET pidentifier RBRACKET {
        auto identifierNode = new IdentifierNode($1, $3);
        $$ = to_void(identifierNode);
    }
    | pidentifier LBRACKET NUM_T RBRACKET {
        auto identifierNode = new IdentifierNode($1, $3);
        $$ = to_void(identifierNode);
    }
    ;

NUM_T:
    NUM {
        $$ = $1;
    }
    | MINUS NUM {
        $$ = -$2;
    }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Syntax error: "<< yytext << std::endl;
    std::cerr << yylineno <<"  | "<< currentLine << std::endl;
}

