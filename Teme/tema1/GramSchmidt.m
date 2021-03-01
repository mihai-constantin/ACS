% CONSTANTIN MIHAI - 311CD

function B = GramSchmidt(A)
	% Functia care calculeaza inversa matricii A folosind factorizari Gram-Schmidt
	% In prima faza, am descompus matricea A sub forma Q * R
    % Q este matrice ortogonala (inv(Q) = Q') si R este matrice superior triunghiulara
    % In final, am rezolvat n sisteme de ecuatii de forma A * x_i = e_i, adica R * x_i = Q' * e_i

    [n n] = size(A); % dimensiune matrice A

    % calculul matricei ortogonale Q si a matricei superior triunghiulare R
    for j = 1 : n

        for i = 1 : j - 1
            R(i,j) = Q(:, i)' * A(:, j);
        endfor

        sum = 0;
        for i = 1 : j - 1
            sum = sum + R(i,j) * Q(:, i);
        endfor

        aux = A(:, j) - sum;

        R(j,j) = norm(aux);
        Q(:, j) = aux / R(j,j);

    endfor

    I = eye(n); % matricea identitate

    for i = 1 : n

        % rezolv ecuatia A * x_i = e_i
        b = Q' * I(:, i);
        x = SST(R, b);
                                 
        B(:, i) = x'; % retin rezultatul in matricea B

    endfor

endfunction
	
