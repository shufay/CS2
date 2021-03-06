/**
 * @file CoordinateStack.hpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Definitions for stack class that stores Coordinate objects.
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

#ifndef __COORDINATESTACK_H__
#define __COORDINATESTACK_H__

#include <cstdlib>
#include <vector>
#include "common.hpp"

using namespace std;

/**
 * @brief Simple stack item for Coordinate objects.
 */
struct stackitem {
    Coordinate c;
    stackitem *next;
};

#ifndef TESTSUITE
#include "MazeSolverBase.hpp"
#include "MazeSolverApp.hpp"
#endif

/**
 * @brief Encapsulates a stack for Coordinate objects.
 */
class CoordinateStack
{
public:
#ifndef TESTSUITE
    CoordinateStack(class MazeSolverApp *app);
#else
    CoordinateStack();
#endif
    ~CoordinateStack();

    void push(Coordinate c);
    Coordinate pop();
    Coordinate peek();
    stackitem* get_top();
    bool is_empty();

private:
    stackitem *top;

#ifndef TESTSUITE
    class MazeSolverApp *app;
#endif

    void init();
    void deinit();
    void do_push(Coordinate c);
    Coordinate do_pop();
};

#endif
