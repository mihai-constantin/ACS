Fs = 1000;              % sampling frequency
T = 1 / Fs;             % sampling period
L = 1500;               % length of signal
t = (0 : L-1) * T;      % time vector
f = Fs * (0:(L/2))/L;

S = 0.7 * sin(2*pi * 50*t) + sin(2*pi * 120*t); % semnal filtrat
X = S + 2 * randn(size(t));

Y = fft(S);
P2 = abs(Y/L);
P1 = P2(1:L/2 + 1);
P1(2:end-1) = 2*P1(2:end-1);

plot(f, P1, 'r');
hold on;


Y = fft(X);
P2 = abs(Y/L);
P1 = P2(1:L/2 + 1);
P1(2:end-1) = 2*P1(2:end-1);
plot(f, P1, 'g');

title('Amplitude Spectrum of S(t)');
xlabel('f(Hz)');
ylabel('|P1(f)|');
