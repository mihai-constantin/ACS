# Laborator 2 SM - Evaluarea performantelor programelor paralele
# Exercitiul 8

# n - valoare simbolica
syms n

# numar de operatii
O1 = n^3;
On = n^3 + n^2 * log2(n);

# timp
T1 = n^3;
Tn = 4*n^3/(n+3);

# numarul de procesoare
x = [1:32];

# accelerarea
s = T1/Tn;
S = function_handle(s);

# eficienta
e = s/n;
E = function_handle(e);

# redundanta
r = On/O1;
R = function_handle(r);

# utilizarea
u = r * e;
U = function_handle(u);

# factorul de calitate
q = s * e / r;
Q = function_handle(q);

# S, R, Q in functie de numarul de procesoare
figure;
plot(x, S(x));
hold on;
plot(x, R(x));
hold on;
plot(x, Q(x));
legend('S','R', 'Q');

# E, U in functie de numarul de procesoare
figure;
plot(x, E(x));
hold on;
plot(x, U(x));
legend('E', 'U');
