A = [1.5 -2.1; -7.6 3.11]
b = [8.3; 6.7]

disp('Solutiile sistemului Ax = b, rezolvat prin mai multe metode:');

[C,d] = GPP(A,b);
disp('GPP:');
x = SST(C,d)

[C,d] = GPPS(A,b);
disp('GPPS:');
x = SST(C,d)

[C,d] = GPT(A,b);
disp('GPT:');
x = SST(C,d)