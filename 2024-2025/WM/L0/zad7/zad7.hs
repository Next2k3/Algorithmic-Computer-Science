f1 :: (Int -> Int) -> Int
f1 g = g 5

f2 :: (Int -> Int) -> (Int -> Int)
f2 g = \x -> g (g x)

f3 :: (Int -> Int) -> (Int -> Int) -> (Int -> Int)
f3 g h = \x -> g (h x)
