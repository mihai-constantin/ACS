%% a rezolva problema înseamnă a genera un template și apoi a îl instanția complet
% solve_knight(N, Sol) 
solve_knight(N, Sol) :- N2 is N*N, template(N2, Sol), fill_board(N, Sol).

%% generează un template
% template(N, Template)
template(1, [1/1]).
template(N, [_|Template]) :- N > 1, Pred is N-1, template(Pred, Template).

%% instanțierea unui template se face recursiv pe principiul:
%%		- template-ul corespunzător stării inițiale este util
%%		- template-ul corespunzător stării S este util dacă
%%				- se poate ajunge în S dintr-o altă stare Prev 
%%				- template-ul corespunzător lui Prev este util
% fill_board(N, Template)
fill_board(_, [_]).
fill_board(N, [S, Prev | Template]) :- 
	fill_board(N, [Prev | Template]),
	arc(N, Prev, S),
	\+member(S, Template).

%% descrie o tranziție validă între două poziții pe tabla de șah
% arc(N, Prev, Next)
arc(N, X1/Y1, X2/Y2) :-
	member((Dx, Dy), [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]),
	X2 is X1 + Dx, X2 > 0, X2 =< N,
	Y2 is Y1 + Dy, Y2 > 0, Y2 =< N.
