def factorial(n):
	result = 1
	for i in range(2,n+1):
		result *= i
	return result

def gcd(a,b):
	while b != 0:
		temp = b
		b = a % b
		a = temp
	return a

def diophantine(a,b,c):
	if a == 0 and b == 0:
		print("Invalid equation: both coefficients cannot be zero.")
		exit(1)
	gcd_ab = gcd(a, b)
	if c % gcd_ab != 0:
		print("No solution: c is not divisible by gcd(a, b).")
		exit(1)
	sign_a = -1 if a < 0 else 1
	sign_b = -1 if b < 0 else 1
	a = abs(a)
	b = abs(b)
	div = c // gcd_ab
	x = sign_a * div
	y = 0
	while (c - a * x) % b != 0:
		x += sign_a * (b // gcd_ab)
		y -= sign_b * (a // gcd_ab)
	y = (c - a * x) // b
	return x, y

		
