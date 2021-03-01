function [vp, sigma, beta] = GetHSReflector(x, p)
  m = length(x);
  
  sigma = 0;
  for i = p:m
    sigma = sigma + x(i)^2;
  end
  sigma = sqrt(sigma);
  sigma = sigma * sign(x(p));
  
  for i = 1:p-1
    vp(i) = 0;
  end
  vp(p) = x(p) + sigma;
  for i = p+1:m
    vp(i) = x(i);
  end
  vp = vp';
  
  beta = sigma * vp(p);
  
  endfunction
    