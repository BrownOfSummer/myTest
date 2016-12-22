
"""Exercises 17.13"""

class Kangaroo(object):
    def __init__(self):
        self.pouch_contents = list()

    def put_int_pouch(self, obj):
        self.pouch_contents.append(obj)

    def __str__(self):
        return str(self.pouch_contents)


kanga = Kangaroo()
roo = Kangaroo()
kanga.put_int_pouch(roo)
print kanga
