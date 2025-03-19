splits' :: [a] -> [([a], [a])]
splits' xs = [(take n xs, drop n xs) | n <- [0 .. length xs]]
