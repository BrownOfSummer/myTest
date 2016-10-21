%% multi_leastSquart
%%
load data.txt
x = data(:,1);
y = data(:,2);
k = 3;
X = ones(length(x), k);
for i=1:length(x)
    for j=2:k
        X(i,j) = x(i)^(j-1);
    end
end

A = inv(X'*X)*X'*y;
disp(A)
p = polyfit(x,y,2);
plot(x,y,'r.');
hold on
plot(x, polyval(p,x),'g')
