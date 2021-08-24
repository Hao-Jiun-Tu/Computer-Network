%% Computer Network HW2-2

% Initialize variables
load('inputdata.mat')
load('107060011.mat')

Cx = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1]; % CRC(x)_32
Mx = packet; % Message
Tx = [Mx zeros(1,length(Cx)-1)]; % T(x) = x^k * M(x)
Rx = codepacket; % is to operate bitwise xor with C(x)

% "Remainder Lookup Table" for codepacket changing for 1-bit
% A1/CRC32 = x ...B1 and A2/CRC32 = x ...B2
% if ~((B1+B2)%CRC32) ==> ((A1+A2)%CRC32)=1
Rx_table = zeros(length(codepacket), 32); 

for i = 1:length(codepacket)
    Rx = codepacket;
    Rx(i) = ~Rx(i);
    for j = 1:length(Mx)
        if Rx(j)
            Rx(j:j+length(Cx)-1) = bitxor(Rx(j:j+length(Cx)-1), Cx);
        else 
            continue
        end
    end
    Remainder = Rx((length(Rx)-(length(Cx)-2)):length(Rx));
    Rx_table(i,:) = Remainder;
end

zero_32 = zeros(1,32);
error = zeros(1,length(codepacket));
flag = false;

for i = 1:(12000-6)
    for j = i+2:(12000-4)
        for k = j+2:6000 %(12000-2)
            for h = k+2:6000 %(12000)
                E1 = Rx_table(i,:);
                E2 = Rx_table(j,:);
                E3 = Rx_table(k,:);
                E4 = Rx_table(h,:);
                if(xor(xor(E1,E2),xor(E3,E4)) == zero_32)
                    flag = true;
                    if flag
                        error(i) = 1;
                        error(j) = 1;
                        error(k) = 1;
                        error(h) = 1;
                        return
                    end
                end
            end
        end
    end
end
