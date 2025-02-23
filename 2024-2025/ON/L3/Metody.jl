# Paweł Krzyszczak 272379

module Metody
export mbisekcji, mstycznych, msiecznych

# funkcja wyliczająca przybliżenie funkcji f(x) = 0 metodą bisekcji
# Dane:
#	f – funkcja f(x) zadana jako anonimowa funkcja (ang. anonymous function),
#	a,b – końce przedziału początkowego,
#	delta,epsilon – dokładności obliczeń,
# Wyniki:
#	(r,v,it,err) – czwórka, gdzie
#	r – przybliżenie pierwiastka równania f(x) = 0,
#	v – wartość f(r),
#	it – liczba wykonanych iteracji,
#	err – sygnalizacja błędu:
#		0 - brak błędu
#		1 - funkcja nie zmienia znaku w przedziale [a,b]

function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64)
	v_a::Float64 = f(a)
    v_b::Float64 = f(b)
    len::Float64 = b - a
    
    if sign(v_a) == sign(v_b)
        return Nothing, Nothing, Nothing, 1
    end

    k = 1
    while true
        len = len/2
        m = a + len
        v_m::Float64 = Float64(f(m))
        
        if abs(len) < delta || abs(v_m) < epsilon
            return m, v_m, k, 0
        end
        
        if sign(v_a) != sign(v_m)
            b = m
            v_b = v_m
        else
            a = m
            v_a = v_m
        end
        
        k = k + 1
    end
end

# funkcja wyliczająca przybliżenie funkcji f(x) = 0 metodą Newtona
# Dane:
#	f, pf – funkcją f(x) oraz pochodną pf(x) zadane jako anonimowe funkcje,
#	x0 – przybliżenie początkowe,
#	delta,epsilon – dokładności obliczeń,
#	maxit – maksymalna dopuszczalna liczba iteracji,
# Wyniki:
#	(r,v,it,err) – czwórka, gdzie
#	r – przybliżenie pierwiastka równania f(x) = 0,
#	v – wartość f(r),
#	it – liczba wykonanych iteracji,
#	err – sygnalizacja błędu
#		0 - metoda zbieżna
#		1 - nie osiągnięto wymaganej dokładności w maxit iteracji,
#		2 - pochodna bliska zeru

function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    v::Float64 = f(x0)
    
    if abs(v) < epsilon
        return x0, v, 0, 0
    end
    
    for k in 1:maxit
        v_d::Float64 = pf(x0)
        
        if abs(v_d) < eps(Float64)
            return x0, v, k, 2
        end
        
        x1::Float64 = x0 - v/v_d
        v= f(x1)
        
        if abs(x1-x0) < delta || abs(v) < epsilon
            return x1, v, k, 0
        end
        
        x0 = x1
    end
    return x0, v, maxit, 1
end

# funkcja wyliczająca przybliżenie funkcji f(x) = 0 metodą siecznych
# Dane:
#	f – funkcja f(x) zadana jako anonimowa funkcja,
#	x0,x1 – przybliżenia początkowe,
#	delta,epsilon – dokładności obliczeń,
#	maxit – maksymalna dopuszczalna liczba iteracji,
# Wyniki:
#	(r,v,it,err) – czwórka, gdzie
#	r – przybliżenie pierwiastka równania f(x) = 0,
#	v – wartość f(r),
#	it – liczba wykonanych iteracji,
#	err – sygnalizacja błędu
#		0 - metoda zbieżna
#		1 - nie osiągnięto wymaganej dokładności w maxit iteracji

function msiecznych(f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64,maxit::Int)
    v_x0::Float64 = f(x0)
    v_x1::Float64 = f(x1)
    
    for k in 1:maxit
    
        if abs(v_x0) > abs(v_x1)
            x0, x1 = x1, x0
            v_x0, v_x1 = v_x1, v_x0
        end
        
        s::Float64 = (x1 - x0)/(v_x1 - v_x0)
        x1 = x0 
        v_x1 = v_x0
        x0 = x0 - v_x0*s
        v_x0 = f(x0)
        
        if abs(x1 - x0) < delta || abs(v_x0) < epsilon
            return x0, v_x0, k, 0
        end 
    end
    return x0, v_x0, maxit, 1
end

end

