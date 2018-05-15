clear all;
close all;

file = 'data/data_O2_complex_power2.txt';
file2 = 'data/data_O3_complex_power2.txt';
file3 = 'data/data_flags_complex_power2.txt';


delimiter = ' ';
headerlines = 0;

A = importdata(file, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);


linecolors = jet(20);

figure

subplot(2,2,1)
hold on
plot(A(:, 2), A(:, 1)./A(:,3), 'Color', linecolors(1,:));
plot(A(:, 4), A(:, 1)./A(:, 5), 'Color', linecolors(16,:));
title('default (-O2)');
xlim([200 32768])
legend('SSE4', 'AVX2');
grid on;

subplot(2,2,2)
hold on
plot(B(:, 2), B(:, 1)./B(:, 3), 'Color', linecolors(1,:));
plot(B(:, 4), B(:, 1)./B(:, 5), 'Color', linecolors(16,:));
title('-O3');
%legend('SSE4', 'AVX2');
grid on;

subplot(2,2,3)
hold on
plot(C(:, 2), C(:, 1)./C(:, 3), 'Color', linecolors(1,:));
plot(C(:, 4), C(:, 1)./C(:, 5), 'Color', linecolors(16,:));
title('other opt flags');
 %legend('SSE4', 'AVX2');
grid on;



