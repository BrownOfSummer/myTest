%% test gradient_descent
%% train set
% each sample has 3 branch (x0, x1, x2)
x = cell(1,5);
x{1} = [1 0.0 3];
x{2} = [1 1.0 3];
x{3} = [1 2.0 3];
x{4} = [1 3.0 2];
x{5} = [1 4.0 4];

% the corresding output
y = [95.364 97.217205 75.195834 60.105519 49.342380];
%%
% iteration threshold
epsilon = 0.0001;

% learning rate
alpha = 0.01;
diff = [0 0];
max_itor = 1000;
error1 = 0;
error0 = 0;
cnt = 0;
m = length(x);
%% initial para
theta0 = 0;
theta1 = 0;
theta2 = 0;
%%
while(1)
    cnt = cnt + 1;
    for i=1:m
        % polyfit function: y = theta0 * x(1) + theta1*x(2) + theta2*x(3)
        % calc residual
        diff(1) = (theta0 + theta1 * x{i}(2) + theta2 * x{i}(3) - y(i) );
        % gradient = diff(1) * x{i}(j)
        theta0 = theta0 - alpha * diff(1) * x{i}(1);
        theta1 = theta1 - alpha * diff(1) * x{i}(2);
        theta2 = theta2 - alpha * diff(1) * x{i}(3);
    end
    error1 = 0;
    for j = 1:m
        error1 = error1 + ( y(i) - (theta0 + theta1 * x{i}(2) + theta2 * x{i}(3) ) )^2 / 2;
    end
    if( abs(error1 - error0) < epsilon )
        break;
    else
        error0 = error1;
    end
    %disp([theta0 theta1 theta2 error1])
end
disp([theta0 theta1 theta2]);
disp(cnt)








