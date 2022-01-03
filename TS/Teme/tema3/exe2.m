% CONSTANTIN MIHAI - 321CD

clear all;
load('drone_log.mat');

N = length(time_unix_usec_mavlink_system_time_t);
deltaT = zeros(1, N); % initializare vector deltaT
for k = 1 : N - 1
    % calculam deltaT(k) pe baza variatiei lui time_unix_usec_mavlink_system_time_t
    deltaT(k) = (time_unix_usec_mavlink_system_time_t(k+1) - time_unix_usec_mavlink_system_time_t(k))/10^6;
end

DeltaT = mean(deltaT); % DeltaT = 0.88

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

dimA = length(A);   % dimA = 6
rangA = rank(A);    % rangA = 6
rangB = rank(B);    % rangB = 3
rangC = rank(C);    % rangC = 3

R = ctrb(A, B);  % R = [B A*B A^2 * B ... A^5 * B] -> n = 6
rangR = rank(R); % rangR = 6

% rang(A) = 6 
% n = 6
% nu avem descompunere controlabila
  
%       |   C   |
%       |  C*A  |
%   Q = | C*A^2 |   -> n = 6
%       | C*A^3 |   
%       | C*A^4 |
%       | C*A^5 |

Q = obsv(A, C);
rangQ = rank(Q); % rangQ = 6

% rang(Q) = 6
% n = 6
% nu avem descompunere observabila

if (rangR == dimA) && (rangQ == dimA)
    disp('Sistem minimal');
end


