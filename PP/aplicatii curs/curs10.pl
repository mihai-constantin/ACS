%% fapte simple
om(gica).
om(ilie).
impiedicat(gica).
traverseaza(ilie, santier). %% ilie și santier sunt constante, este un șantier anume
sapa_groapa(ilie, gica).

%% reguli
cade_in_groapa(X) :- impiedicat(X), traverseaza(X, santier).
cade_in_groapa(X) :- sapa_groapa(X, Y), X \= Y.

%% negație
bun(X) :- \+sapa_groapa(X,_).
om_bun(X) :- om(X), \+sapa_groapa(X,_).
om_bun_(X) :- \+sapa_groapa(X,_), om(X).

%% structuri
carte(titlu('Razboi si pace'), autor('Lev Tolstoi')).
carte(titlu('Sonata Kreutzer'), autor('Lev Tolstoi')).
carte(titlu('Magicianul'), autor('John Fowles')).

%% predicate de folosit în interogări
in_biblioteca(X - Y) :- carte(titlu(X), autor(Y)).
titlu(X) :- in_biblioteca(X - _).
titlu_struct(X) :- carte(X, _).
de_autor(Autor, Carte) :- carte(titlu(Carte), autor(Autor)).

%% ordinea clauzelor și premiselor
parent(george6, elizabeth2).
parent(elizabeth, elizabeth2).
parent(philip, charles).
parent(philip, anne).
parent(philip, andrew).
parent(philip, edward).
parent(elizabeth2, charles).
parent(elizabeth2, anne).
parent(elizabeth2, andrew).
parent(elizabeth2, edward).
parent(charles, william).
parent(charles, harry).
parent(william, george).
parent(william, charlotte).
parent(william, louis).

pred(Parent, Child) :- parent(Parent, Child).
pred(Pred, Succ) :- parent(Pred, Child), pred(Child, Succ).

%% clauze invers
pred1(P, S) :- parent(P, C), pred1(C, S).
pred1(P, C) :- parent(P, C).

%% premise invers
pred2(P, C) :- parent(P, C).
pred2(P, S) :- pred2(C, S), parent(P, C).

%% clauze și premise invers
pred3(P, S) :- pred3(C, S), parent(P, C).
pred3(P, C) :- parent(P, C).

factorial(0, 1).
factorial(N, F) :- 
	N > 0, 
	N1 is N-1, factorial(N1, F1), 
	F is N * F1.

factorial_1(0, 1).
factorial_1(N, F) :- 
	N > 0,
	factorial_1(N1, F1), N1 is N-1,
	F is N*F1.
	
%% eliminarea distincției dintre intrare și ieșire
elem(X, [X|_]).
elem(X, [_|Rest]) :- elem(X, Rest).

concat([], L, L).
concat([X|Rest], L, [X|Rez]) :- concat(Rest, L, Rez).

% exerciții
%elem_
%last_
%del22

%% cut
comp(X, Y, 'LT') :- X < Y.
comp(X, Y, 'EQ') :- X =:= Y.
comp(X, Y, 'GT') :- X > Y.

comp_(X, Y, 'LT') :- X < Y, !.
comp_(X, Y, 'EQ') :- X =:= Y, !.
comp_(_, _, 'GT').

elemP(X, [X|_]) :- !.
elemP(X, [_|Rest]) :- elemP(X, Rest).

sibling(X, Y) :- parent(P, X), parent(P, Y), X \= Y.    
sibling_(X, Y) :- parent(P, X), !, parent(P, Y), X \= Y.
siblingOnce(X, Y) :- once(parent(P, X)), parent(P, Y), X \= Y.