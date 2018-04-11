'''
To run, type 'python warmup.py <x>' in the terminal. <x> is the 
integer to be checked.

In the worst case scenario, each number in 'x' would have to be 
checked individually, hence the time complexity is O(n).

The space complexity is O(n) since the variable 'num' stores 'x'
as a string of integers. 
'''

import string, sys

def check(x):
    '''
    Takes a number 'x' as argument and returns true if there is a 
    string that maps to 'x'. Otherwise, returns false.
    '''
    num = str(x)
    i = 0

    while i < len(num):
        if i+1 < len(num):
            next = num[i:i+2]

            if int(next) <= 26:
                if next[0] == '0':
                    return False
        
                i += 2
                continue
        
        next = num[i]

        if int(next) == 0:
            return False

        i += 1
        
    return True

usage = 'python warmup.py <x>'

if len(sys.argv) != 2:
    print(usage)

else:
    print(check(int(sys.argv[1])))

