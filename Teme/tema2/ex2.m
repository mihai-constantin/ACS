% CONSTANTIN MIHAI - 321CD

function [y1, y2, wn, w1, w2, w3, absH1, absH2, absH3, f, g] = ex2(t)

H = tf(2, [1 2 2]); % functia de transfer
step(H);

% raspunsul sistemului la treapta unitara
y1 = 1 - sqrt(2) .* exp(-t) .* cos(t - pi/4);

% raspunsul sistemului la t * 1(t) = ramp
ramp = zeros(1, length(t));

for i = 1 : length(t)
    if t(i) >= 0
        ramp(i) = t(i);
    end
end

figure
y2 = lsim(H, ramp, t);
plot(y2);
title('Raspunsul sistemului la intrare de tip rampa');

% 2.3
wn = sqrt(2);

w2 = wn;
w1 = w2 - 1;
w3 = w2 + 1;

% raspunsul sistemului la intrarile sinusoidale
y_w1 = lsim(H, sin(w1*t), t);
figure
plot(y_w1);
title('Raspunsul sistemului la intrarea armonica sin(w1 * t)');

y_w2 = lsim(H, sin(w2 * t), t);
figure
plot(y_w2);
title('Raspunsul sistemului la intrarea armonica sin(w2 * t)');

y_w3 = lsim(H, sin(w3 * t), t);
figure
plot(y_w3);
title('Raspunsul sistemului la intrarea armonica sin(w3 * t)');

% functiile de transfer H_w1, H_w2, H_w3

H_w1 = 2 / (-w1^2 + 2i*w1 + 2);
H_w2 = 2 / (-w2^2 + 2i*w2 + 2);
H_w3 = 2 / (-w3^2 + 2i*w3 + 2);

absH1 = abs(H_w1);
absH2 = abs(H_w2);
absH3 = abs(H_w3);

% 2.4
w = logspace(-2, 2, 100);
H_w = 2 ./ (-w.^2 + 2i.*w + 2);
f = abs(H_w);
g = angle(H_w);

figure
plot(f)
title('|H(jw)|')

figure
plot(g)
title('arg(H(jw))')

figure
semilogx(w, H_w);
title('semilog(w, H)');

end