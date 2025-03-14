power :: Int -> Int -> Int
power x y = y ^ x

p2 = power 4
p3 = power 3

power = \x y -> y ^ x
p2 = \y -> y ^ 4
p3 = \y -> y ^ 3



