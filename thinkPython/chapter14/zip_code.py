
##Exercise 14.6
import urllib
"""
conn = urllib.urlopen('http://thinkpython.com/secret.html')
for line in conn:
    print line.strip()
"""

"""zip 02492 provides information about Needham MA, including population, longitude and latitude
Write a program that prompts the usr for a zip code and prints the name and population
of the corresponding town"""

zipcode = '02492'

url = 'http://uszip.com/zip/' + zipcode
conn = urllib.urlopen(url)

for line in conn.fp:
    line = line.strip()
    if 'Population' in line:
        print line
    if 'Longitude' in line:
        print line
    if 'Latitude' in line:
        print line

conn.close()
