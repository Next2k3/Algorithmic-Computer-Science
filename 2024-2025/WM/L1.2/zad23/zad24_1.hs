import Data.List (permutations)

isValid :: [Int] -> Bool
isValid perm = all safe [(i, perm !! i) | i <- [0..length perm - 1]]
  where
    safe (i, x) = all (\(j, y) -> abs (x - y) /= abs (i - j)) 
                      [(j, perm !! j) | j <- [0..length perm - 1], j /= i]

solveNQueens :: [[Int]]
solveNQueens = filter isValid (permutations [1..8])

main :: IO ()
main = do
    mapM_ print solveNQueens  
    putStrLn $ "Liczba rozwiazan: " ++ show (length solveNQueens)

