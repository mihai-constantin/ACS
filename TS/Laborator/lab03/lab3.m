s = tf('s');
H1 = 4/(5*s+1);
H2 = 4/(5*s+1)*(0.05*s+1);
step(H1, 'r');   % raspunsul la treapta
figure;
step(H2, 'g');   % raspunsul la treapta

