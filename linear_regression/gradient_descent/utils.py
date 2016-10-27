
def stochastic_gradient(X, Y, m,alpha, epsilon, max_itor, theta):
    error1 = 0.0
    error0 = 0.0
    cnt = 0
    tmp = 0.0
    while True:
        theta0 = theta[0]
        theta1 = theta[1]
        cnt = cnt + 1
        for i in range(m):
            theta[0] -= alpha * (theta[0] + theta[1] * X[i] - Y[i] ) / m
            theta[1] -= alpha * (theta[0] + theta[1] * X[i] - Y[i]) * X[i] / m

        error1 = 0.0
        for i in range(m):
            diff = theta0 + theta1 * X[i] - theta[0] - theta[1] * X[i]
            error1 += pow(diff, 2)

        if( abs(error1 - error0) <= epsilon or cnt >= max_itor ):
            break
        else:
            error0 = error1
        print("theta[0] = %f, theta[1] = %f, error = %f"%(theta[0],theta[1], error1 - error0))
    return cnt

def batch_gradient(X, Y, m, alpha, epsilon, max_itor, theta):
    error0 = 0.0
    cnt = 0
    while True:
        cnt = cnt + 1
        theta0 = theta[0]
        theta1 = theta[1]
        Sum = 0
        Sum0 = 0
        for i in range(m):
            diff = Y[i] - (theta[0] + theta[1] * X[i])
            Sum += 1.0 * diff * X[i] / m
            Sum0 += 1.0 * diff / m

        theta[0] += alpha * Sum0
        theta[1] += alpha * Sum

        error1 = 0.0
        for i in range(m):
            diff = theta0 + theta1 * X[i] - theta[0] - theta[1] * X[i]
            error1 += pow( diff, 2 )

        if( abs(error1 -error0) <= epsilon or cnt >= max_itor ):
            break
        else:
            error0 = error1

        print("theta[0] = %f, theta[1] = %f, error = %f"%(theta[0], theta[1], error1 - error0))
    return cnt


X = list()
Y = list()
for i in range(1000):
    X.append(i)
    Y.append(5.7*i + 9.0)
epsilon = 0.0001
alpha = 0.000001
theta = [0, 0]

cnt = batch_gradient(X, Y, 1000, alpha, epsilon, 1000, theta)
#cnt = stochastic_gradient(X, Y, 1000, alpha, epsilon, 1000, theta)
print theta, cnt
















