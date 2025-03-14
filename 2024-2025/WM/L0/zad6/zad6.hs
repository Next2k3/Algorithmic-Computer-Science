curry2 :: ((a,b)-> c) -> a -> b -> c
curry2 f x y = f (x,y)

uncurry2 :: (a -> b -> c) -> (a, b) -> c
uncurry2 f (x, y) = f x y

