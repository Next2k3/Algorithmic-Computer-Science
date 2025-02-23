# Paweł Krzysczak 272379

# T: typ dla którego wyliczamy epsilon maszynowy 
# Kahans_eps: funckja wyliczjaca epsilon maszynowy wedlug metody Kahana dla podanego typu
function Kahans_eps(T::Type)
	return T(3.0)*(T(4.0) / T(3.0) - T(1.0)) - T(1.0)
end

eps_float16 = eps(Float16)
eps_float32 = eps(Float32)
eps_float64 = eps(Float64)

eps_2_float16 = Kahans_eps(Float16)
eps_2_float32 = Kahans_eps(Float32)
eps_2_float64 = Kahans_eps(Float64)

println("Epsilon maszynowy dla Float16:")
println("Wbudowany:\t", eps_float16)
println("Kahans:\t\t", eps_2_float16)

println("Epsilon maszynowy dla Float32:")
println("Wbudowany:\t", eps_float32)
println("Kahans:\t\t", eps_2_float32)

println("Epsilon maszynowy dla Float64:")
println("Wbudowany:\t", eps_float64)
println("Kahans:\t\t", eps_2_float64)
