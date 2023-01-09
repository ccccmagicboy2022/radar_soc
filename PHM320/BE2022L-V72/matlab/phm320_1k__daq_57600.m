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
s = serialport('com8', 57600); % 创建串行端口对象
s.Timeout = 300; % 300秒未读到串口数据报错

i = 0;
j = 0;
k = 0;
m = 0;
n = 0;

AD_INT = zeros(4, 1);
A = zeros(5, 1);
B = zeros(4, 1);
res = 0;
CC = 45; %unit: mV
CC_RT = 0;
USE_POINTS = 100;
KEEP_CYCLES = 10;
Y_MAX_VALUE = 500;
pp = zeros(USE_POINTS, 1);
h = animatedline('MaximumNumPoints', USE_POINTS*KEEP_CYCLES, 'Color',[0 .7 .7], 'LineWidth', 1);
yy = (1:1:USE_POINTS);
axis([-inf inf 0 Y_MAX_VALUE]);

while(1)
    % 数据获取
    while(1)
        check_head = read(s, 1, 'uint8');
        while check_head ~= 170
            check_head = read(s, 1, 'uint8');
        end
        data = read(s, 1, 'uint16');
        check_end = read(s, 1, 'uint8');
        if check_end == 235
            i = i + 1;
            break
        end
    end

    AD_INT(i, 1) = data;
    if mod(i,4) == 0
        i = 0;
        AD_INT2 = sort(AD_INT, 1, 'ascend');
        AD_INT2 = AD_INT2(2:end - 1);
        j = j + 1;
        A(j, 1) = sum(AD_INT2) / 2;
        if mod(j,5) == 0
            j = 0;
            A2 = sort(A, 1, 'ascend');
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

            if B(3) < B(2)
                CC_RT = (B(3) - B(1))*1250/4096;
            else
                CC_RT = (B(2) - B(1))*1250/4096;
            end

            m = m + 1;
            n = n + 1;
            addpoints(h, n, abs(CC_RT));
            drawnow limitrate

            pp(m, 1) = abs(CC_RT);
            if m == USE_POINTS
                m = 0;
                title([num2str(max(pp)),'mV'], 'FontSize', 70);
            end
        end
    end
end




% save aaaa

