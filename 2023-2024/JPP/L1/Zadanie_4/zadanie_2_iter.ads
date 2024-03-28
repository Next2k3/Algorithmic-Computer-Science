package Zadanie_2_iter is
	type DiophantineSolution is record
		X : Integer;
		Y : Integer;
	end record;
	
	function Factorial(N : Integer) return Integer;
   	function GCD(A, B : Integer) return Integer;
   	function Diophantine(A, B, C : Integer) return DiophantineSolution;
   	
    	pragma Export (C, Factorial, "Factorial");
    	pragma Export (C, GCD, "GCD");
    	pragma Export (C, Diophantine, "Diophantine");
 end Zadanie_2_iter;
