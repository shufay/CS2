/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

int partition(std::vector<double> &list, std::vector<Tuple*> &list2, int left, int right, int size)
{
    double pivot = list[right];
    int larger = left;

    for (int i = left; i < left+(size); i++)
    {
        if ((i == 0) & (list[i] < pivot))
        {
            larger++;
        }

        else if (list[i] <= pivot)
        {
            if (list[i-1] > pivot)
            {
                double temp = list[larger];
                Tuple* temp2 = list2[larger];
                int shift = i - larger;
                list[larger] = list[i];
                list2[larger] = list2[i];

                for (int j = 0; j < shift; j++)
                {
                    list[i-j] = list[i-j-1];
                    list2[i-j] = list2[i-j-1];
                }

                list[larger+1] = temp;
                list2[larger+1] = temp2;
            }
                
               larger++;
        }
    }
    
    if (larger != right)
    {
        double temp = list[larger];
        Tuple* temp2 = list2[larger];
        list[larger] = pivot;
        list2[larger] = list2[right];

        for (int i = 0; i < (right - larger); i++)
        {
            list[right-i] = list[right-i-1];
            list2[right-i] = list2[right-i-1];
        }

        list[larger+1] = temp;
        list2[larger+1] = temp2;
    }

    return larger;
}

/*
 * Modified inplace quicksort.
 */
void sort_inplace(std::vector<double> &list, std::vector<Tuple*> &list2, int left, int right)
{
  int size = right - left;

    if (size > 0)
    {
        int pivot_ind = partition(list, list2, left, right, size);
        sort_inplace(list, list2, left, pivot_ind-1);
        sort_inplace(list, list2, pivot_ind+1, right);
    }

    return;
}

/*
 * Finds the left-most point.
 */
Tuple* left_most(vector<Tuple*> points)
{
    double min = points[0]->x;
    double *m = &min;
    Tuple* fpoint = points[0];

    for (unsigned int i = 1; i < points.size(); ++i)
    {
        if (points[i]->x < min)
        {
            *m = points[i]->x;
            fpoint = points[i];
        }
    }

    return fpoint;
}

Tuple make_v(Tuple* p1, Tuple* p2)
{
    int X = p2->x - p1->x;
    int Y = p2->y - p1->y;
    Tuple r = Tuple(X, Y);
    return r;
}

double cross_p(Tuple v1, Tuple v2)
{
    double cross = v1.x * v2.y - v1.y * v2.x;
    return cross;
}

bool right_turn(Tuple* current, Tuple* test, Tuple* check, bool norm)
{
    Tuple v_test = make_v(current, test);
    Tuple v_check = make_v(current, check);
    double result = cross_p(v_test, v_check);

    if (norm == false)
    {
        if (!signbit(result) & !norm)
        {
            return true;
        }
    }

    else if (signbit(result) & norm)
    {
        return true;
    }

    return false;
}

/*
 * Find the left-most point and add it to hull.
 * Pick another point to test if it's in hull.
 * Construct a vector (v_test) between the current point and test point.
 * Loop over all other points (check points). Construct vectors (v_check)
 * between these points and the current point.  
 * Calculate cross products of v_test and v_check.
 * If the cross products have the same sign, then all other points lie
 * on one side of v_test, so the test point is in hull.
 * Update the current point to this test point and delete the point 
 * from the 'list' of points.
 * Repeat. 
 *
 */
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    // Make copy of points; this is the vector we'll be referring 
    // indices to. 
    vector<Tuple*> points_o(points); 
    Tuple* left = left_most(points_o); // Find left-most point.
    Tuple* current = left; // Set this to be the first hull point.
    unsigned int i = 0;
    app->add_to_hull(current);

    // Pick a point to test
    while (true)
    {
        Tuple* test = points[i % points.size()];
        Tuple* check = points[(i+1) % points.size()];
        Tuple v_test = make_v(current, test);
        Tuple v_check = make_v(current, check);
        bool go = true;
        bool norm = signbit(cross_p(v_test, v_check));
        unsigned int ind_current = find(points_o.begin(), points_o.end(), current) - points_o.begin();

        if (ind_current != i)
        {
            // Test if point is in hull.
            // Check cases for all points. See if they lie on same side
            // of v_test.
            for (unsigned int j = 0; j < points_o.size(); ++j)
            {
                check = points[j];

                // If test point is same as current, continue.
            
            
                    // If found a point with cross product diff sign, means 
                    // both side of v_test has points. Not in hull.
                   if (!right_turn(current, test, check, norm))
                    {
                        go = false;
                        break; // Stop checking, go to next test point.
                    }
                
            }

            // Goes through for loop, means all points are on the same side
            // of v_test, so in hull.
            if (go) 
            {
                app->add_to_hull(test);

                // If loop back to first point in hull, stop.
                if (test == left)
                {
                    break;
                }

                else
                {
                    current = test; // Let test become new current.

                    // Erase point from list to be tested.
                    points.erase(points.begin()+ i % points.size()); 

                    // Reset index to start testing for all points for this 
                    // new current. To find next in hull.
                    i = 0; 
                    continue;
                }
            }
        }

        ++i;
    }
}

