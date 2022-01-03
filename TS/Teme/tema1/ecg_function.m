% CONSTANTIN MIHAI - 321CD

function [person_id] = ecg_function(input_signal, israw)

    numberofValues = 3;

    load 'matrix.mat' M

    numberOfPeople = 90;
    
    Fs = 500;            % sampling frequency
    T = 1/Fs;            % sampling period
    L = 5000;            % length of signal
    t = (0:L-1)*T;       % time vector
    f = Fs*(0:(L/2))/L;  % frecventa
    
    % daca semnalul input_signal nu este clean, il filtrez
    if israw == 1
        % aici filtrez semnalul input_signal
        input_signal = highpass(input_signal, 0.7, Fs);
        input_signal = lowpass(input_signal, 2.2, Fs);
    end
    
    % determin vectorul de caracterizare pentru input_signal
    Y = fft(input_signal);
    P2 = abs(Y/L);
    P1 = P2(1:L/2 + 1);
    P1(2:end-1) = 2*P1(2:end-1); % amplitudinea

    % sortare descrescatoare P1 -> insertion sort
    N = length(P1);
    i = 2;
    while i <= N

        x = P1(i);
        pos_x = f(i);
        j = i - 1;

        while j >= 1 && P1(j) < x
           P1(j + 1) = P1(j);
           f(j + 1) = f(j);
           j = j - 1;
        end

        P1(j + 1) = x;
        f(j + 1) = pos_x;
        i = i + 1;
    end
    
     v = [];
     for i = 1 : numberofValues
        v(2 * i - 1) = P1(i);
        v(2 * i) = f(i);
     end
    
     for i = 1 : numberOfPeople
         d(i) = norm(M(i, :) - v, 2);
     end
 
     % se determina person_id, pe baza valorii minime din vectorul d
     person_id = 1;
     norm_min = d(1);
     
     for i = 2 : numberOfPeople
         if d(i) < norm_min
             norm_min = d(i);
             person_id = i;
         end
     end
end

