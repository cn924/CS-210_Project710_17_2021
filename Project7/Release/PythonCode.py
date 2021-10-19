import re
import string
import collections

#Function that will count frequency
def ItemCount():
    # Use collections module to store the values as a dictionary
    with open('input.txt') as fp:
    #Counts frequency 
        counts = collections.Counter(line.strip() for line in fp)

    #key-value pairs print string item and digit amount sold
    for key in counts:
        print('%s %d' % (key, counts[key]))

def NameItemCount(v):
    # Capitalizes first letter 
    v = v.capitalize()

    # Open file with built-in count function
    with open('input.txt') as fp:
        data = fp.read()
        occurences = data.count(v)
        return occurences

def ItemCountWriter():
    # Open both the read and write to Frequency.DAT
    with open('frequency.dat', "w") as wp: 
    
        # Storing values in dictionary
        with open('input.txt') as fp:
            counts = collections.Counter(line.strip() for line in fp)

        # Write the item and counts to the output file
        for key in counts:
            wp.write('%s %d\n' % (key, counts[key]))

    #Close Success Message
    if wp.closed:
        print('Success')