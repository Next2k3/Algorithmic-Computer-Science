# Paweł Krzyszczak 272379

function compute_next_x(x::Float64, c::Float64)
    return x^2 + c
end

function print_row(n::Int, c::Float64, current_xs::Vector{Float64})
    print("$n & $(Int.(c))")
    for current_x in current_xs
        print(" & $current_x")
    end
    print("\\\\\n\\hline\n")
end

function run_experiment(c::Float64, xs::Vector{Float64}, plot_prefix::String)
    current_xs = copy(xs)
    x_plot_values = [Vector{Float64}(undef, 41) for _ in eachindex(current_xs)]

    for i in eachindex(current_xs)
        x_plot_values[i][1] = current_xs[i]
    end

    print_row(0, c, current_xs)

    for n in 1:40
        for i in eachindex(current_xs)
            current_xs[i] = compute_next_x(current_xs[i], c)
            x_plot_values[i][n+1] = current_xs[i]
        end

        print_row(n, c, current_xs)
    end

end

run_experiment(-2.0, [1.0, 2.0, 1.99999999999999], "1")
println()
run_experiment(-1.0, [1.0, -1.0, 0.75, 0.25], "2")
