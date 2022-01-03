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

A = [1 DeltaT; 0 1];
B = [DeltaT^2/2; DeltaT];
C = [1 0; 0 1];

K = place(A,B,[-0.1 -0.2]);

% noua matrice A va avea ca valori proprii -0.1 si -0.2
A = A - B * K;

x0 =  [x_mavlink_local_position_ned_t(end); 
    vx_mavlink_local_position_ned_t(end)];
R  = 0.1;
a  = 1;

N = length(x_mavlink_local_position_ned_t);
x(:,1) = x0;
for k=1:N
    x(:,k+1) = A * x(:,k) + B * a;
    y(:,k) = C * x(:,k) + rand(2,1) * sqrt(R);
end

subplot(2,1,1);
plot(y(1,:));
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(y(2,:));
title('Viteza');
xlabel('timp');
ylabel('viteza');
