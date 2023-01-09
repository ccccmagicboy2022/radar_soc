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
s = serialport('com22', 57600); % 创建串行端口对象
s.Timeout = 300; % 300秒未读到串口数据报错
s.flush();

k = 0;

AD_INT = zeros(20, 1);
A = zeros(5, 1);
B = zeros(4, 1);
res = 0;

CC = 12; %unit: mV

CC_RT = 0;
USE_POINTS = 100;
KEEP_CYCLES = 10;
Y_MAX_VALUE = CC*2;
pp = zeros(USE_POINTS, 1);
h = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[0 .7 .7], 'LineWidth', 1);
hcc = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[1 0 0], 'LineWidth', 1);
yy = (1:1:USE_POINTS);
axis([-inf inf 0 Y_MAX_VALUE]);

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

    if B(3) > B(2)
        CC_RT = (B(3) - B(1))*1250/4096;
    else
        CC_RT = (B(2) - B(1))*1250/4096;
    end
    
    addpoints(h, k, abs(CC_RT));
    addpoints(hcc, k, CC);
    
    if abs(CC_RT) >= CC
        title([num2str(abs(CC_RT), '%3.3f'),'mV'], 'FontSize', 100);
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

