file = 'formatted_data_0_Q15.txt';
file2 = 'formatted_data_1_Q15.txt';
file3 = 'formatted_data_2_Q15.txt';
file4 = 'formatted_data_3_Q15.txt';

delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);
D = importdata(file4, delimiter);

linecolors = jet(10);

figure

subplot(2,2,1);
hold on
plot(A(:, 1), A(:, 2), 'Color', linecolors(1,:));
plot(A(:, 3), A(:, 4), 'Color', linecolors(3,:));
plot(A(:, 5), A(:, 6), 'Color', linecolors(6,:));
plot(A(:, 7), A(:, 8), 'Color', linecolors(9,:));
title('Cosine wave');
grid on;


subplot(2,2,2);
hold on
plot(B(:, 1), B(:, 2), 'Color', linecolors(1,:));
plot(B(:, 3), B(:, 4), 'Color', linecolors(3,:));
plot(B(:, 5), B(:, 6), 'Color', linecolors(6,:));
plot(B(:, 7), B(:, 8), 'Color', linecolors(9,:));
title('QPSK');
legend('64', '256', '1024', '4096');
grid on;


subplot(2,2,3);
hold on
plot(C(:, 1), C(:, 2), 'Color', linecolors(1,:));
plot(C(:, 3), C(:, 4), 'Color', linecolors(3,:));
plot(C(:, 5), C(:, 6), 'Color', linecolors(6,:));
plot(C(:, 7), C(:, 8), 'Color', linecolors(9,:));
grid on;
title('16-QAM');


subplot(2,2,4);
hold on
plot(D(:, 1), D(:, 2), 'Color', linecolors(1,:));
plot(D(:, 3), D(:, 4), 'Color', linecolors(3,:));
plot(D(:, 5), D(:, 6), 'Color', linecolors(6,:));
plot(D(:, 7), D(:, 8), 'Color', linecolors(9,:));
grid on;
title('Gaussian noise');




