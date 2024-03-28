with Ada.Text_IO;
with Interfaces.C;
with Zadanie_5;

procedure test is
	use Ada.Text_IO;
	use Zadanie_5;
	
	N : Interfaces.C.unsigned := 5;
	A : Interfaces.C.int := 35;
	B : Interfaces.C.int := 10;
	C : Interfaces.C.int := 55;
	
	Solution : Diophantine_Solution;
begin
		
	Put_Line("Factorial of 5:" & Interfaces.C.unsigned_long'Image(wrapped_factorial(N)));
	Put_Line("GCD of 35 and 10: "& Interfaces.C.int'Image(wrapped_GCD(A,B)));
	Solution := wrapped_diophantine(A,B,C);
	Put_Line("Diophantine Solution - X:" & Interfaces.C.int'Image(Solution.X) & ", Y: " & Interfaces.C.int'Image(Solution.Y));
end test;
