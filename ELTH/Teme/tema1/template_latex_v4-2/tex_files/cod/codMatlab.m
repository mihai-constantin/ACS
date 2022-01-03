clear all;
% script test - pentru a verifica corectitudinea apelurilor fct contour,
% contourf, surf
% Gabriela Ciuprina
% 2014 - toy script for my students

nx = 100;  % nr de pct pentru gridul de discretizare
ny = 100;
gridx = linspace(-20,20,nx);
gridy = linspace(-15,15,ny);
val = zeros(ny,nx);
for i = 1:nx
    for j = 1:ny
        val(j,i) = (gridx(i)-5)^2 + gridy(j)^2;
    end
end

figure(1);
clf;
subplot(2,2,1)
[c,h] = contour(gridx,gridy,val);
clabel(c,h);
daspect([1 1 1]);   % ca sa nu apara deformat
grid on;
title('contour cu echivalori implicite');
   
subplot(2,2,2)
contourf(gridx,gridy,val);
title('contourf cu echivalori implicite');
daspect([1 1 1]);
grid on;

subplot(2,2,3)
[c,h] = contour(gridx,gridy,val,[0 50 100 200]);
clabel(c,h);
daspect([1 1 1]);
grid on;
title('contour cu echivalori impuse');

subplot(2,2,4)
surf(gridx,gridy,val);
title('surf');