function b = Lagrange(a, x, y)
    % valoare polinom Lagrange in a
    n = length(x);
    V = (a-diag(x))*~eye(n) + eye(n);
    U = diag(x) * ones(n) - ones(n) * diag(x) + eye(n);
    b = prod(V)./prod(U) * y;
end
