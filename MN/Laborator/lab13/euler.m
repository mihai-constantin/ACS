function [x y] = euler(x0, h, n, y0, f1)

    y(1) = y0;
    x(1) = x0;

    for i = 1 : n
        y(i + 1) = y(i) + h * f1(x(i), y(i));
        x(i + 1) = x(i) + h;
    endfor

endfunction
