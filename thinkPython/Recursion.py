from swampy.TurtleWorld import *
#print math.pi
def countdown(n):
    if n <= 0:
        print 'Blastoff'
    else:
        print n
        countdown(n-1)
#countdown(3)

def print_n(s, n):
    if n <= 0:
        return
    print s
    print_n(s, n-1)

#N = raw_input('Intput an integer:...\n')
#n = int(N)
#print_n('hello',n)
def factorial(n):
    """Calc the n!"""
    if n == 0:
        return 1
    else:
        recurse = factorial(n - 1)
        result = n * recurse
        return result


def draw(t, length, n):
    if n == 0:
        return
    angle = 50
    fd(t, length * n)
    lt(t, angle)
    draw(t, length, n - 1)
    rt(t, 2 * angle)
    draw(t, length, n - 1)
    lt(t, angle)
    bk(t, length * n)

def koch(t, n):
    """Draw a koch curve with length n."""
    if n < 3:
        fd(t, n)
        return
    m = n / 3.0
    koch(t, m)
    lt(t, 60)
    koch(t, m)
    rt(t, 120)
    koch(t, m)
    lt(t, 60)
    koch(t, m)

def snowflake(t, n):
    """Draws a snowflake (a triangle with a koch curve each side)"""
    for i in range(3):
        koch(t, n)
        rt(t, 120)
world = TurtleWorld()
bob = Turtle()
print bob
bob.delay = 0.01
bob.x = -150
bob.y = 90
bob.redraw()
snowflake(bob, 300)
#draw(bob, 10, 3)
#koch(bob, 200)
world.mainloop()
wait_for_user()
