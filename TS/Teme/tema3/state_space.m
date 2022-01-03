% CONSTANTIN MIHAI - 321CD

clear all;
load('drone_log.mat');

N = length(time_unix_usec_mavlink_system_time_t);
deltaT = zeros(1, N); % initializare vector deltaT
for k = 1 : N - 1
    % calculam deltaT(k) pe baza variatiei lui time_unix_usec_mavlink_system_time_t
    deltaT(k) = (time_unix_usec_mavlink_system_time_t(k+1) - time_unix_usec_mavlink_system_time_t(k))/10^6;
end

% am considerat deltaT(N) = 0

DeltaT = mean(deltaT); % DeltaT = 0.88

%   cazul invariant
A = [1 DeltaT; 0 1];
B = [DeltaT^2/2; DeltaT];
C = [1 0];

% axa Ox
x0 = [x_mavlink_local_position_ned_t(1); vx_mavlink_local_position_ned_t(1)];
R  = 0.1;
a  = xacc_mavlink_raw_imu_t;

N = length(x_mavlink_local_position_ned_t);
x(:,1) = x0;
for k=1:N
    x(:,k+1) = A * x(:,k) + B * a(k);
    y(:,k) = C * x(:,k) + rand(1) * sqrt(R);
end

subplot(2,1,1);
plot(y);
hold on;
plot(x_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vx_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oy
y0 = [y_mavlink_local_position_ned_t(1); vy_mavlink_local_position_ned_t(1)];
a = yacc_mavlink_raw_imu_t;

N = length(y_mavlink_local_position_ned_t);
x(:,1) = y0;
for k = 1 : N
    x(:, k + 1) = A * x(:, k) + B * a(k);
    y(:, k) = C * x(:, k) + rand(1) * sqrt(R);
end

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(y_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vy_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oz
z0 = [z_mavlink_local_position_ned_t(1); vz_mavlink_local_position_ned_t(1)];
a = zacc_mavlink_raw_imu_t;

N = length(z_mavlink_local_position_ned_t);
x(:, 1) = z0;
for k = 1: N
    x(:, k + 1) = A * x(:, k) + B * a(k);
    y(:, k) = C * x(:, k) + rand(1) * sqrt(R);
end

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(z_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vz_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% cazul variant

% axa Ox
x0 = [x_mavlink_local_position_ned_t(1); vx_mavlink_local_position_ned_t(1)];
a  = xacc_mavlink_raw_imu_t;

N = length(x_mavlink_local_position_ned_t);
x(:,1) = x0;
for k=1:N
    % in cazul variant, matricile A si B
    % sunt calculate la fiecare iteratie
    A = [1 deltaT(k); 0 1];
    B = [(deltaT(k)^2)/2; deltaT(k)];
    x(:,k+1) = A * x(:,k) + B * a(k);
    y(:,k) = C * x(:,k) + rand(1) * sqrt(R);
end

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(x_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vx_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oy
y0 = [y_mavlink_local_position_ned_t(1); vy_mavlink_local_position_ned_t(1)];
a = yacc_mavlink_raw_imu_t;

N = length(y_mavlink_local_position_ned_t);
x(:, 1) = y0;
for k=1:N
    %  in cazul variant, matricile A si B
    % sunt calculate la fiecare iteratie
    A = [1 deltaT(k); 0 1];
    B = [(deltaT(k)^2)/2; deltaT(k)];
    x(:,k+1) = A * x(:,k) + B * a(k);
    y(:,k) = C * x(:,k) + rand(1) * sqrt(R);
end

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(y_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vy_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oz
z0 = [z_mavlink_local_position_ned_t(1); vz_mavlink_local_position_ned_t(1)];
a = zacc_mavlink_raw_imu_t;

N = length(z_mavlink_local_position_ned_t);
x(:, 1) = z0;
for k=1:N
    %  in cazul variant, matricile A si B
    % sunt calculate la fiecare iteratie
    A = [1 deltaT(k); 0 1];
    B = [(deltaT(k)^2)/2; deltaT(k)];
    x(:,k+1) = A * x(:,k) + B * a(k);
    y(:,k) = C * x(:,k) + rand(1) * sqrt(R);
end

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(z_mavlink_local_position_ned_t);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(x(2,:));
hold on;
plot(vz_mavlink_local_position_ned_t);
title('Viteza');
xlabel('timp');
ylabel('viteza');
