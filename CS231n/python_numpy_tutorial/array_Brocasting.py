import numpy as np
"""Broadcasting"""

# We will add the vector v to each row of the matrix x,
# storing the result in the matrix y
x = np.array( [ [1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12] ] )
v = np.array([1, 0, 1])
y = np.empty_like(x) #create an empty matrix with the same shape as x
for i in range(4):
    y[i, :] = x[i, :] + v
print "x = "
print x
print "y = "
print y

vv = np.tile(v, (4 ,1))
print "vv = ", vv
vv = np.tile(v, (2, 2))
print "vv = ", vv

"""Numpy broadcasting allows us to perform this computation 
without actually creating multiple copies of v"""
print "x + v ="
print x + v

"""Here are some applications of broadcasting:"""
v = np.array([1, 2, 3])
w = np.array([4, 5])
print np.reshape(v, (3, 1))
print np.reshape(v, (3, 1)) * w
