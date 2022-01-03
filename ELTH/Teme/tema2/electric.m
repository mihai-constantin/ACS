% Exercitiul 3
a = 7; % raza 

[x y] = meshgrid(-a : 1.5 : a);

alpha = atan2(y,x);

r = sqrt(x.^2 + y.^2);
n = length(r);

for i = 1 : n
    for j = 1 : n
        D(i,j) = f(r(i,j), a);
    endfor
endfor

u = D .* cos(alpha);
v = D .* sin(alpha);

figure;
quiver(x, y, u, v);
title('Spectrul lui D');

figure;
contourf(x, y, D);
colorbar;
title('Echivalori ale lui D');

