#Paweł Krzyszczak 272379

# Kroki w przedziale [1, 2] z krokiem δ = 2^-52
delta = 2.0^(-52)

println("Liczby zmiennopozycyjne w przedziale [1, 2]:")

# Wyświetlanie pierwszych 4 wartości
for k in 0:3
    x = 1.0 + k * delta
    println("bitstring: ", bitstring(x))
end

println("...")

# Wyświetlanie ostatnich 4 wartości
for k in (2^52-3):(2^52)
    x = 1.0 + k * delta
    println("bitstring: ", bitstring(x))
end

println("\nLiczby zmiennopozycyjne w przedziale [1/2, 1]:")

# Wyświetlanie pierwszych 4 wartości
for k in 0:3
    x = 0.5 + k * delta
    println("bitstring: ", bitstring(x))
end

println("...")

# Wyświetlanie ostatnich 4 wartości
for k in (2^51-3):(2^51)
    x = 0.5 + k * delta
    println("bitstring: ", bitstring(x))
end

println("\nLiczby zmiennopozycyjne w przedziale [2, 4]:")

# Wyświetlanie pierwszych 4 wartości
for k in 0:3
    x = 2.0 + k * delta
    println("bitstring: ", bitstring(x))
end

println("...")

# Wyświetlanie ostatnich 4 wartości
for k in (2^52-3):(2^52)
    x = 2.0 + k * delta
    println("bitstring: ", bitstring(x))
end

