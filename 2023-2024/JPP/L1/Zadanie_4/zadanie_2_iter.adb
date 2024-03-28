package body Zadanie_2_iter is
	
	function Factorial (N : Integer) return Integer is
		Result : Integer := 1;
	begin
		for I in 1 .. N loop
			Result := Result * I;
		end loop;
		return Result;
	end Factorial;
	
	function GCD (A, B : Integer) return Integer is
		Local_A : Integer := A;
		Local_B : Integer := B;
		Temp : Integer;
	begin
		while Local_B /= 0 loop
			Temp := Local_B;
			Local_B := Local_A mod Local_B;
			Local_A := Temp;
		end loop;
		return Local_A;
	end GCD;
	
	 function Diophantine(A, B, C : Integer) return DiophantineSolution is
      		GCD_AB : Integer;
      		Sign_A, Sign_B : Integer;
      		Div : Integer;
      		Solution, Next_Solution : DiophantineSolution;
   	 begin
      		if A = 0 and B = 0 then
         		raise Program_Error with "Invalid equation: both coefficients cannot be zero.";
      		end if;

      		GCD_AB := GCD(A, B);

      		if C mod GCD_AB /= 0 then
        	 	raise Program_Error with "No solution: c is not divisible by gcd(a, b).";
      		end if;

		if A < 0 then
			Sign_A := -1;
		else
			Sign_A := 1;
		end if;
		if B < 0 then
			Sign_B := -1;
		else
			Sign_B := 1;
		end if;

      		Div := C / GCD_AB;
      		Solution.X := Sign_A * Div;
      		Solution.Y := 0;

      		if (C - A * Solution.X) mod B /= 0 then
         		Next_Solution := Diophantine(B, A mod B, C - A * Solution.X);
         		Solution.X := Solution.X + Sign_A * Next_Solution.X;
         		Solution.Y := Solution.Y + Sign_B * Next_Solution.Y;
      		else
         		Solution.Y := (C - A * Solution.X) / B;
      		end if;

      		return Solution;
   	end Diophantine;
end Zadanie_2_iter;	
