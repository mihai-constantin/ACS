% CONSTANTIN MIHAI - 311CD

function x = SST(A, b)
    % Functie care calculeaza solutia unui sistem superior triunghiular

    [n n] = size(A); % dimensiune matrice

    for i = n : -1 : 1

        sum = 0; % initializare suma

        for j = i + 1 : n
            sum = sum + A(i,j) * x(j);
        endfor

        x(i) = (b(i) - sum) / A(i,i);

    endfor

endfunction
