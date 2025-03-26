module W04b where



data DOW = Po|Wt|Sr|Cz|Pi|So|Ni deriving (Eq, Ord,Enum,Bounded)


instance Show DOW where 
	show Po = "Poniedziałek"
	show Wt = "Wtorek"
	show Sr = "Środa"
	show Cz = "Czwartek"
	show Pi = "Piątek"
	show So = "Sobota"
	show Ni = "Niedziela"
