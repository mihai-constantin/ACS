function x = ApplyHSToRandomColumn(x, vp, p, beta)
  m = length(x);
  t = 0;
  for i = p:m
    t = t + vp(i)*x(i);
  end
  t = t / beta;
  
  for i = p:m
    x(i) = x(i) - t*vp(i);
  end
  
endfunction