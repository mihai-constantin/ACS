function r = rk(a, b, n, y0, f1)

    y = zeros(1, n + 1);
    y(1) = y0;
    h = (b - a) / n;
    x = a;

    for i = 1 : n
        K1 = h * f1(x, y(i));
        K2 = h * f1(x + h/2, y(i) + K1/2);
        K3 = h * f1(x + h/2, y(i) + K2/2);
        K4 = h * f1(x + h, y(i) + K3);
    y(i + 1) = y(i) + (K1 + 2*K2 + 2*K3 + K4)/6;
        x = x + h;
    endfor

    r = y(n + 1);

endfunction
