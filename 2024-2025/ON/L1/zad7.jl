# Paweł Krzyszczak 272379

# Funkcja zdefiniowana jako f(x) = sin(x) + cos(3 * x)
function calculate_function(x::Float64)
    return sin(x) + cos(3.0 * x)
end

# Przybliżenie pochodnej funkcji f w punkcie x z wykorzystaniem metody różnicy skończonej
# df(x, h) ≈ f'(x), czyli df(x, h) = (f(x + h) - f(x)) / h
function approximate_derivative(x::Float64, step::Float64)
    return (calculate_function(x + step) - calculate_function(x)) / step
end

# Obliczanie przybliżonej wartości pochodnej w punkcie x = 1.0
function compute_derivative_convergence()
    exact_derivative_value = 0.11694228168853805 # zewnętrznie obliczona dokładna wartość pochodnej f'(1)
    step_size = 1.0
    power_of_two = 0 # wykładnik potęgi 2 (step_size = 2^power_of_two)
    estimated_derivative = 0.0

    while power_of_two >= -54
        estimated_derivative = approximate_derivative(1.0, step_size)
        println("f'(x) ≈", estimated_derivative," dla h = 2^", power_of_two)
        println("1 + h = ", 1.0 + step_size)
        println("Błąd względny: ", abs(exact_derivative_value - estimated_derivative))
        #println(power_of_two," & ",estimated_derivative," & ",abs(exact_derivative_value - estimated_derivative), " \\","\\")
        step_size /= 2
        power_of_two -= 1
    end
end

compute_derivative_convergence()
