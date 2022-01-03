t = -10 : 0.01 : 10;
u = (t >= 0) * 1;       % treapta
figure;
plot(t, u, 'r'); 
figure;
plot(conv(u, u), 'g');  % rampa
figure;
plot(t.*u);