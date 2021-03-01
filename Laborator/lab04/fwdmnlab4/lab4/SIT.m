function x = SIT(A, b)
  
  n = length(b);
  
  x = zeros(n, 1);
  
  for i = 1:n
    x(i,1) = b(i);
    for j = 1:i-1
      x(i,1) = x(i,1) - A(i,j)*x(j,1);
    endfor
    x(i,1) =  x(i,1) / A(i,i);
    endfor
endfunction