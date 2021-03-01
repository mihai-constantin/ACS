function sample()

    i2 = sqrt(2) * (1 + i);
    t = [0 : 0.001 : 0.3];
    I2 = abs(i2) * sqrt(2) * sin(100 * pi .* t + angle(i2));
    plot(t, I2);

endfunction
