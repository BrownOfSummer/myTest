import random

def make_histograms(s):
    """Make a map from letters to number of times they appear in s.
    s: string
    Returns: map from letter to frequency
    """
    hist = {}
    for x in s:
        hist[x] = hist.get(x, 0) + 1
    return hist

def most_frequency(s):
    """Sort the letters in s in reverse order of frequency.
    s: string
    Returns: list of letters
    """
    hist = make_histograms(s)
    t = []
    """some_dict.items -> [('key',value),...]"""
    for x, freq in hist.items():
        t.append( (freq, x) )
    
    t.sort(reverse=True)
    res = []
    for freq, x in t:
         res.append(x)
    return res

def read_file(filename):
    """Returns the contents of file as a string"""
    return open(filename).read()

if __name__=='__main__':
    s = read_file('words.txt')
    t = most_frequency(s)
    for x in t:
        print(x)
