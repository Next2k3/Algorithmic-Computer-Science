package body Zadanie_2_rec is
	function Factorial (N : Integer) return Integer is
	begin 
		if N <= 1 then
			return 1;
		else
			return N * Factorial(N-1);
		end if;
	end Factorial;
	
	function GCD (A, B : Integer) return Integer is
	begin
		if B = 0 then
			return A;
		else
			return GCD (B, A mod B);
		end if;
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
end Zadanie_2_rec;
	
