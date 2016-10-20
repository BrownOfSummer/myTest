# _*_ coding: utf-8 _*_

# training set
# each sample (x0,x1,x2)
x = [(1, 0., 3), (1, 1., 3), (1, 2., 3), (1, 3., 2), (1, 4., 4)]
# y[i] out result
y = [95.364, 97.217205, 75.195834, 60.105519, 49.342380]

# iteration threshold, while diff between two iteration, stop
epsilon = 0.0001

# learning rate
alpha = 0.01
diff = [0, 0]
max_itor = 1000
error1 = 0
error0 = 0
cnt = 0
m = len(x)


# initial para
theta0 = 0
theta1 = 0
theta2 = 0

while True:
    cnt += 1

    # calc para iteration
    for i in range(m):
        # polyfit function: y = theta0 * x[0] + theta1 * x[1] +theta2 * x[2]
        # 
        diff[0] = (theta0 + theta1 * x[i][1] + theta2 * x[i][2]) - y[i]

        # gradient = diff[0] * x[i][j]
        theta0 -= alpha * diff[0] * x[i][0]
        theta1 -= alpha * diff[0] * x[i][1]
        theta2 -= alpha * diff[0] * x[i][2]

    # calc loss function
    error1 = 0
    for lp in range(len(x)):
        error1 += (y[i]-(theta0 + theta1 * x[i][1] + theta2 * x[i][2]))**2

    if abs(error1-error0) < epsilon:
        break
    else:
        error0 = error1

    #print ' theta0 : %f, theta1 : %f, theta2 : %f, error1 : %f' % (theta0, theta1, theta2, error1)
print 'Done: theta0 : %f, theta1 : %f, theta2 : %f' % (theta0, theta1, theta2)
print 'iteration times: %d' % cnt
