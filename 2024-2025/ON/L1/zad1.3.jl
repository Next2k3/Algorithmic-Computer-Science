# Paweł Krzyszczak 272379

# T: typ dla którego wyliczamy max maszynowy
# max: funkcja wyliczajaca max maszynowy dla podanego typu

function max(T::Type)
	value = T(1.0)
	prev_value = T(1.0)
	while value - prev_value < 1.0
		prev_value /= 2
	end
	value = value - (prev_value * 2)
	while !isinf(value * 2)
		value *= 2
	end
	return value
end

max_float16 = floatmax(Float16)
max_float32 = floatmax(Float32)
max_float64 = floatmax(Float64)

max_2_float16 = max(Float16)
max_2_float32 = max(Float32)
max_2_float64 = max(Float64)

println("Maximum dla Float16:")
println("Wbudowany:\t", max_float16)
println("Moj:\t\t", max_2_float16)

println("Maximum dla Float32:")
println("Wbudowany:\t", max_float32)
println("Moj:\t\t", max_2_float32)

println("Maximum dla Float16:")
println("Wbudowany:\t", max_float16)
println("Moj:\t\t", max_2_float16)
