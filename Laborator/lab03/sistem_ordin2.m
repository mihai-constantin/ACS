H = tf([2], [1 0.4*sqrt(2) 2]);
t = -10 : 0.01 : 25;
u = (t >= 0) * 1;
lsim(H, u, t);