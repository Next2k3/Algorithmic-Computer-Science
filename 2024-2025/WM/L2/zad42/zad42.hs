approx :: Int -> Double
approx n = foldr (\k acc -> acc + ( 1 / factorial (fromIntegral k))) 0 [1..n]
  where
    factorial :: Double -> Double
    factorial k = product [1..k]
    

    
