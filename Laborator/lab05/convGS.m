%ex 2 c
function [succes]=convGS(A)
	succes=0;
	if(diagonalaDominanta(A))
		succes=1;
		break;
	endif

	[n n]=size(A);
	D=zeros(n);
	L=zeros(n);
	U=zeros(n);
	G=zeros(n);
	D(1,1)=A(1,1);

	for i=2:n
		D(i,i)=A(i,i);
		for j=1:i-1
				L(i,j)=-A(i,j);
				U(j,i)=-A(j,i);
		endfor
	endfor
	G=inv(D-L)*(U);
	
	x=max(abs(eig(G)));
	if ((x+0.00001)<1.00000)
		succes=1;
	endif
endfunction