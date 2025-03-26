bubblePass :: (Ord a) => [a] -> [a]
bubblePass [] = [] 
bubblePass [x] = [x]  
bubblePass (x:y:xs)
    | x > y     = y : bubblePass (x:xs) 
    | otherwise = x : bubblePass (y:xs) 
