:- use_module(library(clpfd)).

factorial(0, 1).
factorial(N, F) :-
	N #> 0,
	N1 #= N - 1,
	F #= N * F1,
	factorial(N1, F1).
	
restrictions(Vars) :-
	Vars = [X1, X2, X3, X4, Y1, Y2, Y3, Y4], 
	all_distinct(Vars),
	Vars ins 2 .. 9,
	X1*2 #= Y3,   
	Y4*2 #= X2,
   Y1 #= X1+X3,  
	X1+X2+X3+X4 #> Y1+Y2+Y3+Y4.