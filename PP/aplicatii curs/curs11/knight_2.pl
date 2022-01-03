%% a rezolva problema înseamnă a porni căutarea dintr-o stare inițială
% solve_knight(N, Sol) 
solve_knight(N, Sol) :- fill_board(N, [1/1], Sol).

%% Path = calea urmată de cal până acum
%% Sol = calea completă, va fi egală cu Path când ajungem într-o stare finală
% fill_board(N, Path, Sol)
fill_board(N, Path, Path) :- N2 is N*N, length(Path, N2), !.
fill_board(N, [Prev | Path], Sol) :-
	arc(N, Prev, Next),
	\+member(Next, Path),
	fill_board(N, [Next, Prev | Path], Sol).

%% descrie o tranziție validă între două poziții pe tabla de șah
% arc(N, Prev, Next)
arc(N, X1/Y1, X2/Y2) :-
	member((Dx, Dy), [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]),
	X2 is X1 + Dx, X2 > 0, X2 =< N,
	Y2 is Y1 + Dy, Y2 > 0, Y2 =< N.