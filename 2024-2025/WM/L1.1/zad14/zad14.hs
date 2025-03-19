-- Funkcja obliczająca sumę dzielników liczby n
sumOfDivisors :: Int -> Int
sumOfDivisors n = sum [d | d <- [1..n-1], n `mod` d == 0]

-- Funkcja sprawdzająca, czy liczba jest doskonała
isPerfect :: Int -> Bool
isPerfect n = sumOfDivisors n == n

-- Lista liczb doskonałych mniejszych od 10000
perfectNumbers :: [Int]
perfectNumbers = [n | n <- [1..9999], isPerfect n]

main :: IO ()
main = print perfectNumbers
