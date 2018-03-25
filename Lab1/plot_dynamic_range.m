file1 = 'data_1024_0_Q15.txt'
file2 = 'data_1024_1_Q15.txt'
file3 = 'data_1024_2_Q15.txt'
file4 = 'data_1024_3_Q15.txt'
file5 = 'data_1024_0_Q24.txt'
file6 = 'data_1024_1_Q24.txt'
file7 = 'data_1024_2_Q24.txt'
file8 = 'data_1024_3_Q24.txt'

delimiter = ' ';
headerlines = 0;
str={'X: '};

close all
A = importdata(file1, delimiter);
B = importdata(file2, delimiter);
C = importdata(file3, delimiter);
D = importdata(file4, delimiter);
E = importdata(file5, delimiter);
F = importdata(file6, delimiter);
G = importdata(file7, delimiter);
H = importdata(file8, delimiter);
linecolors = jet(10);

figure

subplot(2,2,1)
hold on
grid on
title('Cosine wave');
y=50;
plot([-40,0],[y,y], 'k');
h1=plot(A(:, 1), A(:, 2), 'Color', linecolors(1,:));
plot(E(:, 1), E(:, 2), 'Color', linecolors(10,:));
datatip(h1, 90, str, 'hold');
datatip(h1, 159, str, 'hold');
x=-24.2;
plot([x,x],[0,100],'k')
x=-31.1;
plot([x,x],[0,100],'k')
ylim([0,100]);


subplot(2,2,2)
hold on
grid on
title('QPSK');

y=50;
plot([-40,0],[y,y], 'k');
h2=plot(B(:, 1), B(:, 2), 'Color', linecolors(1,:));
plot(F(:, 1), F(:, 2), 'Color', linecolors(10,:));
datatip(h2, 84, str, 'hold');
datatip(h2, 334, str, 'hold');
x=-6.7;
plot([x,x],[0,100],'k')
x=-31.7;
plot([x,x],[0,100],'k')




subplot(2,2,3)
hold on
grid on
title('16-QAM');
y=50;
plot([-40,0],[y,y], 'k');
h3=plot(C(:, 1), C(:, 2), 'Color', linecolors(1,:));
plot(G(:, 1), G(:, 2), 'Color', linecolors(10,:));
datatip(h3, 79, str, 'hold');
datatip(h3, 333, str, 'hold');
x=-6.8;
plot([x,x],[0,100],'k')
x=-32.2;
plot([x,x],[0,100],'k')



subplot(2,2,4)
hold on
grid on
title('Gaussian noise');
y=50;
plot([-40,0],[y,y], 'k');
h4=plot(D(:, 1), D(:, 2), 'Color', linecolors(1,:));
plot(H(:, 1), H(:, 2), 'Color', linecolors(10,:));
datatip(h4, 86, str, 'hold');
datatip(h4, 327, str, 'hold');
x=-7.4;
plot([x,x],[0,100],'k')
x=-31.5;
plot([x,x],[0,100],'k')


y=50;
plot([-40,0],[y,y], 'k');
% x=-37.61;
% plot([x,x],[0,90],'k')
% x=-6.386;
% plot([x,x],[0,90],'k')
% x=-7.091;
% plot([x,x],[0,90],'k')
% %title('cosine wave');
% title('16-QAM');
% %title('QPSK');
% grid on;
legend('50 dB','Q15', 'Q24');
% xlim([-40,0]);
% ylim([0,90]);

function hDatatip = datatip(hPlot, index, str, varargin)
 
% function: hDatatip = datatip(hPlot, index, str, varargin)
% hPlot - handle of the plot at which the datatip must appear
% index - index into the data matrix (i.e. axis data) at which the datatip must appear
% str - string cell with strings for the datatip's axis labels
% varargin - type 'hold' in the place of varargin if one want to hold the previous datatips
% hDatatip - datatip handle

% update the figure window 
drawnow update

% set data-cursor mode properties
cursorMode = datacursormode(gcf);
set(cursorMode, 'enable', 'on', 'UpdateFcn', {@datatiptxt, str})

% delete the previous datatip(s) if needed
if strcmp(varargin, 'hold')
else
    cursorMode.removeAllDataCursors
end

% create a datatip
hDatatip = cursorMode.createDatatip(hPlot);
 
% set the datatip marker appearance
set(hDatatip, 'Marker','s', 'MarkerSize',5, 'MarkerFaceColor','k',...
              'MarkerEdgeColor','k', 'OrientationMode','auto')
          
% get the axis data
X = get(hPlot, 'XData');
Y = get(hPlot, 'YData');
Z = get(hPlot, 'ZData');

% determine the datatip position
if isvector(X) && isempty(Z)                % for 2D lines
    pos = [X(index) Y(index) 0];
elseif isvector(X)                          % for 3D lines
    pos = [X(index) Y(index) Z(index)];
else                                        % for 3D surfaces
    pos = [X(index(1), index(2)),...
           Y(index(1), index(2)),...
           Z(index(1), index(2))];
end
              
% move the datatip to the position
% uncomment the next line for Matlab R2014a and earlier 
% set(get(hDatatip, 'DataCursor'), 'DataIndex', index, 'TargetPoint', pos)    
set(hDatatip, 'Position', pos)         
updateDataCursors(cursorMode)

% turn Cursor Mode off
set(cursorMode, 'enable', 'off')

end

function text_to_display = datatiptxt(~, hDatatip, str)

% determine current datatip position
pos = get(hDatatip, 'Position');

% form the X and Y axis datatip labels
text_to_display = {[char(str(1)) num2str(pos(1))]};

% form the Z coordinate datatip label (if exist)
if length(str) > 2
    text_to_display{end+1} = [char(str(3)) num2str(pos(3))];
end

end