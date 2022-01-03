% Subpunctul a)

syms s I1 I2 I6 I7 I8 I9 U1 U2 U3

% sistem cu 9 ecuatii si 9 necunoscute

eq1 = I1 + I2 - I9 == 3/s;
eq2 = I6 + I7 + I8 == -3/s;
eq3 = -I8 + I9 == 6/s;
eq4 = I1 + I2 == 4/s;
eq5 = I1*(6 + (0.6 * s)/pi) - 2*I2 == 0.6/pi;
eq6 = 2*I2 + U1 == -2/s;
eq7 = I8 + U3 == -2/s;
eq8 = I6 - I8 + U1 + U2 == 0;
eq9 = -I6 + I7 * ((10000*pi)/s) == -4/s;

system = [eq1; eq2; eq3; eq4; eq5; eq6; eq7; eq8; eq9];

solution = solve(system, [I1 I2 I6 I7 I8 I9 U1 U2 U3]);

I1 = solution.I1;
I2 = solution.I2;
I6 = solution.I6;
I7 = solution.I7;
I8 = solution.I8;
I9 = solution.I9;
U1 = solution.U1;
U2 = solution.U2;
U3 = solution.U3;

% Subpunctul b)

I_L_s = partfrac(I1);
U_C_s = partfrac(I6); % I6 * R4

I_L_0 = limit(s * I_L_s, s, inf);
U_C_0 = limit(s * U_C_s, s, inf);

I_L_inf = limit(s * I_L_s, s, 0);
U_C_inf = limit(s * U_C_s, s, 0);

% Subpunctul c)

graph = ilaplace(I_L_s)
F = matlabFunction(graph);
x = [0 : 0.0001 : 0.1];
plot(x, F(x));
title('Expresia instantanee a lui I_L(s)');
