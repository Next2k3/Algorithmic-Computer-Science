module W04a where

import Data.List

sum' xs = foldl (+) 0 xs
product' xs = foldl (*) 1 xs
minimum' xs = foldl1 min xs
maximum' xs = foldl1 max xs 
and' xs = foldl (&&) True xs
or' xs = foldl (||) False xs
concat' xxs = foldl (++) [] xxs
concatMap' f  = foldl ((++).f) []

runDFA :: (s -> c ->s) -> s -> [c] -> s
--runDFA delta start cs = foldl delta start cs
runDFA = foldl

acceptDFA :: (s -> c -> s) -> s -> (s -> Bool) -> [c] -> Bool
acceptDFA delta start accept cs = accept (runDFA delta start cs)

delta 1 '1' = 2
delta 1 _   = 1
delta 2 '1' = 1
delta 2 _   = 2
delta _ _   = 1 

myrepeat x = x:myrepeat x

repeat' x = xs where xs = x : xs

cycle' [] = error "cycle: emptyList"
cycle' xs = xs' where xs' = xs ++ xs'

myiterate :: (a -> a) -> a -> [a]
myiterate f x = x : myiterate f (f x)

approSqrt :: Double -> [Double]
approSqrt a = iterate (\x->(x+a/x)/2) a

fibb = 0:1: zipWith (-) fibb (tail fibb)

sieve (p:xs) = p : sieve (filter (\n -> mod n p /= 0) xs)
primes = sieve [2..]

better_sieve (p:xs) = p: sieve (filter(\n -> n<p*p || (mod n p /= 0)) xs)
better_primes = better_sieve [2..]

addGF xs ys = zipWith (+) xs ys

