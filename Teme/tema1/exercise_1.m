% CONSTANTIN MIHAI - 321CD

t = -10 : 0.01 : 10;        % domeniul de definitie al semnalului armonic
u = cos(100 * t + pi/3);    % semnalul armonic

% graficul semnalului de intrare
plot(u);
title("\fontsize{14}Graficul semnalului de intrare u(t)")
xlabel("Timp(s)");
ylabel("Amplitudine");

k = 20 : 40: 100; % valorile pentru care studiem evolutia sistemului

for i = 1 : length(k)
   
   h = exp(-k(i) * t);   % functia pondere
   y = conv(u, h);       % semnalul de iesire
   
   % graficul semnalului de iesire
   figure;
   plot(y);
   title("\fontsize{14}Graficul semnalului de iesire y(t) pentru k = " + k(i));
   xlabel("Timp(s)");
   ylabel("Amplitudine");
   
end