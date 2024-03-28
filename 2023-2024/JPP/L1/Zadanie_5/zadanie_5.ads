with Interfaces.C;

package Zadanie_5 is
	type Diophantine_Solution is record
		X : Interfaces.C.int;
		Y : Interfaces.C.int;
	end record;
	
	function wrapped_factorial(N : Interfaces.C.unsigned) return Interfaces.C.unsigned_long;
	pragma Import (C, wrapped_factorial, "factorial");
	
	function wrapped_GCD(A, B : Interfaces.C.int) return Interfaces.C.int;
	pragma Import (C, wrapped_GCD, "gcd");
	
	function wrapped_diophantine(A, B, C : Interfaces.C.int) return Diophantine_Solution;
	pragma Import (C, wrapped_diophantine, "diophantine");
end Zadanie_5;

