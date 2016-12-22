
class Time(object):
    def __init__(self, seconds = 0):
        self.seconds = seconds

    def __str__(self):
        minutes, second = divmod(self.seconds, 60)
        hour, minute = divmod(minutes, 60)
        return '%.2d:%.2d:%.2d' % (hour, minute, second)

    def print_time(self):
        print str(self)

    def time_to_int(self):
        return self.seconds

    def is_after(self, other):
        return self.seconds > other.seconds

    def __add__(self, other):
        if isinstance(other, Time):
            return self.add_time(other)
        else:
            return self.increment(other)

    def __radd__(self, other):
        return self.__add__(other)

    def add_time(self, other):
        assert self.is_valid() and other.is_valid()
        seconds = self.time_to_int() + other.time_to_int()
        return int_to_time(seconds)

    def increment(self, seconds):
        seconds += self.time_to_int()
        return int_to_time(seconds)

    def is_valid(self):
        minutes, second = divmod(self.seconds, 60)
        hour, minute = divmod(minutes, 60)
        if hour < 0 or minute < 0 or second < 0:
            return False
        if minute >= 60 or second >= 60:
            return False
        return True

def int_to_time(seconds):
    time = Time(seconds)
    return time

def second_from_zero(hour = 0, minute = 0, second = 0):
    return hour * 3600 + minute * 60 + second

def main():
    start = Time( second_from_zero(9, 45, 00) )
    start.print_time()

    end = start.increment(1337)
    end.print_time()

    print 'Is end after start? ',
    print end.is_after(start)

    print 'Using __str__'
    print start, end

    start = Time( second_from_zero(9, 45) )
    duration = Time( second_from_zero(1, 35) )
    print start + duration
    print start + 1337
    print 1337 + start

    print 'Example of polymorphism'
    t1 = Time( second_from_zero(7, 43) )
    t2 = Time( second_from_zero(7, 41) )
    t3 = Time( second_from_zero(7, 37) )

    total = sum([t1, t2, t3])
    print total

if __name__=='__main__':
    main()
