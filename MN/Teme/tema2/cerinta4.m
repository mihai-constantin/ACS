% CONSTANTIN MIHAI - 311CD

function [A_k S] = cerinta4(image, k)

    A = imread(image); % citire imagine
    A = double(A);

    [m n] = size(A); % dimensiune matrice A

    % 1. se calculeaza media pentru fiecare vector (linie) din matricea A

    s = ones(n, 1); % vector coloana plin de 1 de dimensiune n

    for i = 1 : m
        sum = A(i, :) * s;
        miu(i) = sum / n;
    endfor

    % 2. se actualizeaza fiecare vector (linie) din matricea A
    for i = 1 : m
        A(i, :) = A(i, :) - miu(i);
    endfor

    % 3. constructia matricei de covarianta Z
    Z = 1/(n - 1) * A * A';

    % 4. se aplica eig asupra matricei Z
    [V S] = eig(Z);

    % 5. constructiea spatiului k-dimensional al componentelor principale
    W = V(:, [1:k]);

    % 6. se calculeaza proiectia lui A in spatiul componentelor principale
    Y = W' * A;

    % 7. se aproximeaza matricea initiala A
    A_k = W * Y + miu';

endfunction

