clc
clear
%% batch gradient descent
%% data set
X = cell(5,1);
X{1} = [1 0 3]';
X{2} = [1 1 3]';
X{3} = [1 2 3]';
X{4} = [1 3 2]';
X{5} = [1 4 4]';
y = [95.364 97.217205 75.195834 60.105519 49.342380]';
%% h(x) = a1*x1 + a2*x2 + a3*x3
n = length(X{1}); % n theta
m = 5; %n samples
theta = zeros(n,1);
alpha = 0.01;
epsilon = 0.0001;
max_iteration = 10000;
error1 = 0;
error0 = 0;
cnt = 0;
while(1)
    cnt = cnt + 1;
    for j = 1:n
        Sum = 0;
        for i = 1:m
            Sum = Sum + (y(i) - sum(theta.*X{i})) * X{i}(j); 
        end
        theta(j) = theta(j) + alpha * Sum;
    end
    error1 = 0;
    for i = 1:m
        error1 = error1 + (y(i) - sum(theta.*X{i}))^2;
    end
    if(abs(error1 - error0) < epsilon || cnt == max_iteration)
        break;
    else
        error0 = error1;
    end
end
disp(theta);
disp(cnt)
