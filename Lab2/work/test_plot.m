clear all;
close all;

file = 'data/data_O3.txt';
file2 = 'data/data_flags.txt';
file3 = 'data/data.txt';


delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);

linecolors = jet(20);

figure

subplot(2,2,1)
hold on
plot(A(:, 2), A(:, 1), 'Color', linecolors(1,:));
plot(A(:, 4), A(:, 3), 'Color', linecolors(14,:));
plot(A(:, 6), A(:, 5), 'Color', linecolors(17,:));
legend('scalar', 'SSE4', 'AVX2');
title('-O3');
grid on;

subplot(2,2,2)
hold on
plot(B(:, 2), B(:, 1), 'Color', linecolors(1,:));
plot(B(:, 4), B(:, 3), 'Color', linecolors(14,:));
plot(B(:, 6), B(:, 5), 'Color', linecolors(17,:));
ylim([0 2e9])
title('other opt flags');
grid on;

subplot(2,2,3)
hold on
plot(C(:, 2), C(:, 1), 'Color', linecolors(1,:));
plot(C(:, 4), C(:, 3), 'Color', linecolors(14,:));
plot(C(:, 6), C(:, 5), 'Color', linecolors(17,:));
title('default (-O2)');
grid on;


