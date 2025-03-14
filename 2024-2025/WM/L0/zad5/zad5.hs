f = \x -> 1 + x * (x + 1)
g = \x y -> x + y^2
h = \y x -> x + y^2

main = print (f 2, g 2 3, h 3 2)