/*
 * Finds the lowest point.
 */
Tuple* bottom_most(vector<Tuple*> points)
{
    double min = points[0]->y;
    double *m = &min;
    Tuple* fpoint = points[0];

    for (unsigned int i = 1; i < points.size(); ++i)
    {
        if (points[i]->y < min)
        {
            *m = points[i]->y;
            fpoint = points[i];
        }
    }

    return fpoint;
}

/*
 * Creates the 'list' of angles from the 'list' of points.
 */
vector<double> create_angle(vector<Tuple*> points)
{
    Tuple* bottom = bottom_most(points);
    vector<double> angles;

    for (unsigned int i = 0; i < points.size(); ++i)
    {
        if (points[i] != bottom)
        {
            angles.push_back(points[i]->angle_wrt_pt(bottom));
        }

        else
        {
            angles.push_back(0.0);
        }
    }

    return angles;
}

/*
 * Find the lowest point.
 * Sort the 'list' of points according to their angle.
 * Loop through all points in the sorted order, adding points to hull
 * when right turns can be made, making sure that the added points 
 * also make right turns with previous hull points.
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    // Create vector storing angle of the line from a point to the 
    // lowest point to the horizontal through the lowest point.
    vector<double> angles = create_angle(points);

    // Sort points according to angles.
    sort_inplace(angles, points, 0, angles.size()-1);

    // Find norm - sign of 'turn' we want.
    Tuple v1 = make_v(points[1], points[0]);
    Tuple v2 = make_v(points[1], points[2]);
    bool norm = signbit(cross_p(v1, v2));

    // Create vector to store hull points. The lowest point and next
    // point automatically inserted.
    vector<Tuple*> hull(points.begin(), points.begin()+2);

    // Starting from third element in  vector of sorted points, loop
    // over points, see if they belong in hull.
    for (unsigned int i = 2; i < points.size(); ++i)
    {
        // Consider current point, the point before, and the point 
        // after in sorted points.
        Tuple* p1 = points[i-1];
        Tuple* p2 = points[i];
        Tuple* p3 = points[(i+1) % points.size()]; 

        // If right turn (equals initial norm):
        if (right_turn(p2, p1, p3, norm))
        {
            // Add current point to hull.
            hull.push_back(p2);

            // Index of this point in hull.
            unsigned int ind = hull.size()-1;

            // Loop through previous points in hull. If previous
            // 3 points not a right turn, remove the point just before
            // new hull point added. Continue checking until a right
            // turn is found.
            while (!right_turn(p2, hull[ind-1], hull[ind-2], norm))
                //current, test, check 
            {
                // Remove the problem point.
                hull.erase(hull.end()-2);

                // Update last hull point position
                ind = hull.size()-1;

                // Prevents seg_fault
                if (ind < 2)
                {
                    break;
                }
            }
        }
    }

    // For all hull points, add them to app.
    for (unsigned int i = 0; i < hull.size(); ++i)
    {
        app->add_to_hull(hull[i]);
    }
    
    // Add lowest point to app again.
    app->add_to_hull(points[0]);
}
    
    

