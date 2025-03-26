mytakeWhile p [] = []
mytakeWhile p (x:xs) = if p x then x : takeWhile p xs else []

mydropWhile p [] = []
mydropWhile p (x:xs) = if p x then dropWhile p xs else x:xs


