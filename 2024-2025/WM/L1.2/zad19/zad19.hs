tails' :: (Eq a) => [a] -> [[a]]
tails' xs = reverse (helper xs) where 

helper [] = [[]] 
helper (x:xs) = (x:xs) : helper xs


