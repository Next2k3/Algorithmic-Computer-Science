dotprod :: (Num a) => [a] -> [a] -> a
dotprod xs ys = foldl (+) 0 (zipWith (*) xs ys)
