A = [ 3 -13 9 3; -6 4 1 -18; 6 -2 2 4; 12 -8 6 10 ]
b = [ -19; -34; 16; 26 ]

disp('dupa aplicarea GGPS:');

[A, b, v] = GPPS(A, b)

disp('Solutia sistemului Ax = b este:');

x = SST(A,b)
