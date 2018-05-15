clear all;
close all;

file = 'data/data_O2_unrolling.txt';
file2 = 'data/data_O3_unrolling.txt';
file3 = 'data/data_flags_complex.txt';
file4 = 'data/data_O2_unrolling.txt';


delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);
D = importdata(file4, delimiter);

linecolors = jet(20);

figure

subplot(1,2,1)
hold on
plot(A(:, 2), A(:, 1), 'Color', linecolors(1,:));
plot(A(:, 4), A(:, 3), 'Color', linecolors(14,:));
plot(A(:, 6), A(:, 5), 'Color', linecolors(17,:));
legend('scalar', 'SSE4', 'AVX2');
title('default (-O2)');
grid on;

subplot(1,2,2)
hold on
plot(B(:, 2), B(:, 1), 'Color', linecolors(1,:));
plot(B(:, 4), B(:, 3), 'Color', linecolors(14,:));
plot(B(:, 6), B(:, 5), 'Color', linecolors(17,:));
title('-O3');
ylim([0 10e9])
grid on;
% 
% subplot(2,2,3)
% hold on
% plot(C(:, 2), C(:, 1), 'Color', linecolors(1,:));
% plot(C(:, 4), C(:, 3), 'Color', linecolors(14,:));
% plot(C(:, 6), C(:, 5), 'Color', linecolors(17,:));
% title('other opt flags');
% grid on;

% subplot(1,2,2)
% hold on
% plot(D(:, 2), D(:, 1), 'Color', linecolors(1,:));
% plot(D(:, 4), D(:, 3), 'Color', linecolors(14,:));
% plot(D(:, 6), D(:, 5), 'Color', linecolors(17,:));
% title('default (-O2) with unrolling');
% ylim([0 12e9]);
% grid on;
% 

