function [A b x] = kirchhoff()

j_1 = 6i;
j_2 = sqrt(2)*(1 + i);
j_3 = 1.5*sqrt(2)*(1-i);

e_1 = -2;
e_2 = 4i;

z_R1 = 6;
z_R2 = 2;
z_R3 = 1;
z_R4 = 1;

z_L = 60i;
z_C = -100i;

z_p1 = (456 + 15i)/229;
z_p2 = (10000-100i)/10001;

i_1 = j_1;
i_2 = j_2;
i_3 = j_3;
i_4 = i_1 + i_2;
i_5 = -i_3 - i_4;
i_6 = i_1 + i_5;

I = [i_1 i_2 i_3 i_4 i_5 i_6];

A = [z_p2 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1];

b = [e_2; -i_4*z_p1-e_1; i_6*z_R3 - i_4*z_p1 - e_1 - e_2; i_6*z_R3-e_1];

x = A \ b;

endfunction
