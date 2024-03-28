import zadanie_3_rec

n = 5
k = zadanie_3_rec.factorial(n)
print(f"Factorial of {n} is {k}")

a = 35
b = 10
l = zadanie_3_rec.gcd(a,b)
print(f"GCD of {a} and {b} is {l}")

c = 55 
m = zadanie_3_rec.diophantine(a,b,c)
print(f"Diophantine equation: {a}x + {b}y = {c} is x = {m[0]}, y = {m[1]}")
