function [A, b, v] = GPPS(A, b);
  
  n = length(A);
  s = max(abs(A'))';
  v = (1:n)';
  for p = 1:(n-1)
    k = abs(A(:,p))./s;
    ip = max(k(p:n));
    for j = p:n
      if k(j) == ip
        ip = j;
        break;
      endif
    endfor
    v(p) = ip;
    
    l = A(ip, :);
    A(ip, :) = A(p, :);
    A(p, :) = l;
    
    e = b(ip);
    b(ip) = b(p);
    b(p) = e;
    
    for i = p+1:n
      u(i,p) = A(i,p)/A(p,p);
      A(i,p) = 0;
      for j = p+1 : n
        A(i,j) = A(i,j)-u(i,p)*A(p,j);
       end
       b(i) = b(i)-u(i,p)*b(p);
      end 
  endfor;
  
endfunction

  
