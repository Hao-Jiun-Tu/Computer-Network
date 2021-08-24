%% Computer Network Homework 3

load('network_A.mat');

% Initialize Parameters
edge = zeros(100,100);
tree = zeros(100,100);
 
for i = 1:100
    for j = i+1:100
        if A(i,j)  % Store graph edges to Edges vecter
            edge(i,j) = A(i,j);
            edge(j,i) = A(j,i);
        else       % Set non-touching edges to INF
            edge(i,j) = Inf;  
            edge(j,i) = Inf;
        end
    end
end

dis = Inf(1,100);          % to store distance from root to the others            
for i = 1:100             
    dis(1,i) = edge(1,i);  % to find length 1 of distance from root to the others
    if edge(1,i) == 1
        tree(1,i) = 1;     % update the spanning tree
        tree(i,1) = 1;
    end
end

visited = zeros(1,100);    % to check if vertices have been traversed
visited(1) = true;

% Dijkstra algorithm
for i = 1:100
    min = Inf;
    for j = 2:100  % check the minimum distance from root in vertices ID order
        if ~visited(j) && dis(1,j) < min  % to check the unique spanning tree
            min = dis(1,j);
            u = j;
        end
    end
    visited(u) = true;
    for v = 2:100
        if edge(u,v) < Inf
            if dis(1,v) > dis(1,u) + edge(u,v)
                dis(1,v) = dis(1,u) + edge(u,v); % update the distance vector
                tree(u,v) = 1;                   % update the spanning tree
                tree(v,u) = 1;
            end
        end
    end
end
 
