function x=Jacobi(A,b,x0,tol,maxiter)
	[n n]=size(A);
	succesor=0;
	iter=maxiter;
	x=zeros(n,1);

	while maxiter > 0
		maxiter--;

		for i=1:n
			if i==1
				suma=A(i,i+1)*x0(i+1);
			else
				if i==n
					suma=A(i,i-1)*x0(i-1);
				else
					suma=A(i,i-1:i+1)*x0(i-1:i+1)-A(i,i)*x0(i);
				endif
			endif
			
			x(i)=(b(i)-suma)/A(i,i);
		endfor

		if norm(x-x0)<tol
			succesor=1;
			break;
		endif
		x0=x;
	endwhile

	iter=iter-maxiter;

endfunction