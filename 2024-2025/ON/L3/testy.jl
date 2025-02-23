# Paweł Krzyszczak 272379

include("Metody.jl")
using .Metody
using Test

epsilon = delta = 10^(-5)

@testset "$(rpad("Metoda bisekcji", 15))" begin
	f = x -> 2*x^2 - 4*x
	
	# normalny przykład
	poprawnyWynik = 0
	result = mbisekcji(f, -1.0, 1.0, delta, epsilon)
	x = result[1]
	fx = result[2]
	err = result[4]
	@test abs(fx) <= epsilon
	@test abs(poprawnyWynik - x) <= delta
	@test err == 0
	
	# przedział bez zmiany znaku
	result = mbisekcji(f, 0.5, 1.5, delta, epsilon)
	x = result[1]
	fx = result[2]
	it = result[3]
	err = result[4]
	@test fx == Nothing
	@test x == Nothing
	@test it == Nothing
	@test err == 1

	# pierwiatek równo w połowie przedziału
	result = mbisekcji(f, 1.0, 3.0, delta, epsilon)
	x = result[1]
	fx = result[2]
	it = result[3]
	err = result[4]
	@test fx == 0
	@test x == 2
	@test it == 1
	@test err == 0
end

@testset "$(rpad("Metoda Newtona", 15))" begin
	# nomalny przykład
	f = x -> 0.5*x^3 - 4
	pf = x -> 1.5*x^2
	poprawnyWynik = 2.0
	result = mstycznych(f, pf, 0.5, delta, epsilon, 10)
	x = result[1]
	fx = result[2]
	err = result[4]
	@test abs(fx) < epsilon
	@test abs(poprawnyWynik-x) < delta
	@test err == 0

	# pochodna równa 0 dla przybliżenia początkowego
	f = x -> 0.5*x^3 - 4
	pf = x -> 1.5*x^2
	result = mstycznych(f, pf, 0.0, delta, epsilon, 10)
	err = result[4]
	@test err == 2

	# metoda Newtona wpada w cykl
	f = x -> 0.5*x^3 - x + 2
	pf = x -> 1.5*x^2 - 1
	result = mstycznych(f, pf, 0.0, delta, epsilon, 10)
	x = result[1]
	fx = result[2]
	it = result[3]
	err = result[4]
	@test abs(fx) > epsilon
	@test abs(x-0) > delta
	@test it == 10
	@test err == 1
end

@testset "$(rpad("Metoda siecznych", 15))" begin
	# normalny przykład
  	f = x -> x^3 - 1
	correctResult = 1.0
  	result = msiecznych(f, 0.5, 0.7, delta, epsilon, 10)
  	x = result[1]
  	fx = result[2]
  	err = result[4]
  	@test abs(fx) < epsilon
  	@test abs(correctResult-x) < delta
  	@test err == 0

  	# pochodna równa zero w miejscu zerowym
  	f = x -> x^2
  	result = msiecznych(f, -1.0, 1.0, delta, epsilon, 50)
  	x = result[1]
  	fx = result[2]
  	it = result[3]
  	err = result[4]
  	@test isnan(fx)
  	@test isnan(x)
  	@test it == 50
  	@test err == 1
end
