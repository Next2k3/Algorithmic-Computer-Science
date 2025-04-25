remdupl :: Eq a => [a] -> [a]
remdupl = foldr addIfDifferent [] 
	where 
	addIfDifferent x [] = [x]
	addIfDifferent x (y:ys)
		| x == y = y:ys
		| otherwise = x:y:ys		
