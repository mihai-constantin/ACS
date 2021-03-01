%functia returneaza cea mai mare valoare proprie in modul + vectorul propriu normat asociat + nr iteratiifunction [lambda y k] = MPD(A, max, tol)[n n] = size(A); % dimensiune matrice
y = rand(n, 1); %initializare random vector y
for k = 1: max
  z = A * y;  y = z / norm(z);  lambda = y' * A * y;    %conditie de iesire  t = A * y - lambda * y;    if norm(t) < tol    return;  endifendforendfunction