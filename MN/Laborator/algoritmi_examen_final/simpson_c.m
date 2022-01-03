function S = simpson_c(N, a, b, f)

    h = (b - a) / N;

    i = 1 : 2 : N-1;
    x = a + i * h;

    s1 = sum(f(x));

    j = 2 : 2: N - 2;
    y = a + j * h;

    s2 = sum(f(y));

    S = h/3 * (f(a) + f(b) + 4 * s1 + 2 * s2);

endfunction
