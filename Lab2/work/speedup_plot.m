clear all;
close all;

file = 'data_O2_power2.txt';
file2 = 'data_O3_power2.txt';


delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);


linecolors = jet(20);

figure

subplot(2,1,1)
hold on
plot(A(:, 2), A(:, 1)./A(:,5), 'Color', linecolors(1,:));
plot(A(:, 4), A(:, 1)./A(:, 3), 'Color', linecolors(14,:));
title('default (-O2)');
grid on;

subplot(2,1,2)
hold on
plot(B(:, 2), B(:, 1)./B(:, 5), 'Color', linecolors(1,:));
plot(B(:, 4), B(:, 1)./B(:, 3), 'Color', linecolors(14,:));
title('-O3');
grid on;


