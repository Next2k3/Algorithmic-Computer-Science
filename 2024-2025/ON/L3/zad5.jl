# Paweł Krzyszczak 272379

include("Metody.jl")
using .Metody

function calculate(a::Float64, b::Float64)
    f = x -> 3*x - (MathConstants.e)^x
    delta = epsilon = 10^(-4)
    r, v, it, err = mbisekcji(f, a, b, delta, epsilon)
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
end

println("Wyniki dla przedziału [0, 1]:")
calculate(0.0, 1.0)

println("Wyniki dla przedziału [1, 4]:")
calculate(1.0, 4.0)
