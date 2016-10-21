# _*_ coding: utf-8 _*_

# training set
# each sample (x0, x1, x2)
x = [(1, 0., 3), (1, 1., 3), (1, 2., 3), (1, 3., 2), (1, 4., 4)]
# y[i] out results
y = [95.364, 97.217205, 75.195834, 60.105519, 49.342380]

# 
# iteration threshold, while loss between to iteration < threshold, stop
epsilon = 0.0001

# learning rate
alpha = 0.01
diff = [0, 0]
max_iteration = 10000
error1 = 0
error0 = 0
cnt = 0
# num of samples
m = len(x) 

# initial parameters, weights
theta = [0, 0, 0]
n = len(theta)

while True:
    cnt += 1
    for j in range(n):
        Sum = 0;
        for i in range(m):
            hx = theta[0] * x[i][0] + theta[1] * x[i][1] + theta[2] * x[i][2];
            Sum += ( y[i] - hx ) * x[i][j];
        theta[j] += alpha * Sum;
    error1 = 0
    for i in range(m):
        hx = theta[0] * x[i][0] + theta[1] * x[i][1] + theta[2] * x[i][2];
        error1 += ( y[i] - hx )**2

    if( abs(error1 - error0) < epsilon or cnt == max_iteration  ):
        break;
    else:
        error0 = error1;
    
    #print ' theta0 : %f, theta1 : %f, theta2 : %f, error1 : %f' % (theta[0], theta[1], theta[2], error1)
print 'Done: theta0 : %f, theta1 : %f, theta2 : %f' % (theta[0], theta[1], theta[2])
print 'iteration times: %d' % cnt
