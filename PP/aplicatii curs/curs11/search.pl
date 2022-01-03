solve(Sol) :- initial_state(State), search([State], Sol).

search(States, Sol) :- final_state(States), !, reverse(States, Sol).
search([S | States], Sol) :- arc(S, Next), \+member(Next, States), search([Next, S | States], Sol).

%% am abstractizat (vor trebui specificate pentru fiecare problemă particulară)
%%		- initial_state
%%		- final_state
%%		- arc

%% pt săritura calului
%% 	- pe cazul general, stare = soluție parțială a problemei	(aici: tot drumul calului până în prezent)
%%		- pentru a evita redundanța în reprezentare, vom considera o stare ca fiind poziția curentă a calului
n(5).
initial_state(1/1).
final_state(States) :- n(N), N2 is N*N, length(States, N2).
arc(X1/Y1, X2/Y2) :- n(N), arc(N, X1/Y1, X2/Y2).
arc(N, X1/Y1, X2/Y2) :-
	member((Dx, Dy), [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]),
	X2 is X1 + Dx, X2 > 0, X2 =< N,
	Y2 is Y1 + Dy, Y2 > 0, Y2 =< N.

	
