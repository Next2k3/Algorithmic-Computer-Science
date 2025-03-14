phi :: Int -> Int
phi n = length [k | k <- [1..n] , gcd k n == 1]

sumPhiDivisors :: Int -> Int
sumPhiDivisors n = sum [phi k | k <- [1..n], n `mod` k == 0]

