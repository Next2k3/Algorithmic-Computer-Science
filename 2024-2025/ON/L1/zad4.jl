# Paweł Krzyszczak 272379

# find_x: funkcja zwracająca minimalna liczbe 1 < x < 2 , która spełnia x(1/x) != 1 lub nothing w przeciwnym wypadku
function find_x()
	for x in 1.0:1e-16:2.0
		if x * (1/x) != 1.0
            return x  # zwracamy pierwsze x, które spełnia warunek
        end
    end
    return nothing  # jeśli nie znaleziono takiego x
end

x = find_x()
if x != nothing
	println("Znalezione x:", x)
	println("Sprawdzenie: x * (1/x) =", x * (1/x))
	println("W zapisie bitowym: ", bitstring(x))
else
	println("Nie znaleziono x")
end
