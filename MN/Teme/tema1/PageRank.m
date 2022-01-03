% CONSTANTIN MIHAI - 311CD

function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out

    nume_out = strcat(nume, '.out'); % concatenare
    out = fopen(nume_out, 'w'); % deschidere fisier de iesire

    R1 = Iterative(nume, d, eps);

    N = length(R1);
    fprintf(out, '%d\n', N);

    for i = 1: N
        fprintf(out, '%f\n', R1(i));
    endfor

    fprintf(out, '\n');

    R2 = Algebraic(nume, d, eps);

    for i = 1: N
        fprintf(out, '%f\n', R2(i));
    endfor

    fprintf(out, '\n');

    % vectorul de pozitie al fiecarui element
    for i = 1: N
        pos(i) = i;
    endfor

    % sortare descrescatoare vector R -> insertion sort
    i = 2;
    while i <= N

        x = R2(i);
        pos_x = pos(i);
        j = i - 1;

        while j >= 1 && (R2(j) < x || abs(R2(j) - x) < eps)
            R2(j + 1) = R2(j);
            pos(j + 1) = pos(j);
            j = j - 1;
        endwhile

        R2(j + 1) = x;
        pos(j + 1) = pos_x;
        i = i + 1;

    endwhile

    %citire fisier de intrare
    in = fopen(nume, 'r');

    input = fscanf(in, '%f');
    length = length(input);

    % afisare in fisier de output
    for i = 1 : N
        fprintf(out, '%d %d %f\n', i, pos(i), Apartenenta(R2(i), input(length - 1), input(length)));
    endfor

    fclose(out);

endfunction
