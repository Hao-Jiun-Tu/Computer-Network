%% Computer Network Homework 4

load('network_A.mat');

% Initialize Parameters
edge = zeros(100,100);
 
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

d = edge;  % to store distance from root to the others            

visited = zeros(100,100);    % to check if vertices have been traversed
for i = 1:100
    visited(i,i) = 1;
end

% Dijkstra algorithm to run all nodes
for node = 1:100
    for i = 1:100
        min = Inf;
        for j = 1:100  % check the minimum distance from root in vertices ID order
            if ~visited(node,j) && d(node,j) < min  % to check the unique spanning tree
                min = d(node,j);
                u = j;
            end
        end
        visited(node,u) = true;
        for v = 1:100
            if edge(u,v) < Inf
                if d(node,v) > d(node,u) + edge(u,v)
                    d(node,v) = d(node,u) + edge(u,v); % update the distance vector
                end
            end
        end
    end
end

