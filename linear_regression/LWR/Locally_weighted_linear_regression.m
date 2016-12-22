clear ;
close all;
x = [1:50].';
y = [4554 3014 2171 1891 1593 1532 1416 1326 1297 1266 ...
	1248 1052 951 936 918 797 743 665 662 652 ...
	629 609 596 590 582 547 486 471 462 435 ...
	424 403 400 386 386 384 384 383 370 365 ...
	360 358 354 347 320 319 318 311 307 290 ].';

m = length(y); % store the number of training examples
x = [ ones(m,1) x]; % Add a column of ones to x
n = size(x,2); % number of features
theta_vec = inv(x'*x)*x'*y;
tau = [1 10 25 ];
y_est = zeros(length(tau),length(x));
for kk = 1:length(tau)
	for ii = 1:length(x);
		w_ii = exp(-(x(ii,2) - x(:,2)).^2./(2*tau(kk)^2));
		W = diag(w_ii);
		theta_vec = inv(x'*W*x)*x'*W*y;
		y_est(kk, ii) = x(ii,:)*theta_vec;
	end
end

figure;
plot(x(:,2),y,'ks-'); hold on
plot(x(:,2),y_est(1,:),'bp-');
plot(x(:,2),y_est(2,:),'rx-');
plot(x(:,2),y_est(3,:),'go-');
legend('measured', 'predicted, tau=1', 'predicted, tau=10','predicted, tau=25');
grid on;
xlabel('Page index, x');
ylabel('Page views, y');
title('Measured and predicted page views with weighted least squares');