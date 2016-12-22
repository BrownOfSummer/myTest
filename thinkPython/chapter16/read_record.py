
class Time(object):
    """Represent the time of day.
    attributes: hour, minute, second
    """

def print_time(t):
    print '%.2d:%.2d%.2d' % (t.hour, t.minute, t.second)

def is_after(t1, t2):
    return (t1.hour, t1.minute, t1.second) > (t2.hour, t2.minute, t2.second)

def increment1(time, seconds):
    time.second += seconds
    time.minute += time.second / 60
    time.hour += time.minute / 60

    time.second %= 60
    time.minute %=60
    time.hour %= 24

def increment2(time, seconds):
    # Converts total to seconds, then back to a readable format
    time_in_seconds = time.hour*3600 + time.minute*60 + time.second + seconds
    (time.minute, time.second) = divmod(time_in_seconds, 60)
    (time.hour, time.minute) = divmod(time.minute, 60)

def time_to_int(time):
    minutes = time.hour * 60 + time.minute
    seconds = minutes * 60 + time.second
    return seconds

def int_to_time(seconds):
    time = Time()
    minutes, time.second = divmod(seconds, 60)
    time.hour, time.minute = divmod(minutes, 60)
    return time
# test method: time_to_int( int_to_time(x) ) == x , for a lot of numbers

def increment3(time, seconds):
    time = int_to_time( time_to_int(time) + seconds )
time = Time()
time.hour = 11
time.minute = 59
time.second = 30


