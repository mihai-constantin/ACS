function x = modThomas(a,b,c,d)
  n = length(d);
 
  %transform a astfel incat sa aiba n elemente, cu primul element 0
 	a = [0; 0; a];

	% Operatiile la limita;
	c(1) = c(1)/b(1); 
	d(1) = d(1)/b(1);  
 
  if n >= 4
    c(2) = c(2)/b(2);
  endif
    d(2) = d(2)/b(2);
  
 	% calculul coeficientilor pe caz general.
	for i = 3 : n-2
		temp = b(i)-a(i)*c(i-2);
		c(i) = c(i)/temp;
		d(i) = (d(i)-a(i)*d(i-2))/temp;
	endfor
  d(n-1) = (d(n-1)-a(n-1)*d(n-3))/(b(n-1)-a(n-1)*c(n-3));
	d(n) = (d(n)-a(n)*d(n-2))/(b(n)-a(n)*c(n-2));
 
	% Substitutia inapoi pentru rezolvarea sistemului de ecuatii
	x(n) = d(n);
  x(n-1) = d(n-1);
	for i = n-2 : -1 : 1
		x(i) = d(i)-c(i)*x(i+2);
	endfor
  x=x';
endfunction