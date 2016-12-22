import math
class Point(object):
    """Represents a point in 2-D space"""

blank = Point()
blank.x = 3.0
blank.y = 4.0

x = blank.x
print x, blank.y
print '(%g, %g)' % (blank.x, blank.y)

def distane_between_points(p1, p2):
    """p1, p2 are alias of true class of point"""
    distance = math.sqrt( (p1.x - p2.x)**2 + (p1.y - p2.y)**2  )
    return distance

"""class contains another class"""
class Rectangle(object):
    """Represents a rectangle.
    attributes: width, height, corner
    """
box = Rectangle()
box.width = 100.0
box.height = 200.0
box.corner = Point()
box.corner.x = 0.0
box.corner.y = 0.0

"""Instances as return values"""
def find_center(rect):
    p = Point()
    p.x = rect.corner.x + rect.width / 2.0
    p.y = rect.corner.y + rect.height / 2.0
    return p
center = find_center(box)
print "center.x = %g, center.y = %g" %(center.x, center.y)

"""Copying a class
Aliasing can make a program difficult to read because changes in one place
might have unexpected effects in another place.
copying an object is often an alternative to aliasing.
"""
import copy
p1 = Point()
p1.x = 3.0
p1.y = 4.0
p2 = copy.copy(p1)
print "p2.x = %g, p2.y = %g" %(p2.x, p2.y)
print "p1 is p2?",p1 is p2 #indicates that p1 p2 are not the same object
print "p1 == p2?",p1 == p2 # == has same function as is, in object

"""Shallow copy: copy the object, but not the embeded objects"""
box2 = copy.copy(box)
print "box2 is box ?", box2 is box
print "box2.corner is box.corner ?",box2.corner is box.corner
box3 = copy.deepcopy(box)
print "box3.corner is box.corner ?",box3.corner is box.corner

print "The type of the object is: ",type(p1)
print "Does p1 has attribute x ?",hasattr(p1, 'x')
print "Dose p1 has attribute z ?",hasattr(p1, 'z')
