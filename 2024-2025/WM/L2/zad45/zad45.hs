data State = Q0 | Q1 | Q2 | Q3 | QReject deriving (Show, Eq)

next :: State -> Char -> State
next Q0 '0' = Q1     
next Q1 '1' = Q2   
next Q2 '0' = Q2
next Q2 '1' = Q3
next Q3 '0' = Q3 
next Q3 '1' = Q2 
next _ _ = QReject  

accept :: String -> Bool
accept str = isAccepting (foldl next Q0 str) where
    isAccepting Q3 = True
    isAccepting _ = False 
