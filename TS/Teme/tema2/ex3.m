% CONSTANTIN MIHAI - 321CD

function [Y, y, H, px, py, y1, y2, y3, yp, yt] = ex3(t) 

%           -s^2 - 6s - 1
% Y(s) = --------------------
%          s^3 + 4s^2 + 20s

numerator = [0 -1 -6 -1];
denominator = [1 4 20 0];

Y = tf(numerator, denominator);

figure
impulse(Y); % reprezentare grafica pentru raspunsul sistemului
title('Raspunsul sistemului la impuls');

%
% Dupa descompunerea in fractii simple, Y(s) devine
%
%         -1     19          s+2          39          4
% Y(s) = ---- - ---- * --------------- - ---- * --------------
%         20s    20     (s+2)^2 + 4^2     40    (s+2)^2 + 4^2
%

comp_libera = -1/20;
comp_fortata = -19/20 * exp(-2*t).*cos(4*t) - 39/40 * exp(-2*t).*sin(4*t);

% y = L^(-1){Y(s)}
y = comp_libera + comp_fortata;

% functia de transfer in conditii initiale nule
%               2s-1
%   H(s) = --------------
%           s^2 + 4s + 20

H = tf([0 2 -1], [1 4 20]);

% coordonatele pe cele 2 axe ale polilor
%   Polii functiei de transfer:
%       s1 = -2 - 4i
%       s2 = -2 + 4i
%
%   H(s) - stabila deoarece partile reale ale polilor sunt negative
%
px = [-2 -2];
py = [-4 4];

% Reprezentarea in planul complex a polilor sistemului
figure
scatter(px(1), py(1))
text(px(1), py(1), "");
hold on;
scatter(px(2), py(2))
text(px(2), py(2), "");
title('Reprezentarea in planul complex a polilor sistemului');

% semnal treapta
treapta = zeros(1, length(t));
treapta (t >= 0) = 1;

u_1 = treapta;

% semnal rampa
ramp = zeros(1, length(t));

for i = 1 : length(t)
    if t(i) >= 0
        ramp(i) = t(i);
    end
end

u_2 = ramp;

% semnalul u_3 = cos(3*t) * 1(t)
u_3 = cos(3*t) .* treapta;

y1 = lsim(H, u_1, t);
figure;
plot(y1);
title('Raspunsul fortat al sistemului la intrarea u(t) = 1(t)');

y2 = lsim(H, u_2, t);
figure;
plot(y2);
title('Raspunsul fortat al sistemului la intrarea u(t) = t*1(t)');

y3 = lsim(H, u_3, t);
figure
plot(y3);
title('Raspunsul fortat al sistemului la intrarea u(t) = cos(3t) * 1(t)');

% 
% Teorema valorii finale si initiale
%

% regimul permanent - componenta libera pentru Y(s)
yp = -1/20;

% regimul tranzitoriu - componenta fortata - componenta fortata pentru Y(s)
yt = -19/20 * exp(-2*t).*cos(4*t) - 39/40 * exp(-2*t).*sin(4*t);

end