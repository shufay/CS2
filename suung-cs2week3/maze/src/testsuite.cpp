/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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

#include <cstdio>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"

int main()
{
    Coordinate c;
    Coordinate d;
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();

    /*
     * Test stack
     */

    printf("\n \n Testing stack \n \n");

    // pushing to stack
    for (int i = 1; i < 5; i++)
    {
    	stack->push(Coordinate(i, i+2));
    	printf("pushing (%i, %i) to stack...\n", i, i+2);
    	c = stack->peek();
    	printf("pushed to top: (%i, %i)\n \n", c.x, c.y);
    }
 
	// popping from stack
	for (int i = 1; i < 5; i++)
	{
		c = stack->pop();
		printf("popping (%i, %i) from stack...\n", c.x, c.y);
		d = stack->peek();
		printf("new top: (%i, %i)\n \n", d.x, d.y);
	}  

	// is stack empty?
	if (stack->is_empty())
	{
		printf("stack is empty\n \n");
	}

	// popping empty stack
	c = stack->pop();
	printf("popping from empty stack...\n");
	printf("return dummy: (%i, %i)\n \n", c.x, c.y);

	/*
	 * Test queue
	 */
	printf("\n \n Testing queue \n \n");

	// enqueueing queue
    for (int i = 1; i < 5; i++)
    {
    	queue->enqueue(Coordinate(i, i+2));
    	printf("enqueueing (%i, %i) to queue...\n", i, i+2);
    	c = queue->peek();
    	printf("front: (%i, %i)\n \n", c.x, c.y);
    }
 
	// dequeueing queue
	for (int i = 1; i < 5; i++)
	{
		c = queue->dequeue();
		printf("dequeueing (%i, %i) from queue...\n", c.x, c.y);
		d = queue->peek();
		printf("front: (%i, %i)\n \n", d.x, d.y);
	}  

	// is queue empty?
	if (queue->is_empty())
	{
		printf("queue is empty\n \n");
	}

	// dequeueing empty stack
	c = queue->dequeue();
	printf("dequeueing from empty queue...\n");
	printf("return dummy: (%i, %i)\n \n", c.x, c.y);

    delete queue;
    delete stack;

    return 0;
}
