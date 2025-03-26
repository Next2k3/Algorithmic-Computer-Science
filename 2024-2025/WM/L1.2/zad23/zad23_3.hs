import Data.List (permutations, nub)

-- Sprawdza czy permutacja jest poprawna
isValid :: [Int] -> Bool
isValid xs = all (uncurry safe) (zip [0..] xs)
  where safe i x = all (\(j, y) -> j == i || abs (x - y) /= abs (i - j)) (zip [0..] xs)

-- Usuwa symetryczne rozwiązania
uniqueSolutions :: [[Int]] -> [[Int]]
uniqueSolutions sols = foldl addIfUnique [] sols
  where
    addIfUnique acc p = if any (isSym p) acc then acc else p : acc
    isSym p s = reverse s == p || map (7-) s == p || reverse (map (7-) s) == p

-- Główna funkcja
main :: IO ()
main = do
    let solutions = filter isValid (permutations [0..7])
        unique = uniqueSolutions solutions
    putStrLn $ "Wszystkie rozwiązania: " ++ show (length solutions)
    putStrLn $ "Unikalne rozwiązania: " ++ show (length unique)
