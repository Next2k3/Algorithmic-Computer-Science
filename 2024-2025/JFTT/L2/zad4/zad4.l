// Paweł Krzyszczak 272379

%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

int stack[MAX_STACK_SIZE];
int top = -1;
int error_handled = 0;

void push(int value) {
    if (top < MAX_STACK_SIZE - 1) {
        stack[++top] = value;
    } else {
        printf("Błąd: przepełnienie stosu\n");
        error_handled = 1;
    }
}

int pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Błąd: za mała liczba argumentów\n");
        error_handled = 1;
    }
}

int power(int base, int exp) {
    int result = 1;
    if (base == 1) { 
        return 1; 
    } 
    else if (base == 0) {
        return 0;
    }
    else if (exp < 0) { 
        return 0; 
    } 
    else {
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
    }
    return result;
}

void perform_operation(char operator) {
    int b = pop();
    int a = pop();

    if (error_handled) {
        return;
    }
    
    int result;

    switch (operator) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) {
                printf("Błąd: dzielenie przez 0\n");
                error_handled = 1;
                return;
            }
            result = a / b; 
            break;
        case '%': 
            if (b == 0) {
                printf("Błąd: dzielenie przez 0\n");
                error_handled = 1;
                return;
            }
            result = a % b; 
            break;
        case '^': 
            if (a == 0 && b == 0) {
                printf("Błąd: 0^0 jest niezdefiniowane\n");
                error_handled = 1;
                return;
            }
            else if (a == 0 && b < 0) {
                printf("Błąd: nie można podnieść 0 do ujemnej potęgi\n");
                error_handled = 1;
                return;
            }
            result = power(a, b); 
            break;  
        default:
            printf("Błąd: nieznany operator '%c'\n", operator);
            error_handled = 1;
            return;
    }
    push(result);
}

void print_result() {
    if (top == 0) {
        printf("= %d\n", stack[top]);
    } else {
    	if (!error_handled){
    	    printf("Błąd: za mała liczba operatorów\n");
    	}
    }
}

%}

%%

[-]?[0-9]+          { push(atoi(yytext)); }  
[+\-*/%^]           { perform_operation(yytext[0]); }  
[ \t\n]+            ;
.                   { error_handled = 1; top = -1; printf("Błąd: zły symbol '%s'\n", yytext); }  

%%

int main() {
    char line[256];
    
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Błąd: nie udało się wczytać linii\n");
        return 1;
    }

    top = -1; 
    yy_scan_string(line);  
    yylex(); 
    print_result();  

    return 0;
}

