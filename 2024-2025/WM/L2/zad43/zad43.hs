alternatingSum :: [Int] -> Int
alternatingSum xs = foldl (\acc (k, x) -> acc + (if even k then -x else x)) 0 (zip [1..] xs)
