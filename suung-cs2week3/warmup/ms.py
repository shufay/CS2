'''
'gameboard' is the 2D string matrix representing the game board. It is a 
2D numpy array. The function 'reveal' takes as arguments the 'click' x 
and y positions and reveals the board. 
To run, cd into the same directory and type 'py ms.py <x> <y>' into the 
terminal. <x> and <y> are the coordinates to be revealed.
In the worst case scenario, the whole board is empty, so the function is
called n times where n is the number of elements in the board. The four 
for loops in the function do not depend on the input size, so the time
complexity is O(n). 
The space complexity is O(1) because no input values are stored.  
'''

import numpy as np
import sys

gameboard = np.array([['E', 'E', 'E', 'E', 'E'],
                        ['E', 'E', 'M', 'E', 'E'],
                        ['E', 'E', 'E', 'E', 'E'],
                        ['E', 'E', 'E', 'E', 'E']], dtype=str)

x_max, y_max = gameboard.shape

def reveal(x, y):
    if gameboard[x][y] == 'M':
        gameboard[x][y] = 'X'

    elif gameboard[x][y] == 'E':
        mines = 0

        for i in range(x-1, x+2):
            for j in range(y-1, y+2):
                if i < 0 or i > x_max - 1:
                    continue

                if j < 0 or j > y_max - 1:
                    continue

                if gameboard[i][j] == 'M':
                    mines += 1

        if mines > 0:
            gameboard[x][y] = str(mines)

        else:
            gameboard[x][y] = 'B'

            for i in range(x-1, x+2):
                for j in range(y-1, y+2):
                    if i < 0 or i > x_max - 1:
                        continue

                    if j < 0 or j > y_max - 1:
                        continue

                    if i == x and j == y:
                        continue
            
                    reveal(i, j)

    return gameboard

if len(sys.argv) != 3:
    usage = 'Usage: py ms.py <x> <y>'
    print(usage)

else:
    print('ORIGINAL\n')
    print(gameboard)
    print('\nREVEALED\n')
    print(reveal(int(sys.argv[1]), int(sys.argv[2])))


