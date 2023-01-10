close all
clearvars
clear
clc

% pause(10);
% 关闭并删除已占用端口
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
% 端口配置
s = serialport('com11', 57600); % 创建串行端口对象
s.Timeout = 300; % 300秒未读到串口数据报错
s.flush();

k = 0;
m = 0;
n = 0;

AD_INT = zeros(20, 1);
A = zeros(5, 1);
B = zeros(4, 1);
res = 0;

%CC = 100; %unit: mV
CC = 150; %unit: mV

CC_RT1 = 0;
CC_RT2 = 0;
USE_POINTS = 100;
KEEP_CYCLES = 10;
AVG_RT_NUM = 2;
CC_RT1_AVG = zeros(AVG_RT_NUM, 1);
CC_RT2_AVG = zeros(AVG_RT_NUM, 1);
Y_MAX_VALUE = CC*15;
pp = zeros(USE_POINTS, 1);
h1 = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[0 .7 .7], 'LineWidth', 1);
h2 = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[0 .3 .9], 'LineWidth', 1);
hcc = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[1 0 0], 'LineWidth', 1);
yy = (1:1:USE_POINTS);
axis([-inf inf 0 Y_MAX_VALUE]);

str = '---';
h_annot1 = annotation('textbox',[.15 .6 .3 .3],'String',str,'FitBoxToText','on', 'FontSize', 80, 'Color', 'red','EdgeColor','none');
h_annot2 = annotation('textbox',[.15 .4 .3 .3],'String',str,'FitBoxToText','on', 'FontSize', 80, 'Color', 'blue','EdgeColor','none');

s.flush();
tStart = 0;
while(1)
    % 数据获取
    for i=1:20
        while(1)
            check_head = read(s, 1, 'uint8');
            while check_head ~= 170
                check_head = read(s, 1, 'uint8');
            end
            AD_INT(i, 1) = read(s, 1, 'uint16');
            check_end = read(s, 1, 'uint8');
            if check_end == 235
                break
            end
        end
    end

    for j=0:4
        AD_INT2 = bubble_sort(AD_INT(j*4+1:j*4+4, 1));
        AD_INT2 = AD_INT2(2:end - 1);
        A(j+1, 1) = sum(AD_INT2) / 2;
    end

    A2 = bubble_sort(A);
    k = k + 1;

    if k <= 3
        B(k, 1) = A2(end) - A2(1);
    else
        B(1:end - 1, 1) = B(2:end, 1);
        B(end, 1) = A2(end) - A2(1);
    end

    %output
    if B(3) >= (B(1) + CC*4096/1250) && B(2) >= (B(1) + CC*4096/1250)
        res = 1;
    else
        res = 0;
    end

    CC_RT1 = (B(3) - B(1))*1250/4096;
    CC_RT2 = (B(2) - B(1))*1250/4096;

    %addpoints(h1, k, abs(CC_RT1));
	%addpoints(h2, k, abs(CC_RT2));
    %addpoints(hcc, k, CC);
    
    if abs(CC_RT1) >= CC
        addpoints(h1, k, abs(CC_RT1));
        m = m + 1;
        CC_RT1_AVG(m, 1) = abs(CC_RT1);

        if m == 1
            txt = sprintf('RT1: %3.3f mV',abs(CC_RT1));
            set(h_annot1,'String',txt)
        else
            if mod(m, AVG_RT_NUM) == 0
                txt = sprintf('RT1: %3.3f mV',mean(CC_RT1_AVG));
                set(h_annot1,'String',txt)
                m = 0;
            end
        end
    end
    
    if abs(CC_RT2) >= CC
        addpoints(h2, k, abs(CC_RT2));
        n = n + 1;
        CC_RT2_AVG(n, 1) = abs(CC_RT2);

        if n == 1
            txt = sprintf('RT2: %3.3f mV',abs(CC_RT2));
            set(h_annot2,'String',txt)
        else
            if mod(n, AVG_RT_NUM) == 0
                txt = sprintf('RT2: %3.3f mV',mean(CC_RT2_AVG));
                set(h_annot2,'String',txt)
                n = 0;
            end
        end
    end
    
    drawnow limitrate

    tEnd = (cputime - tStart)*1000;
    tStart = cputime;
end

function y=bubble_sort(x)
    x_len=length(x);
    for i=1:x_len-1
        for j=1:x_len-i
            if(x(j)>x(j+1))
                [x(j),x(j+1)]=swap(x(j),x(j+1));
            end
        end
    end
    y=x;
end

function [a,b]=swap(x,y)
    a=y;
    b=x;
end


