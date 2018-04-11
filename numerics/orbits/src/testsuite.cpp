/**
 * @file test_solver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Simple test suite for Solver.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
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

#include "Solver.hpp"
#include <cstdio>

using namespace Solver;

// TEST 1
// root = -1
double deg_three(double x)
{
    return pow(x, 3.) + 1;
}

double deg_three_p(double x)
{
    return 3 * pow(x, 2.);
}

// TEST 2
// roots = -1.608, -0.219
double deg_four(double x)
{
    return pow(x, 4.) + 2 * pow(x, 2.) + 8 * x + 1;
}

double deg_four_p(double x)
{
    return 4 * pow(x, 3.) + 4 * x + 8;
}

// TEST 3
// root = 0.705694 
double transcend(double x)
{
    return deg_three(x) + sin(x);
}

double transcend_p(double x)
{
    return deg_three_p(x) + cos(x);
}

// TEST 4
// roots = 0.739085
double trans2(double x)
{
    return cos(x) - x;
}

double trans2_p(double x)
{
    return -sin(x) - 1;
}

int main()
{
    /* Do your testing here. */
    // TEST 1
    double x1_b = -1.75;
    double x2_b = -0.5;
    double x = -1.75;
    
    double root_b = bisection(deg_three, x1_b, x2_b);
    double root_n = newton_raphson(deg_three, deg_three_p, x);

    printf("TEST 1\n");
    printf("----------\n");
    printf("f(x) = x^3 + 1\n");
    printf("root = -1\n");
    
    printf("bisection(%f, %f): %f\n", x1_b, x2_b, root_b); 
    printf("newton_raphson(%f): %f\n\n", x, root_n);

    // TEST 2
    x1_b = -1.7;
    x2_b = -1.1;
    x = -1.1;

    root_b = bisection(deg_four, x1_b, x2_b);
    root_n = newton_raphson(deg_four, deg_four_p, x);
    
    double x1_b2 = -0.1;
    double x2_b2 = -0.3;
    double x2 = -0.1;

    double root_b2 = bisection(deg_four, x1_b2, x2_b2);
    double root_n2 = newton_raphson(deg_four, deg_four_p, x2);

    printf("TEST 2\n");
    printf("----------\n");
    printf("f(x) = x^4 + 2x^2 + 8x + 1\n");
    printf("roots = -1.608, -0.219\n");
    
    printf("bisection(%f, %f): %f\n", x1_b, x2_b, root_b); 
    printf("newton_raphson(%f): %f\n\n", x, root_n);
    
    printf("bisection(%f, %f): %f\n", x1_b2, x2_b2, root_b2); 
    printf("newton_raphson(%f): %f\n\n", x2, root_n2);
    
    // TEST 3
    x1_b = -0.8;
    x2_b = -0.5;
    x = -1.2;
    
    root_b = bisection(transcend, x1_b, x2_b);
    root_n = newton_raphson(transcend, transcend_p, x);
    
    printf("TEST 3\n");
    printf("----------\n");
    printf("f(x) = x^3 + 1 + sin(x)\n");
    printf("root = -0.70564\n");
    
    printf("bisection(%f, %f): %f\n", x1_b, x2_b, root_b); 
    printf("newton_raphson(%f): %f\n\n", x, root_n);
    
    // TEST 4
    x1_b = 0.87;
    x2_b = 0.6;
    x = 0.6;
    
    root_b = bisection(trans2, x1_b, x2_b);
    root_n = newton_raphson(trans2, trans2_p, x);

    printf("TEST 4\n");
    printf("----------\n");
    printf("f(x) = cos(x) - x\n");
    printf("root = 0.739085\n");
    
    printf("bisection(%f, %f): %f\n", x1_b, x2_b, root_b); 
    printf("newton_raphson(%f): %f\n", x, root_n);

    return 0;
}
