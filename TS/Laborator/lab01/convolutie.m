t = -10 : 0.01 : 10;

u = (t >= 0) * 1; % treapta
plot(t, u, 'r');
figure;
plot(conv(u,u), 'r'); % rampa

u = (t >= 2) * 1; % 1(t - 2)
v = (t >= 5) * 1; % 1(t - 5)

figure;
plot(t, u - v, 'r'); % 1(t - 2) - 1(t - 5) - rect(t)