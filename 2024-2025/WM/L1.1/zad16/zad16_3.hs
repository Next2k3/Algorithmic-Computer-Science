import Data.Ratio ( (%) )
import Data.Function (fix)

-- Funkcja rekurencyjna licząca dcp(n)
dcpRec :: Int -> Int -> Int
dcpRec n 0 = 0
dcpRec n k = (length [l | l <- [1..n], gcd k l == 1]) + dcpRec n (k-1)

dcp :: Int -> Double
dcp n = fromIntegral (dcpRec n n) / fromIntegral (n * n)

main :: IO ()
main = mapM_ (print . (\n -> (n, dcp n))) [100,200..10000]
