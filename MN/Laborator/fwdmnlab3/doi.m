A = [12 -51 4; 6 167 -68; -4 24 -41]
disp('QR cu metoda Householder implementata in laborator:');
[Q, R] = Householder(A)
disp('Factorizarea folosita de Matlab prin functia "qr":');
[q, r] = qr(A)
