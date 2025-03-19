permutations' :: [a] -> [[a]]
permutations' [] = [[]]  
permutations' (x:xs) = [ y | ys <- permutations' xs, y <- insert x ys ]

-- Funkcja insert wstawia element x w każdą możliwą pozycję w liście
insert :: a -> [a] -> [[a]]
insert x [] = [[x]]  -- Jeśli lista jest pusta, zwracamy listę z jednym elementem x
insert x (y:ys) = (x:y:ys) : map (y:) (insert x ys)  -- Wstawiamy x przed y, a potem rekurencyjnie wstawiamy x do reszty listy

