function [x] = SIT(A, b)  [n n] = size(A);    for i = 1 : n        s = 0;    for j = 1 : i - 1      s += A(i, j) * x(j);    endfor        x(i) = (b(i) - s) / A(i, i);    endforendfunction