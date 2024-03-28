def factorial(n):
	if n <= 1:
		return 1
	else:
		return n * factorial(n - 1)
	
def gcd(a, b):
	if b == 0:
		return a
	else:
		return gcd(b, a % b)

def diophantine(a, b, c):
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
    
    	if (c - a * x) % b != 0:
        	next_solution = diophantine(b, a % b, c - a * x)
        	x += sign_a * next_solution[0]
        	y += sign_b * next_solution[1]
    	else:
        	y = (c - a * x) // b
    	return x,y
