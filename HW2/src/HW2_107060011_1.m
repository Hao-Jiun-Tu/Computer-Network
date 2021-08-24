%% Computer Network HW2-1

% Initialize variables
load('inputdata.mat')
Cx = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1]; % CRC(x)_32
Mx = packet; % Message
Tx = [Mx zeros(1,length(Cx)-1)]; % T(x) = x^k * M(x)
Rx = Tx; % is to operate bitwise xor with C(x)

for i = 1:length(Mx)
    if Rx(i)
        Rx(i:i+length(Cx)-1) = bitxor(Rx(i:i+length(Cx)-1), Cx);
    else 
        continue
    end
end

Remainder = Rx((length(Rx)-(length(Cx)-2)):length(Rx));
codepacket = [Tx(1:length(Mx)), bitxor(Tx(length(Mx)+1:length(Tx)), Remainder)];
