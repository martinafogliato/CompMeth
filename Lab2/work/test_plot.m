clear all;
close all;

file = 'data.txt';

delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);

linecolors = jet(10);

figure
hold on
plot(A(:, 2), A(:, 1), 'Color', linecolors(1,:));
plot(A(:, 4), A(:, 3), 'Color', linecolors(9,:));
%title('');
grid on;


