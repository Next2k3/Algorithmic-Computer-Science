# Paweł Krzyszczak 272379
module Blocksys

using SparseArrays

export calculate_b, gauss_elimination, gauss_elimination_with_main_element, lu, solve_lu, lu_with_main_element_sparse, solve_lu_with_main_element

"""
Pomocnicze funkcje do obliczania indeksów granicznych dla bloków.
"""
function last_row(k, l, n)
    return Int64(min(l + l * floor((k+1) / l), n))
end

function last_column(k, l, n)
    return Int64(min(k + l, n))
end

function first_column(i, l)
    return Int64(max((l * floor((i-1) / l) - 1), 1))
end

"""
Funkcja rozwiązująca układ równań liniowych Ax = b metodą eliminacji Gaussa bez wyboru elementu głównego.
Parametry:
- A: dana macierz o rozmiarze nxn
- b: wektor prawnych stron (długości n) 
- l: wielkość bloku
Returns:
- x: wektor rozwiązania (długości n)
"""
function gauss_elimination(A::SparseMatrixCSC{Float64, Int64}, b::Vector{Float64}, l::Int64)
    A_copy = copy(A)
    b_copy = copy(b)
    n = size(A_copy, 1)              
    x = zeros(Float64, n)

    # Tworzenie macierzy górnotrójkątnej
    for k in 1:n-1
        lr = last_row(k, l, n)
        lc = last_column(k, l, n)
        for i in k+1:lr
            if abs(A_copy[k, k]) < 1e-12
                throw(DomainError("Błąd: Element na przekątnej macierzy A[$k, $k] zbyt bliski zeru."))
            end
            m = A_copy[i, k] / A_copy[k, k] 
            A_copy[i, k] = 0 
            for j in k+1:lc
                A_copy[i, j] -= m * A_copy[k, j]
            end
            b_copy[i] -= m * b_copy[k]
        end
    end

    # Rozwiązanie równania za pomocą podstawienia wstecznego
    for i in n:-1:1
        lc = last_column(i, l, n)
        sum = 0.0
        for j in i+1:lc
            sum += A_copy[i, j] * x[j]
        end
        x[i] = (b_copy[i] - sum) / A_copy[i, i] 
    end

    return x
end

"""
Funkcja rozwiązująca układ równań liniowych Ax = b metodą eliminacji Gaussa z częściowym wyborem elementu głównego.
Parametry:
- A: dana macierz o rozmiarze nxn
- b: wektor prawnych stron (długości n) 
Returns:
- x: wektor rozwiązania (długości n)
"""
function gauss_elimination_with_main_element(A::SparseMatrixCSC{Float64, Int}, b::Vector{Float64}, l::Int64)
    A_copy = copy(A)
    b_copy = copy(b)
    n = size(A_copy, 1)
    x = zeros(Float64, n)
    p = collect(1:n)

    for k in 1:n-1
        lc = last_column(k, 2*l, n)
        lr = last_row(k, l, n)
        max_index = k
        max_element = 0.0

        for i in k:lr
            current = abs(A_copy[p[i], k])
            if current > max_element
                max_element = current
                max_index = i
            end
        end

        # Zamiana wierszy w tablicy permutacji
        p[k], p[max_index] = p[max_index], p[k]

        # Tworzenie macierzy górnotrójkątnej
        for i in k+1:lr
            if abs(A_copy[p[k], k]) < 1e-12
                throw(DomainError("Błąd: Element na przekątnej macierzy A[$k, $k] zbyt bliski zeru."))
            end
            m = A_copy[p[i], k] / A_copy[p[k], k]
            A_copy[p[i], k] = 0 
            for j in k+1:lc
                A_copy[p[i], j] -= m * A_copy[p[k], j]
            end
            b_copy[p[i]] -= m * b_copy[p[k]]
        end
    end

    # Rozwiązanie równania za pomocą podstawienia wstecznego
    for i in n:-1:1
        lc = last_column(p[i], 2*l, n)
        sum = 0.0
        for j in i+1:lc
            sum += A_copy[p[i], j] * x[j]
        end
        x[i] = (b_copy[p[i]] - sum) / A_copy[p[i], i]
    end

    return x
end

"""
Funkcja wyznaczająca rozkład LU macierzy A metodą eliminacji Gaussa bez wyboru elementu głównego.
Parametry:
- A: dana macierz o rozmiarze nxn
Returns:
- L:
- U:
"""
function lu(A::SparseMatrixCSC, l::Int64)
    A_copy = copy(A)
    n = size(A_copy, 1)
    L = spzeros(n, n)
    U = spzeros(n, n)

    for k in 1:n-1
        lr = last_row(k, l, n)
        lc = last_column(k, l, n)

        for i in k+1:lr
            if abs(A_copy[k, k]) < 1e-12
                throw(DomainError("Błąd: Element na przekątnej macierzy A[$k, $k] zbyt bliski zeru."))
            end
            m = A_copy[i, k] / A_copy[k, k]
            L[i, k] = m  # Store the multiplier in L

            for j in k+1:lc
                A_copy[i, j] -= m * A_copy[k, j]
            end
        end
    end

    # Rozdzielenie na macierze L i U
    for i in 1:n
        L[i, i] = 1.0  # Jedynki na przekątnej macierzy L
        for j in i:n
            U[i, j] = A_copy[i, j]  # U contains the original upper part of the matrix
        end
    end

    return L, U
