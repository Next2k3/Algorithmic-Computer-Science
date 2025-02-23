# Paweł Krzyszczak 272379

using LinearAlgebra

include("hilb.jl")
include("matcond.jl")

function compute_relative_error(computed_value, exact_value)
    return norm(exact_value - computed_value) / norm(computed_value)
end

function run_hilbert_matrix_experiment(max_n::Int)
    for n in 1:max_n
        x = ones(Float64, n)
        A = hilb(n)
        b = A * x

        gauss_x = A \ b
        inv_x = inv(A) * b

        gauss_error = compute_relative_error(gauss_x, x)
        inv_error = compute_relative_error(inv_x, x)

        println("$n & $(cond(A)) & $(rank(A)) & $gauss_error & $inv_error\\\\\n\\hline")
    end
end

function run_random_matrix_experiment()
    conditions = [1.0, 10.0, 10.0^3, 10.0^7, 10.0^12, 10.0^16]
    for n in [5, 10, 20]
        x = ones(Float64, n)
        for c in conditions
            A = matcond(n, c)
            b = A * x

            gauss_x = A \ b
            inv_x = inv(A) * b

            gauss_error = compute_relative_error(gauss_x, x)
            inv_error = compute_relative_error(inv_x, x)

            println("$n & $c & $(rank(A)) & $gauss_error & $inv_error\\\\\n\\hline")
        end
    end
end

run_hilbert_matrix_experiment(15)
println()
run_random_matrix_experiment()
