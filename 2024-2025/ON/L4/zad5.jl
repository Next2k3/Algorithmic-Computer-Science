# Paweł Krzyszczak

include("interpolation.jl")
using .Interpolation
using Test
using Plots


f = x -> exp(x)
g = x -> x^2 * sin(x)

for n in [5, 10, 15]
  plot_f = rysujNnfx(f, 0.0, 1.0, n)
  plot_g = rysujNnfx(g, -1.0, 1.0, n)
  savefig(plot_f, "./zad5_f1_$n.png")
  savefig(plot_g, "./zad5_f2_$n.png")
end
