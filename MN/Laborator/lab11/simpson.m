function S = simpson(a, b, f)

    h = (b - a) / 2;
    S = h/3 * (f(a) + 4 * f((a + b)/2) + f(b));

endfunction
