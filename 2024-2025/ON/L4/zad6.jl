# Paweł Krzyszczak 272379

include("interpolation.jl")
using .Interpolation
using Test
using Plots


f = x -> abs(x)
g = x -> 1 / (1 + x^2)

for n in [5, 10, 15]
  plot_f = rysujNnfx(f, -1.0, 1.0, n)
  plot_g = rysujNnfx(g, -5.0, 5.0, n)
  savefig(plot_f, "./zad6_f1_$n.png")
  savefig(plot_g, "./zad6_f2_$n.png")
end
