% CONSTANTIN MIHAI - 321CD

numberOfPeople = 90;
numberOfValues = 3;

for Q = 1 : numberOfPeople
    
    % incarcam variabila val in workspace
    
    myFile = 'rec_1m.mat';
    
    myDirectory = 'Person_';            
    chr = int2str(Q);
    
    if Q < 10
        myDirectory = strcat(myDirectory, '0');
        myDirectory = strcat(myDirectory, chr);
    else
        myDirectory = strcat(myDirectory, chr);
    end
    
    fileName = fullfile('ECG-DB', myDirectory, myFile);
    
    % directorul parinte: 321CD_Constantin_Mihai_Tema1TS
    load(fileName);

    Fs = 500;           % sampling frequency
    T = 1/Fs;           % sampling period
    L = 5000;           % length of signal
    t = (0:L-1)*T;      % time vector
    f = Fs*(0:(L/2))/L; % frecventa

    Y = fft(val(2,:));
    P2 = abs(Y/L);
    P1 = P2(1:L/2 + 1);
    P1(2:end-1) = 2*P1(2:end-1); % amplitudinea

    % sortare descrescatoare P1 -> insertion sort
    f1 = f;
    N = length(P1);
    i = 2;
    while i <= N

        x = P1(i);
        pos_x = f1(i);
        j = i - 1;

        while j >= 1 && P1(j) < x
           P1(j + 1) = P1(j);
           f1(j + 1) = f1(j);
           j = j - 1;
        end

        P1(j + 1) = x;
        f1(j + 1) = pos_x;
        i = i + 1;
    end

    % formez vectorul de caracterizare pentru persoana curenta Q
    % vectorul de caracterizare este de forma
    % P1(1), f(1), P1(2), f(2), ..., P1(n), f(n), unde
    % P1(i) este amplitudinea i si 2*pi*f(i) este pulsatia corespunzatoare
    % am considerat n = 3 -> length(v) = 6

    for i = 1 : numberOfValues
        v(2 * i - 1) = P1(i);
        v(2 * i) = f1(i);
    end

    % adaugam vectorul de caracterizare al persoanei curente in matrice
    M(Q, :) = v;

end

% salvam in fisierul matrix.mat matricea care contine vectorii de
% caracterizare pentru fiecare persoana
save ('matrix.mat','M'); 
    
