"""A method of object orient"""
"""I think the most different is that, suppose the first argument is class its self"""

def int_to_time(seconds):
    time = Time()
    minutes, time.second = divmod(seconds, 60)
    time.hour, time.minute = divmod(minutes, 60)
    return time

def print_attributes(obj):
    for attr in obj.__dict__:
        print attr, getattr(obj, attr)

class Time(object):
    def print_time(self):
        print "%.2d:%.2d:%.2d" % (self.hour, self.minute, self.second)

    def time_to_int(self):
        minutes = self.hour * 60 + self.minute
        seconds = minutes * 60 + self.second
        return seconds

    def increment(self, seconds):
        seconds += self.time_to_int()
        return int_to_time(seconds)

    def is_after(self, other):
        return self.time_to_int() > other.time_to_int()

    def add_time(self, other):
        seconds = self.time_to_int() + other.time_to_int()
        return int_to_time(seconds)

    def __init__(self, hour = 0, minute = 0, second = 0):
        self.hour = hour
        self.minute = minute
        self.second = second

    def __str__(self):
        return "%.2d:%.2d:%.2d" % (self.hour, self.minute, self.second)

    def __add__(self, other):
        if isinstance(other, Time):
            return self.add_time( other )
        else:
            return self.increment( other )

    def __radd__(self, other):
        return self.__add__(other)

    def __cmp__(self, other):
        t1 = self.hour, self.minute, self.second
        t2 = other.hour, other.minute, other.second
        return cmp(t1, t2) # t1 > t2 positive; t1 < t2 -> negative; t1 = t2 -> 0




start = Time()
start.hour = 9
start.minute = 45
start.second = 0

Time.print_time(start)
start.print_time()
print Time.time_to_int(start)
print start.time_to_int()

end = start.increment(1337)
end.print_time()
end = Time.increment(start, 1337)
Time.print_time(end)

other = Time()
other.hour = 8
other.minute = 53
other.second = 2
print end.is_after(other)

time2 = Time(10, 54)
time2.print_time()
print time2

print 'start + time2 use +:', start + time2
print 'start + 1700s use +:', start + 1700
print '1700 + start', 1700 + start

"""Becuase we defined the instance function add, we can call sum to add several Time instance as list"""
t1 = Time(7, 41)
t2 = Time(7, 43, 1)
t3 = Time(7, 37)
total = sum([t1, t2, t3])
total.print_time()
print "t1 + t2 + t3 = ", total
print_attributes(t1)
