import math
#from math import *
def print_lyrics():
    print "I'm a handsome boy !"

def repeat_lyrics():
    print_lyrics()
    print_lyrics()

repeat_lyrics()

def print_twice(bruce):
    print bruce
    print bruce

var = 'thanks god'
print_twice(math.pi)
print_twice(var)

def do_twice(f,arg1):
    f(arg1)
    f(arg1)
do_twice(print_twice, 'ahaha')
