from zadanie_6 import factorial, gcd, diophantine

n = 5
k = factorial(n)
print(f"Factorial of {n} is {k}")

a = 35
b = 10
l = gcd(a,b)
print(f"GCD of {a} and {b} is {l}")

c = 55 
m = diophantine(a,b,c)
print(f"Diophantine equation: {a}x + {b}y = {c} is x = {m.x}, y = {m.y}")


