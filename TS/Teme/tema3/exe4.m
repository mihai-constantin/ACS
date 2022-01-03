% CONSTANTIN MIHAI - 321CD

clear all;
load('drone_log.mat');

N = length(time_unix_usec_mavlink_system_time_t);
deltaT = zeros(1, N);
for k = 1 : N - 1
    % calculam deltaT(k) pe baza variatiei lui time_unix_usec_mavlink_system_time_t
    deltaT(k) = (time_unix_usec_mavlink_system_time_t(k+1) - time_unix_usec_mavlink_system_time_t(k))/10^6;
end

DeltaT = mean(deltaT); % DeltaT = 0.88

% procedura de alocare a polilor pentru sistemul obtinut la exercitiul 2

% 
%   Matricele A, B, C au fost calculate de mana pentru a verifica noul
%   sistem. Starea si comanda noului sistem sunt:
%   x = [px py px vx vy vz]
%   u = [ax ay az]
%

A = [1 0 0 DeltaT 0 0; 
    0 1 0 0 DeltaT 0; 
    0 0 1 0 0 DeltaT; 
    0 0 0 1 0 0; 
    0 0 0 0 1 0; 
    0 0 0 0 0 1];

B = [DeltaT^2/2 0 0; 
    0 DeltaT^2/2 0; 
    0 0 DeltaT^2/2; 
    DeltaT 0 0; 
    0 DeltaT 0; 
    0 0 DeltaT];

C = [1 0 0 0 0 0; 
    0 1 0 0 0 0; 
    0 0 1 0 0 0];

%
%   polii au fost alesi corespunzator: |p| < 1 (discul unitate)
%

K = place(A, B, [-rand(1); -rand(1); -rand(1); -rand(1); -rand(1); -rand(1)]);

% noua matrice A va avea ca valori proprii termenii din vectorul de mai sus
A = A - B * K; 

%
%   x0 = [px(end); py(end); pz(end); vx(end); vy(end); vz(end)]
%
x0 = [x_mavlink_local_position_ned_t(end); 
    y_mavlink_local_position_ned_t(end);
    z_mavlink_local_position_ned_t(end);
    vx_mavlink_local_position_ned_t(end);
    vy_mavlink_local_position_ned_t(end);
    vz_mavlink_local_position_ned_t(end)];

R = 0.1;
a = [1; 1; 1];

N = length(x_mavlink_local_position_ned_t);
x(:,1) = x0;
for k=1:N
    x(:,k+1) = A * x(:,k) + B * a;
    y(:,k) = C * x(:,k) + rand(3,1) * sqrt(R);
end

% axa Ox
figure;
subplot(2,1,1);
plot(y(1,:));
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(4,:));
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oy
figure;
subplot(2,1,1);
plot(y(2,:));
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(5,:));
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oz
figure;
subplot(2,1,1);
plot(y(3,:));
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(6,:));
title('Viteza');
xlabel('timp');
ylabel('viteza');

% traiectoria 3D
figure;
plot3(y(1, :), y(2, :), y(3, :));
title('Traiectorie 3D');
xlabel('pozitie x');
ylabel('pozitie y');
zlabel('pozitie z');
grid on;

