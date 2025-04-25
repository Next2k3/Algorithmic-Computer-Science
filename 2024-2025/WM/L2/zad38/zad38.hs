dec2Int :: [Int] -> Int
dec2Int = foldl (\acc x -> acc * 10 + x) 0
