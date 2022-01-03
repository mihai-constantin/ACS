function S = trapez_c(N, a, b, f)

    h = (b - a) / N;

    i = 1 : N-1;
    suma = sum(f(a + i * h));

    S = h/2*(f(a) + f(b) + 2 * suma);

endfunction
