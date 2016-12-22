import numpy as np
bestloss = float("inf") # Python assigns the hightest possible float val
for num in xrange(1000):
    W = np.random.randn(10, 3073) * 0.0001
    loss = L(X_train, Y_train, W)
    if loss < bestloss:
        bestloss = loss
        bestW = W;
    print 'in attempt %d the loss was %f, best %f' %(num, loss, bestloss)

W = np.random.randn(10, 3073) * 0.001
bestloss = float("inf")
for i in xrange(1000):
    step_size = 0.0001
    Wtry = W + np.random.randn(10, 3073) * step_size
    loss = L(X_train, Y_train, W)
    if loss < bestloss:
        W = Wtry
        bestloss = loss
    print 'iter %d loss is %f' % (i, bestloss)


def eval_numerical_gradient(f, x):
    """gradient at x of f
    f does have 1 para
    x is the point where to calc the gradient"""
    fx = f(x) # the value of original
    grad = np.zeros(x.shape)
    h = 0.00001

    it = np.nditer(x, flags=['multi_index'], op_flags=['readwrite'])
    while not it.finished:
        # calc the value at x+h
        ix = it.multi_index
        old_value = x[ix]
        x[ix] = old_value + h
        fxh = f(x) #calc f(x+h)
        x[ix] = old_value

        # calc various gradient
        grad[ix] = (fxh - fx) / h
        it.iternext()
    return grad

def CIFAR10_loss_fun(W):
    return L(X_train, Y_train, W)
W = np.random.randn(10, 3073) * 0.001
df = eval_numerical_gradient(CIFAR10_loss_fun, W) # get the gradient

loss_original = CIFAR10_loss_fun(W) # original loss
print 'original loss: %f' % (loss_original, )

# the result of diverse steps
for step_size_log in [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1]:
    step_size = 10 ** step_size_log
    W_new = W - step_size * df
    loss_new = CIFAR10_loss_fun(W_new)
    print 'for step size %f new loss: %f' % (step_size, loss_new)

# ordinary gradient desent
while True:
    weights_grad = evaluate_gradient(loss_fun, data, weights)
    weights += -step_size * weights_grad

# Mini-batch gradient descent
while True:
    data_batch = sample_training_data(data, 256) # 256 samples
    weights_grad = evaluate_gradient(loss_fun, data_batch, weights)
    weights += - step_size * weights_grad


"""f(x,y,z) = (x + y) * z"""
"""q = x + y, f = qz"""
x = -2; y = 5; z = -4
# forward 
q = x + y # q = 3
f = q * z # f = -12
# backward
# first return to f = q * z
dfdz = q # df/dz = q, so the gradient about z is 3
dfdq = z # df/dq = z, so the gradient about q is -4

# now backward to q = x + y
dfdx = 1.0 * dfdq # dq/dx = 1
dfdy = 1.0 * dfdq # dq/dy = 1
# we get the varience's gradient = [dfdx, dfdy, dfdz]



w = [2, -3, -3]
x = [-1, -2]
# forward
dot = w[0]*x[0] + w[1]*x[1] + w[2]
f = 1.0 / (1 + math.exp(-dot)) # sigmoid function

# backward 
ddot = (1 -f) * f
dx = [ w[0] * ddot, w[1] * ddot ] # backward to x
dw = [ x[0] * ddot, x[1] * ddot, 1.0 * ddot ]


f(x, y) = ( x + sig(y) ) / ( sig(x) + (x + y)**2 )

x = 3; y = -4
#forward
sigy = 1.0 / (1 + math.exp(-y)) #sigmoid in upper
num = x + sigy
sigx = 1.0 / (1 + math.exp(-x)) #sigmoid downer
xpy = x + y
xpysqr = xpy**2
den = sigx + xpysqr
invden = 1.0 / den
f = num * invden

# backward f = num * invden
dnum = invden
dinvden = num
# backward invden = 1.0 / den
dden = -1.0*/(den**2) * dinvden
# backward den = sigx + xpysqr
dsigx = dden
dspysqr = dden
dxpy = (2*xpy) * dxpysqr
# backward xpy = x + y
dx = dxpy
dy = dxpy
# backward sigx = 1.0 / (1 + math.exp(-x))
dx += ((1 - sigx) * sigx) * dsigx

