# Paweł Krzyszczak 272379

using JuMP
import GLPK

function solve_jet_fuel_problem(fuel_supply::Vector, fuel_demand::Vector, fuel_prices::Matrix)
    model = Model(GLPK.Optimizer)

    m, n = size(fuel_prices)  # Liczba lotnisk (m) i firm (n)

    # Zmienne decyzyjne: ilość paliwa dostarczonego przez firmę i do lotniska
    @variable(model, fuel_amount_matrix[1:m, 1:n] >= 0)

    # Ograniczenia: każda firma nie może przekroczyć swojego limitu dostaw
    @constraint(model, [i in 1:n], sum(fuel_amount_matrix[:, i]) <= fuel_supply[i])

    # Ograniczenia: każde lotnisko musi otrzymać dokładnie wymaganą ilość paliwa
    @constraint(model, [j in 1:m], sum(fuel_amount_matrix[j, :]) == fuel_demand[j])

    # Funkcja celu: minimalizacja kosztów dostaw
    @objective(model, Min, sum(fuel_prices[j, i] * fuel_amount_matrix[j, i] for j in 1:m, i in 1:n))

    # Rozwiązywanie modelu
    optimize!(model)

    # Minimalny koszt
    minimal_cost = objective_value(model)
    println("Minimalny koszt dostaw: $minimal_cost")

    # Ilości paliwa dostarczonego przez firmy na lotniska
    fuel_delivery = value.(fuel_amount_matrix)
    println("Plan dostaw paliwa (ilość paliwa dostarczona przez firmy do lotnisk):")
    display(fuel_delivery)

    # Odpowiedzi na pytania
    all_firms_deliver = all(sum(fuel_delivery[:, i]) > 0 for i in 1:n)
    println("Czy wszystkie firmy dostarczają paliwo? ", all_firms_deliver)

    supply_fully_used = all(sum(fuel_delivery[:, i]) == fuel_supply[i] for i in 1:n)
    println("Czy możliwości dostaw paliwa przez firmy zostały wyczerpane? ", supply_fully_used)
end

# Dane wejściowe
fuel_supply_from_companies = [275000, 550000, 660000]  # Dostępne ilości paliwa u firm
fuel_demand_on_airports = [110000, 220000, 330000, 440000]  # Wymagania paliwowe lotnisk
fuel_prices = [10 7 8; 10 11 14; 9 12 4; 11 13 9]  # Koszt dostaw [lotnisko, firma]

# Rozwiązanie problemu
solve_jet_fuel_problem(fuel_supply_from_companies, fuel_demand_on_airports, fuel_prices)
