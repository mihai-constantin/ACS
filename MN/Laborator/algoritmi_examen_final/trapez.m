function S = trapez(a, b, f)

    h = b - a;
    S = h/2 * (f(a) + f(b));

endfunction