end




"""
Funkcja rozwiązująca układ równań Ax=b po wyznaczeniu rozkładu LU bez wyboru głównego elementu.
Parametry: 
- L:
- U: 
- b:
Returns: x
"""
function solve_lu(A::SparseMatrixCSC{Float64}, b::Vector{Float64}, l::Int64)::Vector{Float64}
    A_copy = copy(A)
    b_copy = copy(b)
    n = size(A_copy, 1)
    y = zeros(Float64, n)
    x = zeros(Float64, n)

    # Rozwiązywanie Ly = b (przez podstawianie w przód)
    for i in 1:n
        sum = 0.0
        fc = first_column(i, l)
        for j in fc:i-1
            sum += A_copy[i, j] * y[j]
        end
        y[i] = (b_copy[i] - sum)
    end

    # Rozwiązywanie Ux = y (przez podstawianie wstecz)
    for i in n:-1:1
        sum = 0.0
        lc = last_column(i, l, n)
        for j in i+1:lc
            sum += A_copy[i, j] * x[j]
        end
        x[i] = (y[i] - sum) / A_copy[i, i]
    end

    return x
end

"""
Funkcja wyznaczająca rozkład LU macierzy A metodą eliminacji Gaussa z częściowym wyborem elementu głównego.
Parametry:
- A: dana macierz o rozmiarze nxn
Returns:
"""
function lu_with_main_element_sparse(A::SparseMatrixCSC, l::Int64)
    A_copy = copy(A)
    n = size(A_copy, 1)
    p = collect(1:n)

    for k in 1:n-1
        lr = last_row(k, l, n)
        lc = last_column(k, l, n)
        max_index = k
        max_element = 0.0

        for i in k:lr
            current = abs(A_copy[p[i], k])
            if current > max_element
                max_element = current
                max_index = i
            end
        end

        # Zamiana wierszy w tablicy permutacji
        p[k], p[max_index] = p[max_index], p[k]

        for i in k+1:lr
            if abs(A_copy[p[k], k]) < 1e-12
                throw(DomainError("Błąd: Element na przekątnej macierzy A[$k, $k] zbyt bliski zeru."))
            end
            m = A_copy[p[i], k] / A_copy[p[k], k]  
            A_copy[p[i], k] = m 
            for j in k+1:lc
                A_copy[p[i], j] -= m * A_copy[p[k], j]
            end
        end
    end
    return A_copy, p
end

"""
Funkcja rozwiązująca układ równań Ax=b po wyznaczeniu rozkładu LU z częściowym wyborem głównego elementu.
Parametry: L, U, b, P - wektor permutacji
Returns: x
"""
function solve_lu_with_main_element(A::SparseMatrixCSC, b::Vector{Float64}, p::Vector{Int64}, l::Int64)
    A_copy = copy(A)
    b_copy = copy(b)
    n = size(A_copy, 1)
    x = zeros(Float64, n)
    y = zeros(Float64, n)

    # Rozwiązywanie Ly = b (przez podstawianie w przód)
    for i in 1:n
        sum = 0.0
        fc = first_column(p[i], l)
        for j in fc:i-1
            sum += A_copy[p[i], j] * y[j]
        end
        y[i] = (b_copy[p[i]] - sum)
    end

    # Rozwiązywanie Ux = y (przez podstawianie wstecz)
    for i in n:-1:1
        sum = 0.0
        lc = last_column(p[i], l, n)
        for j in i+1:lc
            sum += A_copy[p[i], j] * x[j]
        end
        x[i] = (y[i] - sum) / A_copy[p[i], i]
    end

    return x
end
"""
Funkcja obliczająca wektor prawych stron b na podstawie macierzy A i wektora x, tj. b = Ax.
Parametry:
- A: rzadka macierz kwadratowa o rozmiarze nxn
- x: wektor wejściowy o długości n
Returns:
- b: wektor prawych stron o długości n
"""
function calculate_b(A::SparseMatrixCSC{Float64})::Vector{Float64}
    n = size(A, 1)
    x = ones(Float64, n)
    if length(x) != n
        throw(DomainError("Długość wektora x musi być zgodna z rozmiarem macierzy A."))
    end
    b = A * x
    return b
end

end
