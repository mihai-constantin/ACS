% CONSTANTIN MIHAI - 311CD

function B = inv_diagonal(A)
% Functia returneaza inversa unei matrice diagonale

    [n n] = size(A); % dimensiune matrice

    B = zeros(n); % initializare matrice B

    for i = 1: n
        B(i, i) = 1  / A(i, i); % formarea inversei matricei diagonale A
    endfor

endfunction
