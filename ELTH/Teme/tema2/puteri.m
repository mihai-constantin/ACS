function [S_gen S_cons] = puteri()

z_p1 = (456 + 15i) / 229;
i_4 = sqrt(2) + i*(6 + sqrt(2));

z_p2 = (10000 - 100i)/10001;
i_8 = -0.04 + 4i;

z_R3 = 1;
i_6 = -2.5 * sqrt(2) + i * 0.5 * sqrt(2);

S_cons = z_p1 * (abs(i_4)^2) + z_p2 * (abs(i_8)^2) + z_R3 * (abs(i_6)^2);

e_1 = -2;
i_5 = -2.5 * sqrt(2) + i * (0.5 * sqrt(2) - 6);

e_2 = 4j;
i_2 = sqrt(2) * (1 + i);
i_7 = i_2 - i_8;

i_1 = 6i;
i_3 = 1.5 * sqrt(2) * (1 - i);

u_1 = -0.33043 - 14.85631i;
u_2 = -3.86596 - 18.14920i;
u_3 = -1.53553 + 0.70711i;

S_gen = e_1 * i_5' - e_2 * i_7' - u_1 * i_1' - u_2 * i_2' - u_3 * i_3';

endfunction
