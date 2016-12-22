clc
clear 
close all

load('Q2x');
load('Q2y');

X = Q2x;
Y = Q2y;
 
X=[ones(size(X,1),1) X];  %[1; X]
m=size(X,1); %100
n=size(X,2); %2
r=0.8;
 
figure;
hold on;
plot(X(:,2),Y,'.b');

xdelt = (max(X(:,2)) - min(X(:,2)))/100;
% test_x=min(X(:,2)):.1:max(X(:,2));
test_x=min(X(:,2)):xdelt:max(X(:,2))-xdelt; 
result_y=zeros(size(test_x,2),1);
 
theta=inv(X'*X)*(X'*Y); % calc inv matrix to get normal equation sulution
result_y=theta(2)*test_x+theta(1); %y = ax + b , test_x, result_y is human generated points for plot
plot(test_x,result_y,'b');
 
rs=[.1 .3 .8 2 10];
colors=['r' 'g' 'm' 'y' 'k'];
 
for l=1:size(rs,2)
    r=rs(l);
    for k=1:1:size(test_x,2)
        w=zeros(m,m);
        for i=1:1:m        
            w(i,i)=exp(-((test_x(k)-X(i,2))^2)/(2*r^2));
%             ww(l,i) = w(i,i);
        end
        %theta=(X'*w*X)\(X'*w*Y);
        theta = inv(X'*w*X)*X'*w*Y;
        result_y(k)=theta(1)+theta(2)*test_x(k);
    end
    plot(test_x,result_y,colors(l));
end
 
legend('trainingdata','linear','r=.1','r=.3','r=.8,','r=2','r=10');

figure
x = 3;
for l = 1:5
% for l = 1:size(rs,2)
    r = rs(l);
    for i = 1:m
        ww(l,i) = exp(-(x-X(i,2))^2/(2*r^2)); 
    end
%     length(test_x)
%     length(ww)
    stem(Q2x,ww(l,:),colors(l));
    hold on
end
