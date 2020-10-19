# Laborator 2 SM - Evaluarea performantelor programelor paralele
# Odd-Even-Transposition-Sort

# n - valoare simbolica
syms n

# numar de operatii
O1 = n * log2(n);
On = n^2/2;

# timp
T1 = n * log2(n);
Tn = n;

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

# S, R, Q E si U in functie de numarul de procesoare
figure;
plot(x, S(x));
hold on;
plot(x, R(x));
hold on;
plot(x, Q(x));
hold on;
plot(x, E(x));
hold on;
plot(x, U(x));
legend('S','R', 'Q', 'E', 'U');
