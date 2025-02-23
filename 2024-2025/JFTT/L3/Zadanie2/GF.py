def gf_format(x: int, P: int) -> int:
    """Zwraca wartość x w formacie modulo P, zapewniając, że wynik jest dodatni."""
    return (x % P + P) % P

def multiply(base: int, exponent: int, P: int) -> int:
    """Mnoży base i exponent w ciele skończonym o porządku P."""
    result = gf_format(base, P)
    for _ in range(1, exponent):
        result = gf_format(result + base, P)
    return result

def inverse(a: int, P: int) -> int:
    """Oblicza odwrotność liczby a modulo P za pomocą algorytmu Euklidesa rozszerzonego."""
    mod = P
    x = 1  # x będzie przechowywać współczynnik odwrotności
    y = 0  # y będzie pomocniczym współczynnikiem
    
    while a > 1:
        quotient = a // mod  # Oblicza iloraz
        remainder = a % mod  # Oblicza resztę
        
        # Zaktualizowanie zmiennych
        a = mod
        mod = remainder
        x, y = y, x - quotient * y
    
    # Jeśli x jest ujemne, dodajemy P, aby uzyskać dodatnią odwrotność
    if x < 0:
        x += P

    return x

