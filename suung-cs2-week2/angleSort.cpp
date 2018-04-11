/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>

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

int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])
    sort_inplace(angles, points, 0, angles.size()-1);

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
