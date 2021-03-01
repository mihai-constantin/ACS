function [A b] = H_GPP(A, b)
	[n n] = size(A);
	
	for p = 2 : n -1
		pivot = -inf;
		linie_pivot = -1;
		
		%calculez maximul dintre elementele A(p : n, p)
		for i = p : n
			if pivot < abs(A(i, p-1));
				pivot = abs(A(i, p-1));
				linie_pivot = i;
			endif
		endfor

		%permutarea liniilor linie_pivot si p
		if p != linie_pivot
			for j = (p-1) : n 
				t = A(p, j);
				A(p, j) = A(linie_pivot, j);
				A(linie_pivot, j) = t;
			endfor
      

			%permutarea elementelor b(linie_pivot) si b(p)
			t = b(linie_pivot);
			b(linie_pivot) = b(p);
			b(p) = t;
		endif
		
		%eliminare gaussiana
		for i = p + 1 : n
			if A(i, p-1) == 0
				continue;
			endif
  
			tp = A(i, p-1)/pivot;
			A(i, p-1) = 0;
			for j = p : n 
				A(i, j) = A(i, j)-tp*A(p, j);
			endfor
     
      for j = 1 : n
        A(j,p) = A(j,p) + tp*A(j,i);
      endfor
					
			b(i) = b(i)-tp*b(p);
		endfor
	endfor
endfunction