% CONSTANTIN MIHAI - 321CD

function [H, h, y3, y4, y5] = ex1(t, w, N )

s = tf('s');

% functia de transfer
H = 1 / (s + 1); 

% raspunsul sistemului la impuls (functia pondere)
h = impulse(H); 
plot(h);
title('Raspunsul sistemului la impuls');

% raspunsul sistemului la intrare de tipul e^jwt
y3 = lsim(H, exp(1i * w .* t), t);
figure;
plot(t, y3);
title('Raspunsul sistemului la intrare de tipul e^{jwt}');

% y_bun = exp(1i * w .* t) * (1/(1i*w+1));
% figure;
% plot(t, y_bun);
% title('Raspuns bun');

% raspunsul sistemului la intrare de tipul cos(t)
figure;
lsim(H, cos(t), t); 
title('Raspunsul sistemului la intrare de tipul cos(t)');

% raspunsul sistemului la intrare de tipul suma(k*cos(2*k*pi*t))
sum = 0;
for k = 1 : N
    sum = sum +  k .*cos(2*k*pi*t);
end

y5 = lsim(H, sum, t);
figure
plot(y5)
title('Raspunsul sistemului la intrare de tipul suma(k*cos(2*k*pi*t))');


end

