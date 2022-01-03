% functia returneaza toate valorile proprii ale matricei A + toti vectorii proprii
% foloseste MPD de n ori

    [lambda(i) y k] = MPD(A, max, tol);

    vectori(:, i) = y;

    x = A(i, :)' / (lambda(i) * y(i));
    B = (A - lambda(i) * y * x');
    A = B;
         
endfor
        
[lambda(n) y k] = MPD(A, max, tol); % ultima valoare proprie
vectori(:, n) = y;
