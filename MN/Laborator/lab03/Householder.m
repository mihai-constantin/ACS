function [Q, R] = Householder(A)
  [m,n] = size(A);
  H = eye(n);
  for p = 1:min(m-1,n)
    [vp, sigma, beta] = GetHSReflector(A(:,p), p);
    Hp = eye(n) - 2*(vp*vp')/(vp'*vp);
    
    A(:,p) = ApplyHSToPColumn(A(:,p), p, sigma);
    for i = p+1:m
      A(:,i) = ApplyHSToRandomColumn(A(:,i), vp, p, beta);
    endfor
    
    H = Hp * H;
  endfor
  Q = H';
  R = A;
endfunction