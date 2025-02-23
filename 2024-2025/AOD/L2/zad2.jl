# Paweł Krzyszczak 272379

using JuMP
using GLPK

function solve_problem(product_profits::Vector, product_costs::Vector, product_demands::Vector, machine_costs::Vector, machine_availibility_times::Vector, machine_product_creation_times::Matrix)
    model = Model(GLPK.Optimizer)
    
    # m - liczba produktów, n - liczba maszyn
    m, n = size(machine_product_creation_times)
    
    # Przekształcamy czas dostępności maszyn z godzin na minuty
    machine_availibility_times *= 60
    # Przekształcamy koszty maszyn z jednostek godzinowych na minutowe
    machine_costs /= 60
    
    # Deklarujemy zmienną decyzyjną: ilość wyprodukowana dla każdego produktu
    @variable(model, amount_produced[1:m] >= 0)
    
    # Ograniczenie: całkowity czas użycia maszyn nie może przekroczyć ich dostępności
    @constraint(model, [j in 1:n], sum(amount_produced[i] * machine_product_creation_times[i, j] for i in 1:m) <= machine_availibility_times[j])
    
    # Ograniczenie: ilość wyprodukowanych produktów nie może przekroczyć popytu
    @constraint(model, amount_produced .<= product_demands)
    
    # Funkcja celu: maksymalizacja zysku
    # Zysk = (zysk jednostkowy - koszt jednostkowy) * ilość wyprodukowana
    # Od tego odejmujemy koszt użytkowania maszyn
    @objective(model, Max, sum((product_profits[i] - product_costs[i]) * amount_produced[i] for i in 1:m) - sum(machine_costs[j] * sum(machine_product_creation_times[i, j] * amount_produced[i] for i in 1:m) for j in 1:n))
    
    optimize!(model)
    
    if termination_status(model) == MOI.OPTIMAL
        maximum_profit = objective_value(model)
        println("Maximum profit: $maximum_profit\n")
        println("Optimal amounts to produce:")
        display(value.(amount_produced))
        println()
    elseif termination_status(model) == MOI.INFEASIBLE
        println("The model is infeasible.")
        return nothing
    else
        println("No optimal solution found.")
        return nothing
    end
end



product_profits = [9, 7, 6, 5]
product_costs = [4, 1, 1, 1]
product_demands = [400, 100, 150, 500]
machine_costs = [2, 2, 3]
machine_availibility_times = [60, 60, 60]
machine_product_creation_times = [5 10 6;
								  3 6 4;
								  4 5 3;
								  4 2 1]

solve_problem(product_profits, product_costs, product_demands, machine_costs, machine_availibility_times, machine_product_creation_times )
