#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include "grid.hpp"
using namespace std;

/*
 * @brief Constructs a Grid object.
 */

Grid::Grid() {}

/*
 * @brief Constructs the game board by taking in a filename that
 * stores the occupancy data and populates the grid.
 *
 * @param filename the filename with occupancy data.
 *
 * @return True if file could not be opened. False otherwise. 
 */

bool Grid::loadBoard(string filename)
{
    string line;
    int x = 0;
    ifstream file (filename);
    
    if (file.is_open()) // Check if file could be opened.
    {
        while (getline(file, line))
        {
            for (int y = 0; y < 9; y++)
            {
                // Load file contents into grid. 'grid' is the grid that will
                // be updated.
                grid[x][y] = line[y]; 
            }

                x++;
        }

        for (int i = 0; i < 9; i++) // 
        {
            for (int j = 0; j < 9; j++)
            {
                // Copy contents of 'grid' to 'grid_o'. 'grid_o' stores the 
                // original configuration of the board.
                grid_o[i][j] = grid[i][j];
            }
        }

        file.close();
        return 0;
    }

    else
    {
        cout << "ERROR: invalid file" << endl;
        return 1;
    }
}

/*
 * @brief Displays the board in the terminal.
 */

void Grid::display()
{
    for (int x = 0; x < 9; x++)
    {
        if (x % 3 == 0)
        {
            cout << "-------------------------" << endl;
        }   
        
        for (int y = 0; y < 9; y++)
        {        
            if (y % 3 == 0)
            {
                cout << "| ";   
            }  
            
            cout << grid[x][y] << ' ';
        }

        cout << "|" << endl;
    }
    
    cout << "-------------------------" << endl;
}

/*
 * @brief Checks to see if the board is full.
 *
 * @return True if board is complete. False otherwise.
 */

bool Grid::isComplete()
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            // If there remains an empty grid, sudoku is incomplete.
            if (grid[x][y] == ' ') 
            {
                return 0;
            }
        }        
    }
    
    return 1;
}

/*
 * @brief Given a move, checks if it violates the 3x3, row, and/or
 * column constraints.
 *
 * @param x user specified row
 * @param y user specified column
 * @param val number to add
 *
 * @return True if valid move. False otherwise.
 */

bool Grid::checkValid(int x, int y, char val)
{
    if ((x < 0) || (x > 8)) // Check if 0 < x < 8.
    {
        cout << "ERROR: index not in range" << endl;
        return 0;
    }

    if ((y < 0) || (y > 8)) // Check if 0 < y < 8.
    {
        cout << "ERROR: index not in range" << endl;
        return 0;
    }

    // Check if 1 < val < 9.
    if (((int) (val - '0') < 1) || ((int) (val - '0') > 9)) 
    {
        cout << "ERROR: invalid value" << endl;
        cout << val << endl;
        return 0;
    }

    // Check if grid is non-empty.
    if (grid[x][y] != ' ')
    {
        cout << "ERROR: grid is occupied" << endl;
        return 0;
    }

    // Check if val is in row x
    char row[9];

    for (int j = 0; j < 9; j++)
    {
        row[j] = grid[x][j];
    }

    if (find(begin(row), end(row), val) != end(row))
    {
        cout << "ERROR: value exists in row" << endl;
        return 0;
    }

    // Check if val is in column y
    for (int i = 0; i < 9; i++)
    {
        if (grid[i][y] == val)
        {
            cout << "ERROR: value exists in column" << endl;
            return 0;
        }    
    }

    // To check if val is in the box specified by row and and column y.
    int box_x = floor(x / 3);
    int box_y = floor(y / 3);
    int *rows = new int[3];
    int *cols = new int[3];
    
    // Check which box val is in.
    if (box_x == 0)
    {
        rows[0] = 0;
        rows[1] = 1;
        rows[2] = 2;
    }

    else if (box_x == 1)
    {
        rows[0] = 3;
        rows[1] = 4;
        rows[2] = 5;
    }

    else 
    {
        rows[0] = 6;
        rows[1] = 7;
        rows[2] = 8;
    }

    if (box_y == 0)
    {
        cols[0] = 0;
        cols[1] = 1;
        cols[2] = 2;
    }

    else if (box_y == 1)
    {
        cols[0] = 3;
        cols[1] = 4;
        cols[2] = 5;
    }

    else
    {
        cols[0] = 6;
        cols[1] = 7;
        cols[2] = 8;
    }
  
    // Check if val is in box.
    for (int i = 0; i < 3; i++)
    {
        int r = rows[i];

        for (int j = 0; j < 3; j++)
        {
            int c = cols[j];

            if (val == grid[r][c])
            {
                cout << "ERROR: value exists in box" << endl;
                return 0;                
            }
        }
    }

    delete[] rows;
    delete[] cols;

    return 1;    
}


/*
 * @brief Given a move, applies it to the board if it does not violate
 * any constraints.
 *
 * @param x user specified row
 * @param y user specified column
 * @param val number to add
 */

void Grid::writeNum(int x, int y, char val)
{
    grid[x][y] = val;
}

/*
 * @brief Undoes the move in the given position.
 *
 * @param x user specified row
 * @param y user specified column
 */

void Grid::undoNum(int x, int y)
{
    // If this grid in the original board is not empty, cannot undo.
    if (grid_o[x][y] != ' ') 
    {
        cout << "ERROR: cannot undo existing board." << endl;
    }

    else
    {
        grid[x][y] = ' ';
    }
}






    



    






            
        

