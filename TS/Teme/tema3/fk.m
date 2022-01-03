% CONSTANTIN MIHAI - 321CD

clear all;
load('drone_log.mat');

N = length(time_unix_usec_mavlink_system_time_t) - 1;
dt = zeros(1, N);
for k = 1 : N
    % calculam dt(k) pe baza variatiei lui time_unix_usec_mavlink_system_time_t
    dt(k) = (time_unix_usec_mavlink_system_time_t(k+1) - time_unix_usec_mavlink_system_time_t(k))/10^6;
end

% axa Ox
x  = x_mavlink_local_position_ned_t;        % pozitia
vx = vx_mavlink_local_position_ned_t;       % viteza
ax = xacc_mavlink_raw_imu_t;                % acceleratia

C = eye(2);
R = eye(2);
Q = eye(2);
P = rand(2);
I = eye(2);

xc = [x(1); vx(1)];

for i = 2:length(dt)
    A = [1 dt(i); 0 1];
    B = [dt(i)^2/2; dt(i)];
    % predictie
    xc(:,i) = A * xc(:, i-1) + B * ax(i);
    P = A * P * A' + Q;
    
    % actualizare
    G = P * C' * inv(C * P * C' + R);
    xc(:,i) = xc(:,i) + G * ([x(i); vx(i)] - C * xc(:,i));
    P = (I - G * C) * P;
end

filtred_x  = xc(1,:);
filtred_vx = xc(2,:);

subplot(2,1,1);
plot(x);
hold on;
plot(filtred_x);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(vx);
hold on;
plot(filtred_vx);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oy
y  = y_mavlink_local_position_ned_t;        % pozitia
vy = vy_mavlink_local_position_ned_t;       % viteza
ay = yacc_mavlink_raw_imu_t;                % acceleratia

C = eye(2);
R = eye(2);
Q = eye(2);
P = rand(2);
I = eye(2);

xc = [y(1); vy(1)];

for i = 2:length(dt)
    A = [1 dt(i); 0 1];
    B = [dt(i)^2/2; dt(i)];
    % predictie
    xc(:,i) = A * xc(:, i-1) + B * ay(i);
    P = A * P * A' + Q;
    
    % actualizare
    G = P * C' * inv(C * P * C' + R);
    xc(:,i) = xc(:,i) + G * ([y(i); vy(i)] - C * xc(:,i));
    P = (I - G * C) * P;
end

filtred_y  = xc(1,:);
filtred_vy = xc(2,:);

figure;
subplot(2,1,1);
plot(y);
hold on;
plot(filtred_y);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(vy);
hold on;
plot(filtred_vy);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% axa Oz
z  = z_mavlink_local_position_ned_t;        % pozitia
vz = vz_mavlink_local_position_ned_t;       % viteza
az = zacc_mavlink_raw_imu_t;                % acceleratia

C = eye(2);
R = eye(2);
Q = eye(2);
P = rand(2);
I = eye(2);

xc = [z(1); vz(1)];

for i = 2:length(dt)
    A = [1 dt(i); 0 1];
    B = [dt(i)^2/2; dt(i)];
    % predictie
    xc(:,i) = A * xc(:, i-1) + B * az(i);
    P = A * P * A' + Q;
    
    % actualizare
    G = P * C' * inv(C * P * C' + R);
    xc(:,i) = xc(:,i) + G * ([z(i); vz(i)] - C * xc(:,i));
    P = (I - G * C) * P;
end

filtred_z  = xc(1,:);
filtred_vz = xc(2,:);

figure;
subplot(2,1,1);
plot(z);
hold on;
plot(filtred_z);
title('Pozitia');
xlabel('timp');
ylabel('pozitie');

subplot(2,1,2);
plot(vz);
hold on;
plot(filtred_vz);
title('Viteza');
xlabel('timp');
ylabel('viteza');

% traiectoria 3D
figure;
plot3(x, y, z);
hold on;
plot3(filtred_x, filtred_y, filtred_z);
title('Traiectorie 3D');
xlabel('pozitie x');
ylabel('pozitie y');
zlabel('pozitie z');
grid on;

%
%   Filtrul are rezultate bune atat in cazul pozitiilor, cat si in cel al
%   vitezelor calculate, cu exceptia datelor pentru axa Oz.
%   Filtrarea consta in actualizarea vectorului starilor la fiecare
%   iteratie, acesta fiind calculat in functie de matricele P, Q, G si R.
%

