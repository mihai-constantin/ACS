function [ok]=diagonalaDominanta(A)
	ok=1;
	[n n]=size(A);
	for i=1:n
		a=0;
		for j=1:n
			a=a+abs(A(i,j));
		endfor
		a=a-abs(A(i,i));
		if ((abs(A(i,i))+0.00001)<a)
			ok=0;
			break;
		endif
	endfor
endfunction