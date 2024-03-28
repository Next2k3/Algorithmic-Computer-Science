with Ada.Text_IO; use Ada.Text_IO;
with Zadanie_2_rec; use Zadanie_2_rec;

procedure Test_rec is
	N : constant := 5;
   	A : constant := 35;
   	B : constant := 10;
   	C : constant := 55;
   	Solution : Zadanie_2_rec.DiophantineSolution;
begin
   	Put_Line("Factorial of " & Natural'Image(N) & " is " & 	Integer'Image(Zadanie_2_rec.Factorial(N)));

   	Put_Line("GCD of " & Integer'Image(A) & " and " & Integer'Image(B) & " is " & Integer'Image(Zadanie_2_rec.GCD(A, B)));

   	Solution := Zadanie_2_rec.Diophantine(A, B, C);
   	Put_Line("Diophantine equation: " & Integer'Image(A) & "x + " & Integer'Image(B) & "y = " & Integer'Image(C) & " is x = " & Integer'Image(Solution.X) & ", y = " & Integer'Image(Solution.Y));
end Test_rec;
