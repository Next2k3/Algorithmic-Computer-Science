# Paweł Krzyszczak 272379
include("blocksys.jl")
using .Blocksys
using SparseArrays
using LinearAlgebra

function read_A(file_path::String)
    # Open file to read matrix data
    input_file = open(file_path, "r")

    # Read total elements and matrix size from the first line
    total_elements, matrix_size = parse.(Int, split(readline(input_file)))  # total_elements = liczba elementów, matrix_size = rozmiar macierzy


    # Initialize sparse matrices
    matrix = spzeros(total_elements, total_elements) 

    # Read the rest of the file to populate the matrices
    for line in eachline(input_file)
        split_data = split(line)
        i = parse(Int, split_data[1])
        j = parse(Int, split_data[2])
        value = parse(Float64, split_data[3])

        matrix[i,j]=value
    end

    close(input_file)

    return matrix, matrix_size
end

function read_b(file_path::String)
    input_file = open(file_path, "r")
    
    n = parse(Int, readline(input_file))

    float_array = Float64[]

    for _ in 1:n
        push!(float_array, parse(Float64, readline(input_file)))
    end
    
    close(input_file)
    
    return float_array
end

function exportx(file_name::String, x::Vector{Float64})
    # Tworzenie folderu, jeśli nie istnieje
    mkpath("../result")
    
    # Ścieżka do pliku
    file_path = joinpath("../result", file_name)
    relative_error = getRelaitveError(x,ones(size(x)))
    # Zapisanie wyników do pliku
    open(file_path, "w") do file
    	write(file, "$(relative_error)\n")
        for xi in x
            write(file, "$(xi)\n")
        end
    end
end

function norma_euklidesowa(v::Vector{Float64})
    return sqrt(sum(x^2 for x in v))
end

function getRelaitveError(x_computed::Vector{Float64}, x_real::Vector{Float64})
    # Compute relative error
    n = length(x_computed)
    diff = x_computed - x_real
    norm_diff = norm(diff)
    norm_x = norm(x_real)
    return norm_diff / norm_x
end



A_file_name = readline()
b_file_name = readline()

A, l = read_A(A_file_name)
b = read_b(b_file_name)

#x = Blocksys.gauss_elimination(A, b, l)
#exportx("gauss_elimination",x)
#exportx("gauss_elimination_error",blad_wzgledny(x))
#println("Rozwiązanie: ", x)
    
#x2 = Blocksys.gauss_elimination_with_main_element(A, b, l)
#exportx("gauss_elimination_with_main_element",x2)
#exportx("gauss_elimination_with_main_element_error",blad_wzgledny(x2))
#println("Rozwiązanie: ", x2)
   
#x3_L,x3_U = lu(A, l)

#x4 = solve_lu(x3_U, b, l)
#exportx("solve_lu",x4)
#exportx("solve_lu_error",blad_wzgledny(x4))
#println("Rozwiązanie: ", x4)

#x5, P = Blocksys.lu_with_main_element_sparse(A, l)

#x6 = Blocksys.solve_lu_with_main_element(x5, b, P, l)
#exportx("solve_lu_with_main_element",x6)
#exportx("solve_lu_with_main_element_error",blad_wzgledny(x6))
#println("Rozwiązanie: ", x6)

b_calculated = Blocksys.calculate_b(A)

x7 = Blocksys.gauss_elimination(A,b_calculated,l)
#xportx("gauss_elimination_with_calculate_b", x7)
exportx("gauss_elimination_with_calculate_b_error",x7)
#println("Rozwiązanie: ", x7)

x8 = Blocksys.gauss_elimination_with_main_element(A,b_calculated,l)
exportx("gauss_elimination_with_main_element_and_calculate_b_error",x8)

#x, y = Blocksys.lu(A, l)
#x9 = Blocksys.solve_lu(x, b_calculated, l)
#exportx("solve_lu_with_calculate_b_error",x9)

#x2 , P = Blocksys.lu_with_main_element_sparse(A, l)
	
#x10 = Blocksys.solve_lu_with_main_element(x2,b_calculated,P, l)
#exportx("solve_lu_with_calculated_b_with_main_element_error",x10)

