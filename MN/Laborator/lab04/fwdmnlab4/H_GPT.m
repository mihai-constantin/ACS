function [A, b] = H_GPT(A, b)
	[n n] = size(A);
	
	for p = 2 : n - 1
		pivot = -inf;
		linie_pivot = -1;
		coloana_pivot = -1;
		
		%calculez maximul in submatricea A(p : n, p : n)
		for i = p : n
			for j = p : n
				if pivot < abs(A(i, j));
					pivot = abs(A(i, j));
					linie_pivot = i;
					coloana_pivot = j;
				endif
			endfor
		endfor

		if p != linie_pivot
			%permutarea liniilor linie_pivot si p
			for j = p-1 : n 
				t = A(p, j);
				A(p, j) = A(linie_pivot, j);
				A(linie_pivot, j) = t;
			endfor
			
			%permutarea elementelor b(linie_pivot) si b(p)
			t = b(linie_pivot);
			b(linie_pivot) = b(p);
			b(p) = t;
		endif
		
		%permutarea coloanelor coloana_pivot si p
		if p != coloana_pivot
			for i = 1 : n 
				t = A(i, p);
				A(i, p) = A(i, coloana_pivot);
				A(i, coloana_pivot) = t;
			endfor
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
					
			b(i) = b(i)-tp*b(p);
		endfor
	endfor
endfunction