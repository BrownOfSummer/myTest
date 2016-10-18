%% test 最小二乘法
%%
load data.txt
X = data(:,1);
Y = data(:,2);
n = length(X);
alpha = ( n*sum( X.*Y ) - sum(X)*sum(Y) ) / ( n*sum(X.^2) - (sum(X))^2 );
beta = ( sum(X.^2)*sum(Y) - sum(X)*sum(X.*Y) ) / (n*sum(X.^2) - (sum(X))^2);
%a = polyfit(data(:,1), data(:,2), 1);