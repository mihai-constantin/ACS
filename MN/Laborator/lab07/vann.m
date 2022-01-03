function [L, V] = vann(A, max_iter, tol)
[n n] = size(A);
L = zeros(1, n);
V = zeros(n);
C = A;

for k = 1 : n - 1
% getting the current eigenvalue
[lam y nr] = MPD(A, max_iter, tol);
L(k) = lam;
V(:, k) = y;

% calculating the next matrix
x = A(k, :)' / (lam * y(k));
B = A - lam * y * x';
A = B;
endfor

% getting the last eigenvalue
[lam y nr] = MPD(A, max_iter, tol);
L(n) = lam;
V(:, n) = y;

endfunction
