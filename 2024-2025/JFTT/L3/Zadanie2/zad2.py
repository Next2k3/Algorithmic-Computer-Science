import ply.yacc as yacc
import ply.lex as lex
from sys import stdin
from lex import *
from GF import *

def print_(*x) -> None:
    print(*x, end='')
    
lex.lex()

error_message = "error";
RPN = "";
P=1234577

precedence = (
   ("left", 'PLUS', 'MINUS'),
   ("left", 'MULT', 'DIV','MOD'),
   ('right', 'POW') )

def p_error(p):
    print(error_message + "\n")
    
def p_start(p):
    """start : EXPRESSION"""
    global RPN
    print(RPN)
    print('Wynik: ', p[1])
    RPN = ""; 

def p_start_com(p):
    """start : COM"""
    pass
    
def p_expression_number(p):
    """EXPRESSION : NUM"""
    global RPN 
    RPN+= str(gf_format(p[1],P)) + ' '
    p[0] = gf_format(p[1],P)
    
def p_expression_neg(p):
    """EXPRESSION : MINUS NUM"""
    global RPN
    global P
    RPN += str(P-p[2]) + ' '; 
    p[0] = P-p[2];
    
def p_expression_group(p):
    """EXPRESSION : BRACKET_OPEN EXPRESSION BRACKET_CLOSE"""
    p[0] = p[2]

def p_expression_plus(p):
    """EXPRESSION : EXPRESSION PLUS EXPRESSION"""
    global RPN 
    global P
    RPN += '+ '; 
    p[0] = gf_format(p[1] + p[3], P);
    
def p_expression_minus(p):
    """EXPRESSION : EXPRESSION MINUS EXPRESSION"""
    global RPN
    global P 
    RPN += '- '; 
    p[0] = gf_format(p[1] - p[3],P);
    
def p_expression_mult(p):
    """EXPRESSION : EXPRESSION MULT EXPRESSION"""
    global RPN 
    global P
    RPN += '* '; 
    p[0] = gf_format(p[1] * p[3],P);
    
def p_expression_div(p):
    """EXPRESSION : EXPRESSION DIV EXPRESSION"""
    global RPN
    global P
    RPN += '/ '
    if(p[3] == 0):
    	error_message = str(p[3])+" nie posiada odwrotności w GF("+str(P)+")"
    	return
    p[0] = gf_format(p[1]*inverse(p[3],P),P)
 
def p_expression_mod(p):
    """EXPRESSION : EXPRESSION MOD EXPRESSION"""
    global RPN
    global P
    RPN += '% ';
    p[0] = gf_format(p[1] % p[3],P);
 
def p_expression_pow(p):
    """EXPRESSION : EXPRESSION POW EXPRESSION"""
    global RPN 
    global P
    RPN += '^ ';
    p[0] = gf_format(pow(p[1],  p[3]),P);

yacc.yacc()

acc = ''
for line in stdin:
    if line[-2] == '\\':
        acc += line[:-2]
    elif acc != '':
        acc += line
        yacc.parse(acc)
        acc = ''
    else:
        yacc.parse(line)
