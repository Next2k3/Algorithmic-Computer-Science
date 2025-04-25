countEven :: [Int] -> Int
countEven = foldr (\x acc -> if even x then acc + 1 else acc) 0

--countEven :: [Int] -> Int
--countEven = foldr f 0 where f x acc | even x = acc +1 | otherwise = acc
