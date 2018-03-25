file = 'formatted_data_0_Q24.txt';
file2 = 'formatted_data_round_Q24.txt';
file3 = 'formatted_data_1_Q24.txt';
file4 = 'formatted_data_2_Q24.txt';
file5 = 'formatted_data_3_Q24.txt';

delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);
D = importdata(file4, delimiter);
E = importdata(file5, delimiter);

linecolors = jet(10);

figure
hold on
subplot(2,2,1)
hold on
plot(A(:, 5), A(:, 6), 'Color', linecolors(1,:));
plot(B(:, 1), B(:, 2), 'Color', linecolors(9,:));
title('Cosine wave');
grid on;

subplot(2,2,2)
hold on
plot(C(:, 5), C(:, 6), 'Color', linecolors(1,:));
plot(B(:, 3), B(:, 4), 'Color', linecolors(9,:));
title('QPSK');
grid on;

subplot(2,2,3)
hold on
plot(D(:, 5), D(:, 6), 'Color', linecolors(1,:));
plot(B(:, 5), B(:, 6), 'Color', linecolors(9,:));
title('16-QAM');
grid on;

subplot(2,2,4)
hold on
plot(E(:, 5), E(:, 6), 'Color', linecolors(1,:));
plot(B(:, 7), B(:, 8), 'Color', linecolors(9,:));
title('Gaussian noise');
grid on;

legend('truncation', 'rounding');





