-- Funkcja obliczająca sumę dzielników właściwych liczby n
sumOfDivisors :: Int -> Int
sumOfDivisors n = sum [d | d <- [1..n `div` 2], n `mod` d == 0]

-- Funkcja znajdująca wszystkie pary zaprzyjaźnione
amicablePairs :: Int -> [(Int, Int)]
amicablePairs limit = [(m, n) | m <- [1..limit-1], 
                                let n = sumOfDivisors m, 
                                n > m, n < limit, 
                                sumOfDivisors n == m]

main :: IO ()
main = print $ amicablePairs 100000

