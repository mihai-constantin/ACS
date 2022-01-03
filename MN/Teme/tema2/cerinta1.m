% CONSTANTIN MIHAI - 311CD

% Descompunerea redusa a valorilor singulare
% A_k[m, n] = U_k[m, k] * S_k[k, k] * V_k[k, n]

function A_k = cerinta1(image, k)

    A = imread(image); % citire imagine
    A = double(A);

    [m n] = size(A); % dimensiune matrice A

    [U S V] = svd(A);

    U_k = U(:, 1:k);
    S_k = S(1:k, 1:k);
    V = V';
    V_k = V(1:k, :);

    A_k = U_k * S_k * V_k;

endfunction
