% Albert and Bernard have just met Cheryl.
% “When is your birthday?” Albert asked Cheryl.
% Cheryl thought for a moment and said, “I won’t tell you,
% but I’ll give you some clues”. She wrote down a list of ten dates:

% May 15, May 16, May 19
% June 17, June 18
% July 14, July 16
% August 14, August 15, August 17

% “One of these is my birthday,” she said.

% Cheryl whispered in Albert’s ear the month, and only the month, of her birthday.
% To Bernard, she whispered the day, and only the day.
% “Can you figure it out now?” she asked Albert.

% Albert: “I don’t know when your birthday is, but I know Bernard doesn’t know, either.”
% Bernard: “I didn’t know originally, but now I do.”
% Albert: “Well, now I know, too!”

% When is Cheryl’s birthday?

%% pornim cu întreg setul de candidați
candidate(Day, Month) :- 
	member(Day/Month, [15/may, 16/may, 19/may, 17/jun, 18/jun, 14/jul, 16/jul, 14/aug, 15/aug, 17/aug]).

%% dintre cei de la pasul anterior,
%% candidații care sunt consistenți cu ce a spus Albert: I don’t know when your birthday is, but I know Bernard doesn’t know, either.
candidate1(Day, Month) :-
	candidate(Day, Month),
	forall(candidate(D, Month), findall(_, candidate(D, _), [_,_|_])).
	
%% dintre cei de la pasul anterior,
%% candidații care sunt consistenți cu ce a spus Bernard: I didn’t know originally, but now I do.
candidate2(Day, Month) :-
	candidate1(Day, Month),
	findall(_, candidate1(Day, _), [_]).
%% dintre cei de la pasul anterior,
%% candidații care sunt consistenți cu ce a spus Albert: Well, now I know, too!
candidate3(Day, Month) :-
	candidate2(Day, Month),
	findall(_, candidate2(_, Month), [_]).