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

AD_INT = zeros(4, 1);
A = zeros(5, 1);
B = zeros(3, 1);
res = 0;
CC = 45; %unit: mV

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
	
    if mod(i,5) == 0
        i = 0;
        AD_INT2 = sort(AD_INT, 1, 'ascend');
        AD_INT2 = AD_INT2(2:end - 1);
        j = j + 1;
        A(j, 1) = sum(AD_INT2) / 2;
        if mod(j,5) == 0
            j = 0;
            k = k + 1;
            A2 = sort(A, 1, 'ascend');
            B(k, 1) = A2(end) - A2(1);
            if mod(k,3) == 0
                k = 0
                if B(3) >= (B(1) + CC*4096/1250) & B(2) >= (B(1) + CC*4096/1250)
                    res = 1
                else
                    res = 0
                end
                  title([num2str(res),'人'], 'FontSize', 70)
            end
        end
    else
        AD_INT(i, 1) = data;
    end
	
end


   
    
% save aaaa

