/*

1. The woman from Galveston, who found herself sitting directly across the table from Mara, had the sausage eater on her immediate right.

2. Marva, who was seated directly across the table from the eater of the mushrooms, had on her immediate right the person from Dallas. 

3. The eater of the pepperoni was situated with Moira immediately to her right, and with the resident of San Antonio directly across the table from her. 

4. Marla, who sat in between two strict vegetarians, was directly across the table from the native of the Woodlands. 

5. Myra sat directly across from the devourer of the meatballs.

6. The consumer of broccoli was not seated next to Moira.

7. The native of Austin was not seated next to Maya.
*/

right(1,6).
right(L,R) :- member(L, [2,3,4,5,6]), R is L-1.

across(A,B) :- A =:= B-3 ; A =:= B+3.

solvePizza(Sol) :-
%% template bazat pe prima constrângere
%% 1. The woman from Galveston, who found herself sitting directly across the table from Mara, had the sausage eater on her immediate right.
	Sol = [(1, mara, C1, T1), (2, N2, C2, T2), (3, N3, C3, sausage), (4, N4, galveston, T4), (5, N5, C5, T5), (6, N6, C6, T6)],
	
%% generare
	
	member((Imarva, marva, _, _), Sol),
	member((Imush, _, _, mushrooms), Sol), across(Imarva, Imush),
	member((Ippro, _, _, pepperoni), Sol),
	member((Imoira, moira, _, _), Sol), right(Ippro, Imoira),
	member((Imyra, myra, _, _), Sol),
	member((Imbal, _, _, meatballs), Sol), across(Imyra, Imbal),
	member((Ibroc, _, _, broccoli), Sol), \+right(Ibroc, Imoira), \+right(Imoira, Ibroc),

%% 2. Marva, who was seated directly across the table from the eater of the mushrooms, had on her immediate right the person from Dallas. 	
	
	member((Idall, _, dallas, _), Sol), right(Imarva, Idall),
	
%% 3. The eater of the pepperoni was situated with Moira immediately to her right, and with the resident of San Antonio directly across the table from her.
	
	member((Isan, _, san_a, _), Sol), across(Ippro, Isan),
	
%% 4. Marla, who sat in between two strict vegetarians, was directly across the table from the native of the Woodlands.	
	member((Imarla, marla, _, _), Sol),
	member((Iwoo, _, woodlands, _), Sol), across(Imarla, Iwoo),
	
	
%% 5. Myra sat directly across from the devourer of the meatballs.	
	
%% 6. The consumer of broccoli was not seated next to Moira.
	
%% 7. The native of Austin was not seated next to Maya.	
	member((Imaya, maya, _, _), Sol),
	member((Iaust, _, austin, _), Sol), \+right(Imaya, Iaust), \+right(Iaust, Imaya),
	
	lists:perm([moira,maya,marla,myra,marva],[N2,N3,N4,N5,N6]),
	lists:perm([mushrooms,pepperoni,meatballs,broccoli,pepper],[T1,T2,T4,T5,T6]),
	right(I,Imarla), \+member((I, _, _, pepperoni),Sol), \+member((I, _, _, sausage),Sol), \+member((I, _, _, meatballs),Sol),
	right(Imarla,J), \+member((J, _, _, pepperoni),Sol), \+member((J, _, _, sausage),Sol), \+member((J, _, _, meatballs),Sol),
	lists:perm([austin,dallas,san_a,houston,woodlands],[C1,C2,C3,C5,C6]).


%% predicat pentru testarea timpului de rulare
%% se apelează checkTime(solvePizza).
checkTime(P) :- 
	statistics(runtime,[Start|_]),
	Call =..[P,S], call(Call),
	statistics(runtime,[Stop|_]),
	Runtime is Stop - Start,
	write(S), nl,
	write('Time elapsed = '), write(Runtime), write('ms.'), nl.
	
	