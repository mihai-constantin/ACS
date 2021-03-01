function x = ApplyHSToPColumn(x, p, sigma)
  m = length(x);
  
  x(p) = -sigma;
  
  for i = p+1:m
    x(i) = 0;
  end
  
endfunction