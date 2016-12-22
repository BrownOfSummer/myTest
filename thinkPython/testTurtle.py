from swampy.TurtleWorld import *
world = TurtleWorld()
bob = Turtle()
print bob

#fd(bob, 100)
#lt(bob, 90)
#fd(bob, 100)
#lt(bob, 90)
#fd(bob, 100)
#lt(bob, 90)
#fd(bob, 100)
def square(t, length):
    for i in range(4):
        fd(t, length)
        lt(t, 90)
#square(bob, 100)

def polygon(t, length, n):
    angle = 360.0 / n;
    for i in range(n):
        fd(t, length)
        lt(t, angle)
#polygon(bob, 100, 6)

def circle(t, r):
    circumference = 2 * 3.14159265358 * r
    for i in range(360):
        lt(t, 1)
        fd(t, circumference / 360)
#bob.delay = 0.01
#circle(bob, 50)

def arc(t, r, angle):
    circumference = 2 * 3.14159265358 * r
    for i in range(angle):
        lt(t, 1)
        fd(t, circumference / 360)
bob.delay = 0.01
arc(bob, 50, 190)
wait_for_user()
