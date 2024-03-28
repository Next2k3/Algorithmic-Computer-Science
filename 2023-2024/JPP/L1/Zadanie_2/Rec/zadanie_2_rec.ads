package Zadanie_2_rec is
	type DiophantineSolution is record
		X : Integer;
		Y : Integer;
	end record;
	
	function Factorial(N : Integer) return Integer;
   	function GCD(A, B : Integer) return Integer;
   	function Diophantine(A, B, C : Integer) return DiophantineSolution;
 end Zadanie_2_rec;
