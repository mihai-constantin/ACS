% CONSTANTIN MIHAI - 321CD

function [H, G, zeta, wn, px, py, K, Kperf, ystep, Tt0, Kfinal, yStepFinal] = ex4(t)

s = tf('s');

J = 6 * 10^5;
b = 2 * 10^4;

% functia de transfer in conditii initiale nule
%               1
%   H(s) = ------------
%           J*s^2 + bs

K = 5000;

H = tf(1, [J b 0]);
G = (K/J) / (s^2 + (b/J) * s + K/J);

% 4.2
wn = sqrt(K/J); % pulsatia
zeta = b / (2*J*wn); % factorul de amplificare

% polii sistemului G(s)
delta = (b/J)^2 - 4*(K/J);
s1 = (-b/J + 1i*sqrt(-delta))/2;
s2 = (-b/J - 1i*sqrt(-delta))/2;

px = [real(s1); real(s2)];
py = [imag(s1); imag(s2)];

% Reprezentarea in planul complex a polilor sistemului
figure
scatter(px(1), py(1))
text(px(1), py(1), "");
hold on;
scatter(px(2), py(2))
text(px(2), py(2), "");
title('Reprezentarea in planul complex a polilor sistemului');

% 4.4
Kperf = 450;
Gperf = (Kperf/J) / (s^2 + (b/J) * s + Kperf/J);

ystep = step(Gperf, t);
figure
step(Gperf)

% 4.5
Kfinal = 2000;
Gfinal = (Kfinal/J) / (s^2 + (b/J) * s + Kfinal/J);
temp = stepinfo(Gfinal);
Tt0 = temp.SettlingTime;

yStepFinal = step(Gfinal, t);

% 4.6
% Raspunsul sistemului la treapta pentru K = 200, 400, 1000, 2000
%
K6_1 = 200;
G6_1 = (K6_1/J) / (s^2 + (b/J) * s + K6_1/J);

figure
step(G6_1);
hold on;

K6_2 = 400;
G6_2 = (K6_2/J) / (s^2 + (b/J) * s + K6_2/J);

step(G6_2);
hold on;

K6_3 = 1000;
G6_3 = (K6_3/J) / (s^2 + (b/J) * s + K6_3/J);

step(G6_3);
hold on;

K6_4 = 2000;
G6_4 = (K6_4/J) / (s^2 + (b/J) * s + K6_4/J);

step(G6_4);

end