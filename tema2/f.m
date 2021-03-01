function y = f(r, a)
    
    if r > a
        y = (1/r^2) * (a^6/6 + 7*a^3/3);
    else
         y = r^4/6 + 7*r/3;
    endif

endfunction

