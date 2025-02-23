# Paweł Krzyszczak 272379

# T: typ dla którego wyliczamy epsilon maszynowy 
# eps_2: funkcja wyliczajaca epsilon maszynowy dla podanego typu
function eps_2(T::Type)
	eps = T(1.0)
	while T(1.0) + eps != T(1.0)
		eps /= 2
	end
	return eps*2
end

eps_float16 = eps(Float16)
eps_float32 = eps(Float32)
eps_float64 = eps(Float64)

eps_2_float16 = eps_2(Float16)
eps_2_float32 = eps_2(Float32)
eps_2_float64 = eps_2(Float64)

println("Epsilon maszynowy dla Float16:")
println("Wbudowany:\t", eps_float16)
println("Moj:\t\t", eps_2_float16)

println("Epsilon maszynowy dla Float32:")
println("Wbudowany:\t", eps_float32)
println("Moj:\t\t", eps_2_float32)

println("Epsilon maszynowy dla Float64:")
println("Wbudowany:\t", eps_float64)
println("Moj:\t\t", eps_2_float64)
