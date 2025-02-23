#Paweł Krzyszczak 272379

# T: typ dla którego wyliczamy eta maszynowy
# eta: funkcja wyliczajaca eta maszynowy dla podanego typu
 
function eta(T::Type)
	eta = T(1.0)
	while eta / 2 > 0.0
		eta /= 2
	end
	return eta
end

eta_float16 = nextfloat(Float16(0.0))
eta_float32 = nextfloat(Float32(0.0))
eta_float64 = nextfloat(Float64(0.0))

eta_2_float16 = eta(Float16)
eta_2_float32 = eta(Float32)
eta_2_float64 = eta(Float64)

println("Eta dla Float16:")
println("Wbudowany:\t", eta_float16)
println("Moj:\t\t", eta_2_float16)

println("Eta dla Float32:")
println("Wbudowany:\t", eta_float32)
println("Moj:\t\t", eta_2_float32)

println("Eta dla Float64:")
println("Wbudowany:\t", eta_float64)
println("Moj:\t\t", eta_2_float64)
