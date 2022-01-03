function [U I] = sin()

out = fopen('sin.out', 'w'); % deschidere fisier de iesire

i_1 = 6i;
i_2 = sqrt(2)*(1 + i);
i_3 = 1.5*sqrt(2)*(1-i);
i_4 = i_1 + i_2;
i_5 = -i_3 - i_4;
i_6 = i_1 + i_5;
i_8 = -0.04+4i;
i_7 = i_2 - i_8;

I = [i_1; i_2; i_3; i_4; i_5; i_6; i_7; i_8];

U = [-0.33043 - 14.85631i; -3.86596 - 18.14920i; -1.53553 +  0.70711i; -2.3304 - 14.8563i; 2; -3.53553 + 0.70711i; -4i; -4i];

for i = 1 : 8

    modul = abs(I(i));
    argument = arg(I(i));

    if argument > 0
        fprintf(out, "I%d = %f * sqrt(2) * sin(100 * pi * t + %f)\n", i, modul, argument);
    endif

    if argument < 0
        fprintf(out, "I%d = %f * sqrt(2) * sin(100 * pi * t - %f)\n", i, modul, abs(argument));
    endif

endfor

fprintf(out, "\n");

for i = 1 : 8

    modul = abs(U(i));
    argument = arg(U(i));

    if argument > 0
        fprintf(out, "U%d = %f * sqrt(2) * sin(100 * pi * t + %f)\n", i, modul, argument);
    endif

    if argument < 0
        fprintf(out, "U%d = %f * sqrt(2) * sin(100 * pi * t - %f)\n", i, modul, abs(argument));
    endif

endfor

fclose(out);

endfunction
