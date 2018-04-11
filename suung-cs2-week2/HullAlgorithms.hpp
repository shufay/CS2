/*
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.hpp"
#include "structs.hpp"

using namespace std;

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
int partition(vector<double> &list, vector<Tuple*> &list2, int left, int right, int size);
void sort_inplace(vector<double> &list, vector<Tuple*> &list2, int left, int right);
Tuple* left_most(vector<Tuple*> points);
Tuple make_v(Tuple* p1, Tuple* p2);
double cross_p(Tuple v1, Tuple v2);
bool right_turn(Tuple* current, Tuple* test, Tuple* check, bool norm);
Tuple* bottom_most(vector<Tuple*> points);
vector<double> create_angle(vector<Tuple*> points);

