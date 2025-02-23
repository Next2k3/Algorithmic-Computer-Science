# Paweł Krzyszczak 272379

include("interpolation.jl")
using .Interpolation
using Test
using Plots

@testset "$(rpad("zadanie 4 z listy 4 z ćwiczeń", 40))" begin
  x::Vector{Float64} = [-2.0, -1.0, 0.0, 1.0, 2.0, 3.0]
  f::Vector{Float64} = [-25.0, 3.0, 1.0, -1.0, 27.0, 235.0]
  fx::Vector{Float64} = ilorazyRoznicowe(x, f)
  @test fx[1] == -25 #wyliczone na kartce papieru
  @test fx[2] == 28
  @test fx[3] == -15
  @test fx[4] == 5
  @test fx[5] == 0
  @test fx[6] == 1
  @test warNewton(x, fx, -2.0) == -25.0 #spełnienie warunku interpolacji
  @test warNewton(x, fx, -1.0) == 3.0
  @test warNewton(x, fx, 0.0) == 1.0
  @test warNewton(x, fx, 1.0) == -1.0
  @test warNewton(x, fx, 2.0) == 27.0
  @test warNewton(x, fx, 3.0) == 235.0
  naturalne = naturalna(x, fx)
  @test naturalne[1] == 1.0  #wyliczone na kartce papieru
  @test naturalne[2] == -3.0
  @test naturalne[3] == 0.0
  @test naturalne[4] == 0.0
  @test naturalne[5] == 0.0
  @test naturalne[6] == 1.0
end

@testset "$(rpad("zadanie 5 z listy 4 z ćwiczeń cz.1", 40))" begin
  x::Vector{Float64} = [-1.0, 0.0, 1.0, 2.0]
  f::Vector{Float64} = [2.0, 1.0, 2.0, -7.0]
  fx::Vector{Float64} = ilorazyRoznicowe(x, f)
  @test fx[1] == 2.0 #wyliczone na kartce papieru
  @test fx[2] == -1.0
  @test fx[3] == 1.0
  @test fx[4] == -2.0
  @test warNewton(x, fx, -1.0) == 2.0 #spełnienie warunku interpolacji
  @test warNewton(x, fx, 0.0) == 1.0
  @test warNewton(x, fx, 1.0) == 2.0
  @test warNewton(x, fx, 2.0) == -7.0
  naturalne = naturalna(x, fx)
  @test naturalne[1] == 1.0 #wyliczone na kartce papieru
  @test naturalne[2] == 2.0
  @test naturalne[3] == 1.0
  @test naturalne[4] == -2.0
end

@testset "$(rpad("zadanie 5 z listy 4 z ćwiczeń cz.2", 40))" begin
  x::Vector{Float64} = [-1.0, 0.0, 1.0, 2.0, 3.0]
  f::Vector{Float64} = [2.0, 1.0, 2.0, -7.0, 10.0]
  fx::Vector{Float64} = ilorazyRoznicowe(x, f)
  @test fx[1] == 2.0 #wyliczone na kartce papieru, zmiana lokalna względem cz.1
  @test fx[2] == -1.0
  @test fx[3] == 1.0
  @test fx[4] == -2.0
  @test fx[5] == 2.0
  @test warNewton(x, fx, -1.0) == 2.0 #spełnienie warunku interpolacji
  @test warNewton(x, fx, 0.0) == 1.0
  @test warNewton(x, fx, 1.0) == 2.0
  @test warNewton(x, fx, 2.0) == -7.0
  @test warNewton(x, fx, 3.0) == 10.0
  naturalne = naturalna(x, fx)
  @test naturalne[1] == 1.0 #wyliczone na kartce papieru
  @test naturalne[2] == 6.0
  @test naturalne[3] == -1.0
  @test naturalne[4] == -6.0
  @test naturalne[5] == 2.0
end

@testset "$(rpad("interpolowanie wielomianu", 40))" begin
  f = x -> 2*x^3 + x^2 + 3*x + 7
  x::Vector{Float64} = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]
  fWartosci::Vector{Float64} = [f(x[1]), f(x[2]), f(x[3]), f(x[4]), f(x[5]), f(x[6])]
  fx::Vector{Float64} = ilorazyRoznicowe(x, fWartosci)
  @test fx[1] == 7.0 #wyliczone na kartce papieru
  @test fx[2] == 6.0
  @test fx[3] == 7.0
  @test fx[4] == 2.0
  @test fx[5] == 0.0
  @test fx[6] == 0.0
  @test warNewton(x, fx, x[1]) == f(x[1]) #spełnienie warunku interpolacji
  @test warNewton(x, fx, x[2]) == f(x[2])
  @test warNewton(x, fx, x[3]) == f(x[3])
  @test warNewton(x, fx, x[4]) == f(x[4])
  @test warNewton(x, fx, x[5]) == f(x[5])
  @test warNewton(x, fx, x[6]) == f(x[6])
  naturalne = naturalna(x, fx)
  @test naturalne[1] == 7.0   # wielomian interpolujący wielomian to ten sam wielomian co interpolowany
  @test naturalne[2] == 3.0
  @test naturalne[3] == 1.0
  @test naturalne[4] == 2.0
  @test naturalne[5] == 0.0
  @test naturalne[6] == 0.0
  @test typeof(rysujNnfx(f, 0.0, 5.0, 5)) == Plots.Plot{Plots.GRBackend}
end
