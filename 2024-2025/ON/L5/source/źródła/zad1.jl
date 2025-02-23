# Paweł Krzyszczak 272379
include("blocksys.jl")
using .Blocksys
using SparseArrays

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
    
    # Zapisanie wyników do pliku
    open(file_path, "w") do file
        for xi in x
            write(file, "$(xi)\n")
        end
    end
end

function norma_euklidesowa(v::Vector{Float64})
    return sqrt(sum(x^2 for x in v))
end

function blad_wzgledny(v2::Vector{Float64})
    # Tworzymy wektor jedynek o tej samej długości co v2
    v1 = ones(Float64, length(v2))
    
    # Obliczamy błąd względny dla każdego elementu wektora
    blad_wektora = [abs(v1[i] - v2[i]) / norma_euklidesowa(v1) for i in 1:length(v2)]
    
    return blad_wektora
end



A_file_name = readline()
b_file_name = readline()

A, l = read_A(A_file_name)
b = read_b(b_file_name)

x = Blocksys.gauss_elimination(A, b, l)
#exportx("gauss_elimination",x)
exportx("gauss_elimination_error",blad_wzgledny(x))
#println("Rozwiązanie: ", x)
    
x2 = Blocksys.gauss_elimination_with_main_element(A, b, l)
#exportx("gauss_elimination_with_main_element",x2)
exportx("gauss_elimination_with_main_element_error",blad_wzgledny(x2))
#println("Rozwiązanie: ", x2)
   
x3_L,x3_U = lu(A, l)

x4 = solve_lu(x3_U, b, l)
#exportx("solve_lu",x4)
exportx("solve_lu_error",blad_wzgledny(x4))
#println("Rozwiązanie: ", x4)

x5, P = Blocksys.lu_with_main_element_sparse(A, l)

x6 = Blocksys.solve_lu_with_main_element(x5, b, P, l)
#exportx("solve_lu_with_main_element",x6)
exportx("solve_lu_with_main_element_error",blad_wzgledny(x6))
#println("Rozwiązanie: ", x6)

b_calculated = Blocksys.calculate_b(A)

x7 = Blocksys.gauss_elimination(A,b_calculated,l)
#xportx("gauss_elimination_with_calculate_b", x7)
exportx("gauss_elimination_with_calculate_b_error",blad_wzgledny(x7))
#println("Rozwiązanie: ", x7)


