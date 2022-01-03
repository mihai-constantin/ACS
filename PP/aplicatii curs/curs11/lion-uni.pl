% fapte din enunț
lies(lion, [mon, tue, wed]).
lies(unicorn, [thu, fri, sat]).

% alte fapte necesare modelării constrângerilor
days([sun, mon, tue, wed, thu, fri, sat, sun]).
yesterday(Yday, Today) :- days(Days), consec(Days, Yday, Today).
consec([Yday, Today | _], Yday, Today).
consec([_ | Rest], Yday, Today) :- consec(Rest, Yday, Today).

%% pornim cu întreg setul de candidați
% candidate(Day).
candidate(Day) :- days([_|Days]), member(Day, Days).

%% dintre cei de la pasul anterior,
%% candidații care sunt consistenți cu ce a spus leul: Ieri mințeam
% candidate1(Day)
candidate1(Day) :-
	candidate(Day),
	lies(lion, LieDays), yesterday(Yday, Day),
	( member(Day, LieDays), \+member(Yday, LieDays) ;
	  \+member(Day, LieDays), member(Yday, LieDays) ).

%% dintre cei de la pasul anterior,
%% candidații care sunt consistenți cu ce a spus unicornul: Și eu
% candidate2(Day)
candidate2(Day) :-
	candidate1(Day),
	lies(unicorn, LieDays), yesterday(Yday, Day),
	( member(Day, LieDays), \+member(Yday, LieDays) ;
	  \+member(Day, LieDays), member(Yday, LieDays) ).
	
	

