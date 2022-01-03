k = 100;
m = 20;
b = 2;
A = [0 1; -k/m -b/m];
B = [0; 1/m];
C = [1 0; -k/m -b/m];
D = [0; 1/m];
% C = [1 0; 0 1; -k/m -b/m];
% D = [0; 0; 1/m];

H = ss(A, B, C, D);
step(H);
isstable(H)
eig(A)
