A = input('Introduceti matricea: ');[n n] = size(A);for i = 1 : n - 1  A1 = A([1 : i], [1 : i]);   %disp(det(A1));    A4 = A([i + 1 : n], [i + 1 : n]);    %disp(det(A4));  disp('');    A2 = A([i + 1 : n], [1 : i]);  A3 = A([1 : i], [i + 1 : n]);    if det(A1) != 0 && det(A4) != 0    %disp('ok');    break;  endifendfordisp('A1: ')disp(A1);disp('A2: ');disp(A2);disp('A3: ');disp(A3);disp('A4: ');disp(A4);X1 = inv(A1 - A3 * inv(A4) * A2);X2 = -inv(A4) * A2 * X1;X4 = inv(A4 - A2 * inv(A1) * A3);X3 = -inv(A1) * A3 * X4;disp('X1: ')disp(X1);disp('X2: ');disp(X2);disp('X3: ');disp(X3);disp('X4: ');disp(X4);X([1 : i], [1 : i]) = X1;X([i + 1 : n], [1 : i]) = X2;X([1 : i], [i + 1 : n]) = X3;X([i + 1 : n], [i + 1 : n]) = X4;disp('X: ');disp(X);