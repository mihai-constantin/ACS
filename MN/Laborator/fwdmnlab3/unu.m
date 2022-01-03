#a
disp('a)');
u = [1/2; 0; 1/2; 0; 1/2; 0; 1/2; 0]
v = [0; 1/2; 0; 1/2; 0; 1/2; 0; 1/2]
n = length(u);

#b
disp('b)');
x = u + v
normax = norm(x)
#normax = sqrt(x'*x);

#c
disp('c)');
H = eye(n) - x*x'
Hu = H*u
Hv = H*v
normaH = norm(H)

#d
disp('d)');
A = u*v'
B = (H^-n)*A*(H^n)
