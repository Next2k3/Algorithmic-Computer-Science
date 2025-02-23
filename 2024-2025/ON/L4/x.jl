
include("interpolation.jl")
using .Interpolation

 x::Vector{Float64} = [-1.0,0.0,1.0,2.0]
 f::Vector{Float64} = [-1.0,0.0,-1.0,2.0]
 fx::Vector{Float64} = ilorazyRoznicowe(x, f)
 a = naturalna(x, fx)
#0 -1 -1  1
#(1)*x^3 + (-1)*x^2 + (-1)x + 0
println(a)
