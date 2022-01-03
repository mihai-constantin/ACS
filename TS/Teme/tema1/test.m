% CONSTANTIN MIHAI - 321CD

% script care testeaza acuratetea filtrului aplicat pentru semnalele raw
% pentru fiecare persoana aplic functia ecg_function
% daca person_id == i, se incrementeaza nr

numberOfPeople = 90;
nr = 0;

fprintf('-----     Persoanele care au dat match     -----\n');

for i = 1 : 90
    
    myFile = 'rec_1m.mat';
    
    myDirectory = 'Person_';            
    chr = int2str(i);
    
    if i < 10
        myDirectory = strcat(myDirectory, '0');
        myDirectory = strcat(myDirectory, chr);
    else
        myDirectory = strcat(myDirectory, chr);
    end
    
    fileName = fullfile('ECG-DB', myDirectory, myFile);
    
    % directorul parinte: 321CD_Constantin_Mihai_Tema1TS
    load(fileName);

    person_id = ecg_function(val(1, :), 1);
   
    if i == person_id
        fprintf('%d ', person_id);
        nr = nr + 1;
        if mod(nr, 15) == 0
            fprintf('\n');
        end
    end
    
end

fprintf('\n');
fprintf('match: %d/90\n', nr);
percent = 10 * nr / 9;
fprintf('percent: %.2f%%\n', percent);
