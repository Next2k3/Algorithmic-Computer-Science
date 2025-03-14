myMap :: (a -> b) -> [a] -> [b]
myMap _ [] = []
myMap f (x:xs) = f x : myMap f xs

myZip :: [a] -> [b] -> [(a,b)]
myZip [] _ = []
myZip _ [] = []
myZip (x:xs) (y:ys) = (x, y) : myZip xs ys

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith _ [] _ = []
myZipWith _ _ [] = []
myZipWith f (x:xs) (y:ys) = f x y : myZipWith f xs ys

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []
myFilter p (x:xs)| p x = x : myFilter p xs| otherwise = myFilter p xs

myTake :: Int -> [a] -> [a]
myTake _ [] = []
myTake n (x:xs) | n <= 0 = [] | otherwise = x : myTake (n-1) xs

myDrop :: Int -> [a] -> [a]
myDrop _ [] = []
myDrop n (x:xs) | n <= 0 = x:xs | otherwise = myDrop (n-1) xs 

