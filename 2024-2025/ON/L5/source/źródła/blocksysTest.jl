# Paweł Krzyszczak 272379
include("blocksys.jl")
using .Blocksys
using Test
using SparseArrays

# Testowanie funkcji calculate_b
function test_calculate_b()
    # Testowy przykład macierzy rzadkiej
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 1.0
    A[2, 2] = 2.0
    A[3, 3] = 3.0
    A[4, 4] = 4.0
    A[5, 5] = 5.0
    A[6, 6] = 6.0
    x = ones(Float64, n)
    
    b = calculate_b(A)
    
    # Oczekujemy, że b = A * x, czyli b[i] = A[i,i] dla tego przykładu
    expected_b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    
    @test isapprox(b, expected_b, atol=1e-8)  # Porównanie wektorów z tolerancją
end

# Testowanie funkcji gauss_elimination
function test_gauss_elimination()
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 2.0
    A[2, 2] = 3.0
    A[3, 3] = 4.0
    A[4, 4] = 5.0
    A[5, 5] = 6.0
    A[6, 6] = 7.0
    b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    
    x = gauss_elimination(A, b, l)
    
    # Proste oczekiwania dla tego przykładu
    expected_x = [0.5, 0.6666666666666666, 0.75, 0.8, 0.8333333333333334, 0.8571428571428571]
    
    @test isapprox(x, expected_x, atol=1e-8)  # Porównanie wektorów z tolerancją
end

# Testowanie funkcji gauss_elimination_with_main_element
function test_gauss_elimination_with_main_element()
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 2.0
    A[2, 2] = 3.0
    A[3, 3] = 4.0
    A[4, 4] = 5.0
    A[5, 5] = 6.0
    A[6, 6] = 7.0
    b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    
    x = gauss_elimination_with_main_element(A, b, l)
    
    # Proste oczekiwania dla tego przykładu
    expected_x = [0.5, 0.6666666666666666, 0.75, 0.8, 0.8333333333333334, 0.8571428571428571]
    
    @test isapprox(x, expected_x, atol=1e-8)  # Porównanie wektorów z tolerancją
end

# Testowanie funkcji lu
function test_lu()
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 2.0
    A[2, 2] = 3.0
    A[3, 3] = 4.0
    A[4, 4] = 5.0
    A[5, 5] = 6.0
    A[6, 6] = 7.0
    
    L, U = lu(A, l)
    
    # Oczekiwana postać rozkładu LU - musisz podać właściwe oczekiwania
    # W tym przypadku zakładamy, że L i U powinny być odpowiednio rozkładem LU
    expected_L = sparse([1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6], [1.0, 1.0, 1.0, 1.0, 1.0, 1.0], 6, 6)  # Przykład, dostosuj do swoich oczekiwań
    expected_U = sparse([1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6], [2.0, 3.0, 4.0, 5.0, 6.0, 7.0], 6, 6) # Przykład, dostosuj do swoich oczekiwań

    @test isapprox(L, expected_L, atol=1e-8)
    @test isapprox(U, expected_U, atol=1e-8)
end

# Testowanie funkcji solve_lu
function test_solve_lu()
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 2.0
    A[2, 2] = 3.0
    A[3, 3] = 4.0
    A[4, 4] = 5.0
    A[5, 5] = 6.0
    A[6, 6] = 7.0
    b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    
    L, U = lu(A, l)
    x = solve_lu(U, b, l)
    # Przykładowe oczekiwania dla tego testu
    expected_x = [0.5, 0.6666666666666666, 0.75, 0.8, 0.8333333333333334, 0.8571428571428571]
    
    @test isapprox(x, expected_x, atol=1e-8)
end

# Testowanie rozkładu LU z głównym elementem
function test_lu_with_main_element()
    n = 6
    l = 2
    A = spzeros(n, n)
    A[1, 1] = 2.0
    A[2, 2] = 3.0
    A[3, 3] = 4.0
    A[4, 4] = 5.0
    A[5, 5] = 6.0
    A[6, 6] = 7.0
    b = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    LU, p = lu_with_main_element_sparse(A, l)
    x = solve_lu_with_main_element(LU, b, p, l)
    
    # Oczekiwanie dla tego przykładu
    expected_x = [0.5, 0.6666666666666666, 0.75, 0.8, 0.8333333333333334, 0.8571428571428571]
    
    @test isapprox(x, expected_x, atol=1e-8)
end

# Uruchamianie testów
test_calculate_b()
test_gauss_elimination()
test_gauss_elimination_with_main_element()
test_lu()
test_solve_lu()
test_lu_with_main_element()

