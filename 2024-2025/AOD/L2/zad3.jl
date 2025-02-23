# Paweł Krzyszczak 272379

using JuMP
import GLPK

function solve_problem(
    production_costs_per_unit::Vector, 
    production_costs_per_additional_unit::Vector,  
    max_basic_units_to_produce::Vector,  
    max_additional_units_to_produce::Vector,  
    demand_in_units::Vector,  
    initial_units_in_storage::Int, 
    max_units_in_storage::Int,  
    storage_cost_per_unit::Int  
)

    model = Model(GLPK.Optimizer)

    # Liczba okresów
    K = length(production_costs_per_unit)
    
    # Zmienne decyzyjne
    @variable(model, basic_units_produced[1:K] >= 0)  # Produkcja w trybie normalnym w każdym okresie
    @variable(model, additional_units_produced[1:K] >= 0)  # Produkcja w trybie ponadwymiarowym w każdym okresie
    @variable(model, stored_units[1:K+1] >= 0)  # Liczba jednostek magazynowanych na koniec każdego okresu (łącznie z ostatnim okresem)

    # Ograniczenia dotyczące maksymalnej produkcji
    @constraint(model, basic_units_produced .<= max_basic_units_to_produce)  # Produkcja w trybie normalnym nie może przekraczać limitu
    @constraint(model, additional_units_produced .<= max_additional_units_to_produce)  # Produkcja w trybie ponadwymiarowym nie może przekraczać limitu

    # Ograniczenia dotyczące magazynowania
    @constraint(model, [j in 1:K], stored_units[j] <= max_units_in_storage)  # Magazynowanie nie może przekraczać maksymalnej pojemności magazynu

    # Równanie bilansu zapotrzebowania
    @constraint(model, [j in 1:K], 
        stored_units[j+1] == basic_units_produced[j] + additional_units_produced[j] + stored_units[j] - demand_in_units[j]
    )

    # Ograniczenie: na końcu okresu nie może być zapasów
    @constraint(model, stored_units[K+1] == 0)

    # Ograniczenie: początkowy stan magazynu
    @constraint(model, stored_units[1] == initial_units_in_storage)

    # Funkcja celu: minimalizacja całkowitego kosztu
    @objective(
        model, Min,
        sum(production_costs_per_unit .* basic_units_produced) +  # Koszt produkcji normalnej
        sum(production_costs_per_additional_unit .* additional_units_produced) +  # Koszt produkcji ponadwymiarowej
        sum(stored_units .* storage_cost_per_unit)  # Koszt magazynowania
    )

    optimize!(model)
    
    if termination_status(model) == MOI.OPTIMAL
        println("Cost: $(objective_value(model))") 
        println("Basic units produced: $(value.(basic_units_produced))") 
        println("Additional units produced: $(value.(additional_units_produced))")  
        println("Stored units: $(value.(stored_units))")  
    elseif termination_status(model) == MOI.INFEASIBLE
        println("The model is infeasible.") 
        return nothing
    else
        println("No optimal solution found.")  
        return nothing
    end
end

production_costs_per_unit = [6000, 4000, 8000, 9000] 
production_costs_per_additional_unit = [8000, 6000, 10000, 11000] 
max_basic_units_to_produce = [100, 100, 100, 100]  
max_additional_units_to_produce = [60, 65, 70, 60]
demand_in_units = [130, 80, 125, 195]  
initial_units_in_storage = 15  
max_units_in_storage = 70  
storage_cost_per_unit = 1500  

solve_problem(
    production_costs_per_unit,
    production_costs_per_additional_unit,
    max_basic_units_to_produce,
    max_additional_units_to_produce,
    demand_in_units,
    initial_units_in_storage,
    max_units_in_storage,
    storage_cost_per_unit
)

