module W3 where

qS [] = []
qS (x:xs) = (qS [y| y<-xs, y<x]) ++ [x] ++ (qS [y| y<-xs, y>=x])

partition :: (a->Bool) -> [a] -> ([a],[a])
partition _ [] = ([],[])
partition p (x:xs) = if p x then (x:l, r)
                            else (l, x:r)
  where (l,r) = partition p xs

qSort [] = []
qSort [x] = [x]
qSort (x:xs) = (qSort l) ++ (x:qSort r)
  where (l,r) = partition (<x) xs

inSort [] = []
inSort (x:xs) = l ++ [x] ++ r
  where sxs = inSort xs
        (l,r) = partition (<x) sxs

zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x,y): (zip' xs ys)
        
add [] = 0
add (x:xs) = x + add xs 

pro [] = 1
pro (x:xs) = x * pro xs

myfoldr op e [] = e
myfoldr op e (x:xs) = op x (myfoldr op e xs)

myfoldl op e [] = e
myfoldl op e (x:xs) = foldl op (op e x) xs


