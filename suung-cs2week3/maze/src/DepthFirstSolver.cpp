/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    /* TODO: Write your initialization code here! */
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            visited[x][y] = 0;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
    /* TODO: Write your cleanup code here! */
}


/** 
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    /* TODO: Solve the maze.
     *
     * You are provided a `visited` member variable that you can use to
     * track which cells you have already visited; you are responsible for
     * maintaining it, filling it with useful information, and using it
     * in a consistent way. */

    stack->push(Coordinate(MAZE_START_X, MAZE_START_Y)); 

    while (!stack->is_empty())
    {
        // Find the current coordinate in maze
        Coordinate current(stack->peek());
        visited[current.x][current.y] = 1;

        if ((current.x == MAZE_END_X) & (current.y == MAZE_END_Y))
        {

            break;
        }   

        else
        {
            int possible = maze->get_possible_moves(current.x, current.y);

            // Finding all possible moves.
            if (possible & N)
            {
                Coordinate next = Coordinate(current.x, current.y - 1);

                if (visited[next.x][next.y] == 0)
                {
                    // If next coordinate unvisited, push to stack, then start
                    // a new iteration of the loop.
                    stack->push(next);
                    continue;
                }
            }

            if (possible & S)
            {
                Coordinate next = Coordinate(current.x, current.y + 1);

                if (visited[next.x][next.y] == 0)
                {
                    stack->push(next);
                    continue;
                }
            }

            if (possible & E)
            {
                Coordinate next = Coordinate(current.x + 1, current.y);
                
                if (visited[next.x][next.y] == 0)
                {
                    stack->push(next);
                    continue;
                }
            }

            if (possible & W)
            {
                Coordinate next = Coordinate(current.x - 1, current.y);
                
                if (visited[next.x][next.y] == 0)
                {
                    stack->push(next);
                    continue;
                }
            }

            // If no moves available, backtrack.
            stack->pop();
        }
    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    vector<Coordinate> list;

    /* TODO: Get the current path through the maze. For a DFS, this is quite
     * easy: just get all the Coordinates on the stack. */

    stackitem *top = stack->get_top();
    list.clear();

    while (top != nullptr)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        list.push_back(top->c); 
        top = top->next;
    }

    return list;
}

