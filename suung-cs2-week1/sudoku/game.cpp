#include <iostream>
#include <string>
#include "game.hpp"
using namespace std;

/*
 * @brief Constructs a Game object.
 */

Game::Game()
{
    moves = 0;
}

/*
 * @brief Gets a move from user input.
 *
 * 'd' denotes a move followed by the row, column and value
 * (e.g. d 1 1 2).
 *
 * 'u' undoes a move followed by the row and column (e.g. u 1 1).
 *
 * 'q' quits the game.
 */

void Game::getMove()
{
    char move;
    cout << "Enter a move: " << endl;
    cin >> move;
   
    // User enters 'q'.
    if (move == 'q')
    {
        exit(0);
    }

    // User enters 'd <x> <y> <val>'.
    else if (move == 'd')
    {
        int x, y;
        char val;
        cin >> x >> y >> val; 

        if (myGrid.checkValid(x - 1, y - 1, val))
        {
            myGrid.writeNum(x - 1, y - 1, val);
        }
    }
    
    // User enters 'u <x> <y>'.
    else if (move== 'u')
    {
        int x, y;
        cin >> x >> y;
        myGrid.undoNum(x - 1, y - 1);
    }

    else
    {
        cout << "ERROR: invalid move" << endl;
    }
}

/*
 * @brief Sets up and plays a single session of Sudoku.
 */

void Game::Run()
{ 
    string filename;

    do 
    {
        cout << "Enter a file: " << endl;
        getline(cin, filename);;
    } while (myGrid.loadBoard(filename));

    myGrid.display();
    
    bool a = myGrid.isComplete();

    while (!a) // While myGrid is not complete...
    {
        Game::getMove();
        moves += 1;
        myGrid.display();
        a = myGrid.isComplete(); 
    }
   
    cout << "moves: " << moves << endl;;
    cout << "SOLVED" << endl; 
    exit(0);
    return;
}        


