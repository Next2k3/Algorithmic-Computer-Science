partition :: (a -> Bool) -> [a] -> ([a], [a])
partition _ [] = ([], [])
partition p (x:xs) =
  let (ys, zs) = partition p xs
  in if p x then (x:ys, zs) else (ys, x:zs)

