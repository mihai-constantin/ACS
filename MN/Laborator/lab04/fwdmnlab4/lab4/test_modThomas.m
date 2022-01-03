a = [8:12]';
b = [1:7]';
c = [13:17]';
d = [18:24]';

n = length(d);

A = zeros(n);

for i=1:2
  A(i,i) = b(i);
end

for i=3:n
  A(i,i-2) = a(i-2);
  A(i,i) = b(i);
  A(i-2,i) = c(i-2);
end

disp('Pentru matricea:');
A
disp('si vectorul:');
d
disp('Solutia sistemului Ax = d, aflata prin metoda Thomas, modificata, este:'); 

x = modThomas(a,b,c,d)