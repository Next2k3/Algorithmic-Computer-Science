# Paweł Krzyszczak 272379

include("Metody.jl")
using .Metody

function calculate1(f, a, b, delta, epsilon)
    r, v, it, err = mbisekcji(f, a, b, delta, epsilon)
    println("Pierwsza metoda (metoda bisekcji)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end


function calculate2(f, pf, x0, delta, epsilon, maxit)
    r, v, it, err = mstycznych(f, pf, x0, delta, epsilon, maxit)
    println("Druga metoda (metoda Newtona)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end

function calculate3(f, z0, x1, delta, epsilon, maxit)
    r, v, it, err = msiecznych(f, z0, x1, delta, epsilon, maxit)
    println("Trzecia metoda (metoda siecznych)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end

function compare(r1, r2, r3)
    results = [(abs(r1), 1), (abs(r2), 2), (abs(r3), 3)]
    
    resultsSorted = sort(results, by=x->x[1])
    bestIndex = resultsSorted[1][2]
    if bestIndex == 1
        println("Najlepsza jest metoda bisekcji")
    elseif bestIndex == 2
        println("Najlepsza jest metoda Newtona")
    elseif bestIndex == 3
        println("Najlepsza jest metoda siecznych")
    end
end

f1 = x -> (MathConstants.e)^(1-x) - 1
pf1 = x -> -(MathConstants.e)^(1-x)

f2 = x -> x*(MathConstants.e)^(-x)
pf2 = x -> (1 - x) * (MathConstants.e)^(-x)

delta = epsilon = 10^(-5)
maxit = 20

println("-------------------------------------------------------------")
println("f1(x) = e^(1-x) - 1\n")
a = 1.0
b = 2.0
println("Metoda bisekcji: ")
r11, v11 = calculate1(f1, a, b, delta, epsilon)

x0 = 2.0
println("Metoda Newtona: ")
r12, v12 = calculate2(f1, pf1, x0, delta, epsilon, maxit)

x0 = 0.0
x1 = 0.5
maxit = 20
println("Metoda siecznych: ")
r13, v13 = calculate3(f1, x0, x1, delta, epsilon, maxit)
compare(v11, v12, v13)
println()

for x0 in [1.0, 1.1, 1.5, 2.0, 5.0, 10.0, 50.0, 100.0]
    println("Test dla x0 = ", x0, ":")
    calculate2(f1, pf1, x0, delta, epsilon, maxit)
end

println("-------------------------------------------------------------")
println("f2(x) = x*e^(-x)\n")
a = 0.5
b = 1.0
println("Metoda bisekcji: ")
r21, v21 = calculate1(f1, a, b, delta, epsilon)

pf = x -> -(MathConstants.e)^(-x)*(x-1)
x0 = 0.5
maxit = 20
println("Metoda Newtona: ")
r22, v22 = calculate2(f1, pf1, x0, delta, epsilon, maxit)

x0 = 0.5
x1 = 1.0
maxit = 20
println("Metoda siecznych: ")
r23, v23 = calculate3(f1, x0, x1, delta, epsilon, maxit)
compare(v21, v22, v23)

for x0 in [1.0, 1.1, 1.5, 2.0, 5.0, 10.0, 50.0, 100.0]
    println("Test dla x0 = ", x0, ":")
    calculate2(f2, pf2, x0, delta, epsilon, maxit)
end
