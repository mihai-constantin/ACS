s = tf('s');
H = 4/(s+5);            % functia de transfer

step(H);                % raspunsul sistemului la treapta

figure;
impulse(H);             % raspunsul sistemului la impulsul Dirac

t = -10 : 0.01 : 10;
u = cos(4*t + pi/3);
figure;
lsim(H, u, t);          % raspunsul sistemului la intrarea u

ramp = zeros(1, length(t));
for i = 1 : length(t)
    if t(i) >= 0
        ramp(i) = t(i);
    end
end

figure;
lsim(H, ramp, t);

treapta = (t >= 0) * 1;
figure;
lsim(H, treapta, t);


