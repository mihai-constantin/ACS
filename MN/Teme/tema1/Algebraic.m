% CONSTANTIN MIHAI - 311CD

function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari: 
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.

    in = fopen(nume, 'r'); % deschidere fisier de intrare
    N = fscanf(in, '%d', 1); % nr de noduri

    A = zeros(N); % initializare matrice de adiacenta
    K = zeros(N); % initializare matrice diagonala K

    % citire lista vecini
    for i = 1: N

        x = fscanf(in, '%d', 1);
        nr_vecini = fscanf(in, '%d', 1); % nr de vecini pentru nodul x

        K(i,i) = nr_vecini; % formare matrice diagonala K

        for k = 1: nr_vecini
            y = fscanf(in, '%d', 1);
            A(x, y) = 1; % formare matrice de adiacenta A
        endfor

    endfor

    % pe diagonala principala avem intotdeauna valoarea 0
    for i = 1: N
        if A(i, i) == 1
            K(i, i) = K(i, i) - 1; % daca A(i,i) == 1, gradul de iesire al nodului i scade cu 1
        endif
        A(i, i) = 0;
    endfor

    % matricea M
    M = (inv_diagonal(K) * A)';

    %vector coloana care contine numai 1
    for i = 1 : N
        v(i) = 1;
    endfor

    v = v';

    I = eye(N); % matricea identitate

    % calcul vector R
    R = GramSchmidt(I - d * M) * (1 - d)/N * v;

    fclose(in);

endfunction
