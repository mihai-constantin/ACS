% CONSTANTIN MIHAI - 311CD

function cerinta2()

for T = 1 : 4

    if T == 1
        image = "in/images/image1.gif";
    elseif
        T == 2
            image = "in/images/image2.gif";
    elseif
        T == 3
            image = "in/images/image3.gif";
    elseif
        T == 4
            image = "in/images/image4.gif";
    endif

    A = imread(image); % citire imagine
    A = double(A);

    [m n] = size(A); % dimensiune matrice A

    [U S V] = svd(A);

    figure;

    % 1. reprezentarea grafica a tuturor valorilor singulare ale matricei A in ordine descrescatoare
    subplot(2, 2, 1);
    plot(diag(S));
    title("diag(S)");

    % 2. reprezentarea grafica a informatiei oferite de primele k valori singulare

    k = [1:19 20:20:99 100:30:min(m,n)]; % valoare random pentru k

    y_2 = zeros(1, length(k)); % initializare vector y_2

    for i = 1 : length(k)
        y_2(i) = trace(S(:, [1:k(i)])) / trace(S);
    endfor

    subplot(2, 2, 2);
    plot(k, y_2);
    title("informatia data de primele k valori singulare");

    % 3. reprezentarea grafica a erorii aproximarii pentru matricea A

    y_3 = zeros(1, length(k)); % initializare vector y_3

    for q = 1 : length(k)

        A_k = cerinta1(image, k(q));

        sum = 0;
        for i = 1 : m
            for j = 1 : n
                x = A(i,j) - A_k(i,j);
                sum = sum + x * x;
            endfor
        endfor

        y_3(q) = sum / (m * n);

    endfor

    subplot(2, 2, 3);
    plot(k, y_3);
    title("eroarea aproximarii pentru matricea A");

    % 4. reprezentarea grafica a ratei de compresie a datelor

    y_4 = zeros(1, length(k)); % initializare vector y_4

    for i = 1 : length(k)
        y_4(i) = (m * k(i) + n * k(i) + k(i)) / (m * n);
    endfor

    subplot(2, 2, 4);
    plot(k, y_4);
    title("rata de compresie a datelor");

endfor

endfunction
