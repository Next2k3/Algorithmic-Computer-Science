# Paweł Krzyszczak 272379

include("Metody.jl")
using .Metody

function calculate1()
    f = x -> sin(x) - (0.5*x)^2
    a = 1.5
    b = 2.0
    delta = epsilon = 0.5*10^(-5)
    r, v, it, err = mbisekcji(f, a, b, delta, epsilon)
    println("Pierwsza metoda (metoda bisekcji)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end


function calculate2()
    f = x -> sin(x) - (0.5*x)^2
    pf = x -> cos(x) - 0.5*x
    x0 = 1.5
    delta = epsilon = 0.5*10^(-5)
    r, v, it, err = mstycznych(f, pf, x0, delta, epsilon, 20)
    println("Druga metoda (metoda Newtona)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end

function calculate3()
    f = x -> sin(x) - (0.5*x)^2
    x0 = 1.0
    x1 = 2.0
    delta = epsilon = 0.5*10^(-5)
    r, v, it, err = msiecznych(f, x0, x1, delta, epsilon, 20)
    println("Trzecia metoda (metoda siecznych)")
    println("r:                       ", r)
    println("v:                       ", v) 
    println("it:                      ", it)
    println("er:                      ", err)
    println()
    return r, v
end

function compare()
    r1, v1 = calculate1()
    r2, v2 = calculate2()
    r3, v3 = calculate3()

    results = [(abs(v1), 1), (abs(v2), 2), (abs(v3), 3)]
    
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

compare()
