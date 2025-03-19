import Data.Ratio ( (%) )
import Data.List (genericLength)
import Data.Function (fix)
import Data.Set (fromList, size)

-- Funkcja licząca dcp(n) za pomocą list comprehension
dcpListComp :: Int -> Double
dcpListComp n = fromIntegral coprimeCount / fromIntegral (n * n)
  where
    coprimeCount = length [(k, l) | k <- [1..n], l <- [1..n], gcd k l == 1]

main :: IO ()
main = print $ dcpListComp 100  -- Przykładowe wywołanie

