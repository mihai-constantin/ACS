function [Q R b] = givens(A, b)
	[m n] = size(A);
	G = eye(m);
	
	for k = 1 : n-1
		for l = k + 1 : m
			r = sqrt(A(k,k)^2 + A(l,k)^2);
			c = A(k,k)/r;
			s = -A(l,k)/r;

			t = c*A(k,k:n) - s*A(l,k:n);
			A(l,k:n) = s*A(k,k:n) + c*A(l,k:n);
			A(k,k:n) = t;

			u = c*b(k) - s*b(l);
			b(l) = s*b(k) + c*b(l);
			b(k) = u;

			t = c*G(k,1:m) - s*G(l,1:m);
			G(l,1:m) = s*G(k, 1:m) + c*G(l,1:m);
			G(k,1:m) = t;
		end
	end
    
	Q = G';
	R = A;
end
