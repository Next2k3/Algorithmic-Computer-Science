import Data.List (permutations, nub)

-- Funkcja sprawdzająca, czy permutacja jest poprawnym rozwiązaniem
isValid :: [Int] -> Bool
isValid perm = all safe [(i, perm !! i) | i <- [0..length perm - 1]]
  where
    safe (i, x) = all (\(j, y) -> abs (x - y) /= abs (i - j)) 
                      [(j, perm !! j) | j <- [0..length perm - 1], j /= i]

-- Odbicie pionowe
reverseVertical :: [Int] -> [Int]
reverseVertical = reverse

-- Odbicie poziome (odwrócenie pozycji wierszy)
reverseHorizontal :: [Int] -> [Int]
reverseHorizontal = map (9 -)

-- Sprawdzenie, czy rozwiązanie jest symetryczne względem już znalezionych rozwiązań
isSymmetric :: [Int] -> [[Int]] -> Bool
isSymmetric perm knownSolutions = 
    any (\sol -> reverseVertical sol == perm || reverseHorizontal sol == perm || reverseVertical (reverseHorizontal sol) == perm ) knownSolutions

-- Funkcja usuwająca duplikaty rozwiązania z symetriami
uniqueSolutions :: [[Int]] -> [[Int]]
uniqueSolutions = foldl (\acc perm -> if isSymmetric perm acc then acc else perm : acc) []

-- Rozwiązania dla 8 hetmanów
solveNQueens :: [[Int]]
solveNQueens = filter isValid (permutations [1..8])

-- Funkcja główna
main :: IO ()
main = do
    let solutions = solveNQueens
    let uniqueSol = uniqueSolutions solutions
    putStrLn $ "Liczba wszystkich rozwiazan: " ++ show (length solutions)
    putStrLn $ "Liczba nierównoważnych rozwiazan: " ++ show (length uniqueSol)

