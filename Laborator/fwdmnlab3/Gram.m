function [Q, R] = Gram(A)
  n = length(A);
 
  for j = 1:n
    aux = A(:,j);
    for i = 1:j-1
      R(i,j) = Q(:,i)' * A(:,j);
      aux = aux - R(i,j) * Q(:,i);
    end
    R(j,j) = norm(aux);
    Q(:,j) = aux / R(j,j);
    end
      
endfunction