# Paweł Krzyszczak 272379

module Interpolation
export ilorazyRoznicowe, warNewton, naturalna, rysujNnfx
using Plots

"""
Function for calculating difference quotients for given values
Input:
    x - vector of length n+1 with values of nodes x_0, ..., x_n
    f - vector of length n+1 with values of function f in nodes x_0, ..., x_n
Output:
    fx - vector of length n+1 with calculated values of difference quotients for given data
"""
function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
    len = length(x)
    fx = zeros(len)

    for i in 1:len
        fx[i] = f[i]
    end

    for j in 2:len
        for k in len:-1:j
           fx[k] = (fx[k] - fx[k - 1])/(x[k] - x[k - j + 1])
        end
    end

    return fx
end


"""
Function for value of interpolation polynomial in given point t
Input:
    x - vector of length n+1 with values of nodes x_0, ..., x_n
    fx - vector of length n+1 with values of difference quotients for given noded x_0, ..., x_n
    t - value for which the value of polynomial will be calculated
Output:
    nt - calculated value of polynomial in point t
"""
function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    len = length(x)
    nt::Float64 = fx[len]
    for i in (len-1):-1:1
        nt = fx[i] + (t - x[i])*nt
    end

    return nt
end


"""
Function for calculating the coefficients of interpolation polynomial in its natural form
Input:
    x - vector of length n+1 with values of nodes x_0, ..., x_n
    fx - vector of length n+1 with values of difference quotients for given noded x_0, ..., x_n
Output:
    a - vector of length n+1 with calculated values of coefficients of interpolation polynomial a_0, ..., a_n
"""
function naturalna(x::Vector{Float64}, fx::Vector{Float64})::Vector{Float64}
    len = length(x)
    a::Vector{Float64} = zeros(len)
    a[len] = fx[len]
    for i in (len-1):-1:1
        a[i] = fx[i] - x[i] * a[i+1]
        for j in (i+1):(len-1)
            a[j] = a[j] - x[i] * a[j+1]
        end
    end

    return a
end


"""
Function, which interpolates given function using interpolation polynomial and draws its graphic representations
Input:
    f - the function f(x)
    a, b - ends of interval of interpolation
    n - degree of interpolation polynomial
Output:
    graph of both interpolation polynomial and interpolated function
"""
function rysujNnfx(f, a::Float64, b::Float64, n::Int)
    graphResolution = 100
    h::Float64 = (b - a) / n
    x::Vector{Float64} = zeros(n+1)
    f_values::Vector{Float64} = zeros(n+1)

    for i in 1:(n+1)
        x[i] = a + (i-1) * h
        f_values[i] = f(x[i])
    end

    c::Vector{Float64} = ilorazyRoznicowe(x, f_values)
    pointsNum = graphResolution * n + 1
    intervalLen::Float64 = (b - a) / (pointsNum - 1)

    X::Vector{Float64} = zeros(pointsNum)
    W::Vector{Float64} = zeros(pointsNum)
    Y::Vector{Float64} = zeros(pointsNum)

    X[1] = a
    W[1] = warNewton(x, c, X[1])
    Y[1] = f(X[1])

    for i in 2:pointsNum
        X[i] = a + (i - 1) * intervalLen
        W[i] = warNewton(x, c, X[i])
        Y[i] = f(X[i])
    end

    p = plot(X, [W, Y], label = ["p(x)" "f(x)"], title = "Interpolation of function f using interpolation polynomial of degree <=$n", size=(1000, 400))

    return p
end

end
