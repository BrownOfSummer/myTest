#filenames and path
import os
cwd = os.getcwd()
print cwd
print "the absolute path of words.txt is: ",os.path.abspath('../words.txt')
print "Is words.txt exist ? ", os.path.exists('../words.txt')
print "Is words.txt is a dir ?", os.path.isdir('../words.txt')
print "Is words.txt is a file ?", os.path.isfile('../words.txt')

def walk(dirname):
    """Walks through a directory, prints the name of all the files, and calls itself recursively on all directory"""
    for name in os.listdir(dirname):
        """os.path.join takes a directory and a file name and joins them into a complete path"""
        path = os.path.join(dirname, name)

        if os.path.isfile(path):
            print path
        else:
            walk(path)
#walk('../')

"""Most databases are organized like a dictionary, map leys to values"""

import anydbm
"""c means that the database should be created if it doesn't already exist"""
db = anydbm.open('captions.db', 'c')
db['cleese.png'] = 'Photo of Jone Cleese.'
print db['cleese.png']
db['cleese.png'] = 'Photo of Jone Cleese doing a silly walk.'
print db['cleese.png']
db.close()

import pickle
t1 = [1, 2, 3]
s = pickle.dumps(t1)
print s
t2 = pickle.loads(s)
print t2
print "t1 == t2 ? -> ", t1 == t2
print "t1 is t2 ? -> ", t1 is t2


