A = [3 1 -2; 1 3 1; -2 1 3]
disp('QR cu metoda Givens implementata in laborator:');
[Q, R] = givens(A)
disp('Factorizarea folosita de Matlab prin functia "qr":');
[q, r] = qr(A)
