# Paweł Krzyszczak 272379

x = [2.718281828, -3.141592654, 1.414213562, 0.577215664, 0.301029995]
y = [1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049]


function in_order(T::Type)
	S = T(0.0)
	for i in 1:5
		S += T(x[i]) * T(y[i])
	end
	return S
end

function in_reversed_order(T::Type)
	S = T(0.0)
	for i in 5:-1:1
		S += T(x[i]) * T(y[i])
	end
	return S
end

function in_descending_order(T::Type)
	poz_sum = T(0.0)
	neg_sum = T(0.0)
	x_y = []
	for i in 1:5
		push!(x_y,T(x[i])*T(y[i]))
	end
	sort!(x_y, rev=true)
	for i in 1:5
		if T(x_y[i]) > T(0.0)
			 poz_sum+= T(x_y[i])
		end
	end
	for i in 5:-1:1
		if T(x_y[i]) <= T(0.0)
			neg_sum += T(x_y[i])
		end
	end
	return poz_sum+neg_sum
end

function in_ascending_order(T::Type)
	poz_sum = T(0.0)
	neg_sum = T(0.0)
	x_y = []
	for i in 1:5
		push!(x_y,T(x[i])*T(y[i]))
	end
	sort!(x_y, rev=true)
	for i in 5:-1:1
		if T(x_y[i]) > T(0.0)
			 poz_sum+= T(x_y[i])
		end
	end
	for i in 1:5
		if T(x_y[i]) <= T(0.0)
			neg_sum += T(x_y[i])
		end
	end
	return poz_sum+neg_sum
end

println("\t\t\tFloat32\t\tFloat64")
println("In order:\t\t", in_order(Float32), "\t", in_order(Float64))
println("In reversed order:\t", in_reversed_order(Float32), "\t", in_reversed_order(Float64))
println("In descending order:\t", in_descending_order(Float32), "\t\t", in_descending_order(Float64))
println("In ascending order:\t", in_ascending_order(Float32), "\t\t", in_ascending_order(Float64))

