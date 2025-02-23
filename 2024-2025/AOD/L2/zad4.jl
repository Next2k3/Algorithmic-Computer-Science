# Paweł Krzyszczak

using JuMP
using GLPK

# Funkcja pomocnicza do wypisania wykorzystanych łuków w rozwiązaniu
function print_used_arches(matrix)
    rows, cols = size(matrix)
    for i in 1:rows
        for j in 1:cols
            if matrix[i, j] != 0.0
                println("($i, $j)")  
            end
        end
    end
end

function solve_problem(cities::Int, starting_city::Int, ending_city::Int, max_time::Int, arches_data::Vector{Vector{Int}})

    arches_matrix = zeros(cities, cities)  # Macierz określająca istnienie łuku między miastami
    costs_matrix = zeros(cities, cities)   # Macierz kosztów dla każdego łuku
    times_matrix = zeros(cities, cities)   # Macierz czasów przejazdu dla każdego łuku


    for arch in arches_data
        i, j, c_ij, t_ij = arch
        arches_matrix[i, j] = 1       
        costs_matrix[i, j] = c_ij        
        times_matrix[i, j] = t_ij       
    end

    model = Model(GLPK.Optimizer)

    # Zmienna decyzyjna: macierz binarna wskazująca, czy dany łuk jest użyty (1) czy nie (0)
    @variable(model, 0 <= arches_used[1:cities, 1:cities] <= 1, Int)

    # Ograniczenie: można używać tylko istniejących łuków
    @constraint(model, arches_used .<= arches_matrix)

    # Ograniczenie: ścieżka musi zaczynać się w mieście początkowym
    @constraint(model, sum(arches_used[starting_city, :]) == 1)  # Dokładnie jeden łuk wychodzi z miasta początkowego
    @constraint(model, sum(arches_used[:, starting_city]) == 0) # Nie ma łuków wchodzących do miasta początkowego

    # Ograniczenie: ścieżka musi kończyć się w mieście końcowym
    @constraint(model, sum(arches_used[:, ending_city]) == 1)  # Dokładnie jeden łuk wchodzi do miasta końcowego
    @constraint(model, sum(arches_used[ending_city, :]) == 0)  # Nie ma łuków wychodzących z miasta końcowego

    # Ograniczenie zachowania przepływu: liczba łuków wchodzących = liczba łuków wychodzących dla każdego miasta pośredniego
    for i in 1:cities
        if i != starting_city && i != ending_city
            @constraint(model, sum(arches_used[i, :]) == sum(arches_used[:, i]))
        end
    end

    # Ograniczenie na maksymalny czas przejazdu: całkowity czas musi być mniejszy lub równy maksymalnemu dozwolonemu czasowi
    @constraint(model, sum(arches_used .* times_matrix) <= max_time)

    # Funkcja celu: minimalizacja całkowitego kosztu przejazdu
    @objective(model, Min, sum(arches_used .* costs_matrix))


    optimize!(model)


    if termination_status(model) == MOI.OPTIMAL
        minimal_cost = objective_value(model) 
        println("Minimalny koszt: $minimal_cost")
        print_used_arches(value.(arches_used))
    elseif termination_status(model) == MOI.INFEASIBLE
        println("Model jest niewykonalny.")  
        return nothing
    else
        println("Nie znaleziono optymalnego rozwiązania.") 
        return nothing
    end
end

# Dane do podpunktu (a)
cities = 10
starting_city = 1
ending_city = 10
max_time = 15
arches_data = [[1, 2, 3, 4], 
[1, 3, 4, 9], 
[1, 4, 7, 10], 
[1, 5, 8, 12], 
[2, 3, 2, 3], 
[3, 4, 4, 6], 
[3, 5, 2, 2], 
[3, 10, 6, 11], 
[4, 5, 1, 1], 
[4, 7, 3, 5], 
[5, 6, 5, 6], 
[5, 7, 3, 3], 
[5, 10, 5, 8], 
[6, 1, 5, 8], 
[6, 7, 2, 2], 
[6, 10, 7, 11], 
[7, 3, 4, 6], 
[7, 8, 3, 5], 
[7, 9, 1, 1], 
[8, 9, 1, 2], 
[9, 10, 2, 2]]


solve_problem(cities, starting_city, ending_city, max_time, arches_data)

# Dane przykładowe do podpunktu (b)
my_cities = 10
my_starting_city = 1
my_ending_city = 10
my_max_time = 18
my_arches_data = [
[1, 2, 3, 4],
[1, 3, 5, 6],
[1, 4, 8, 7],
[1, 7, 2, 10],
[2, 5, 2, 3],
[2, 6, 4, 6],
[3, 5, 3, 2],
[3, 6, 4, 4],
[4, 6, 1, 2],
[4, 7, 2, 5],
[5, 8, 3, 3],
[6, 9, 6, 5],
[7, 9, 7, 3],
[7, 10, 1, 10],
[8, 10, 5, 6],
[9, 10, 2, 3]]


solve_problem(my_cities, my_starting_city, my_ending_city, my_max_time, my_arches_data)


