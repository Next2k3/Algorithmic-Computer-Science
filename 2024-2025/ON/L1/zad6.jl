# Paweł Krzyszczak 272379

# f(x) = sqrt(x^2 + 1) -1
function f(x::Float64)
	return sqrt(x*x + 1.0) -1.0
end

# g(x) = x^2 / (sqrt(x^2 + 1) + 1)
function g(x::Float64)
	return (x * x) / (sqrt(x*x + 1.0) + 1.0)
end

# Funkcja porównująca wartości funkcji f(x) i g(x) dla malejących wartości x
function calculate_and_compare_values()
	x = 1.0 / 8.0
	exp = -1
	while x > 0.0
		println("x = 8^", exp, ",\t f(x) = ",f(x), ",\tg(x) = ", g(x))
		x /= 8.0
		exp -= 1 
	end
end

calculate_and_compare_values()
