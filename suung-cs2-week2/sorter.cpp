/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"
#include <math.h>

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size()-1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.hpp if you write a helper function!
 */

/* 
 * remaining_passes = list_length - 1
 *
 * WHILE remaining_passes > 0 
 *  FOR i in range(remaining_passes)
 *      IF list[i] > list[i+1] THEN
 *          swap them
 *          number_of_swaps++  
 *
 *      ELSE
 *          continue
 *
 *      ENDIF
 *
 *  IF number_of_swaps == 0 THEN
 *      remaining_passes = 0
 *
 *  ELSE
 *      remaining_passes--
 *      number_of_swaps = 0
 *
 *  ENDIF
 *
 */

std::vector<int> bubbleSort(std::vector<int> &list)
{
    int remaining_passes = list.size() - 1;
    int temp;
    int swaps;

    while (remaining_passes > 0)
    {
        for (int i = 0; i < remaining_passes; i++)
        {
            if (list[i] > list[i+1])
            {
                temp = list[i];
                list[i] = list[i+1];
                list[i+1] = temp;   
                swaps++;
            }
        }

        if (swaps == 0)
        {
            remaining_passes = 0;
        }

        else
        {
            remaining_passes--;
            swaps = 0;
        }
    }

    return list;
}

/*
 * IF list_length > 1 THEN
 *  smaller = []
 *  larger = []
 *
 *  FOR item in list
        IF item != pivot THEN
 *          IF item < pivot THEN
 *              append item to smaller
 *
 *          ELSE
 *              append item to larger
 *
 *          ENDIF
 *      ENDIF
 *
 *  smaller = quickSort(smaller)
 *  larger = quickSort(Larger)
 *
 *  list = [smaller, pivot, larger]
 *
 * ELSE
 *  return list
 *
 * ENDIF
 *  
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    if (list.size() > 1)
    {
        int pivot_ind = ceil((int) list.size() / 2);
        int pivot = list[pivot_ind];
        std::vector<int> smaller;
        std::vector<int> larger;

        for (int i = 0; i < (int) list.size(); i++)
        {
            if (i != pivot_ind)
            {
                if (list[i] > pivot)
                {
                    larger.push_back(list[i]);
                }

                else
                {
                    smaller.push_back(list[i]);
                }
            }
        }
        
        smaller = quickSort(smaller);
        larger = quickSort(larger);

        std::vector<int>::iterator start = list.begin();
        std::vector<int>::iterator last = list.end();
        int s_size = smaller.size();

        list.clear();
        list.insert(start, smaller.begin(), smaller.end());
        list.insert(start+s_size, pivot);
        list.insert(start+s_size+1, larger.begin(), larger.end());
    }

    return list;
}

/*
 * IF list_length > 1 THEN
 *  merged = []
 *  to_erase = []
 *  size = list_length
 *
 *  FOR item in list
 *      merged.append([item])
 * 
 *  WHILE list_length > 1
 *      IF list_length % 2 == 0 THEN
 *          FOR i in range(0, size, 2)
 *              merge(list[i], list[i+1])
 *              to_erase.append(i+i)
 *      ELSE 
 *          FOR i in range(0, size - 1, 2)
 *              merge(list[i], list[i+1])
 *              to_erase.append(i+1)
 *      ENDIF
 *
 *      FOR k in range(length of to_erase)
 *          merged.remove(merged[to_erase[k]-k])
 *
 *      size = length of merged
 *      empty to_erase
 *
 *  replace left with merged[0]
 *
 * ENDIF
 *
 * return list
 *      
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
    int size = (int) list.size();
    int *s = &size;

    if (size > 1)
    {
        std::vector<std::vector<int>> merged; 
        std::vector<int> to_erase;

        for (int i = 0; i < size; i++)
        {
            std::vector<int> item (1, list[i]);
            merged.push_back(item);
        }

        while (size > 1)
        {
            if (size % 2 == 0)
            {
                for (int i = 0; i < size; i += 2)
                {
                    merge(merged[i], merged[i+1]);
                    to_erase.push_back(i+1);
                }
            }

            else
            {
                for (int i = 0; i < (size-1); i += 2)
                {
                    merge(merged.at(i), merged.at(i+1));
                    to_erase.push_back(i+1);
                }
            }

            for (int i = 0; i < (int) to_erase.size(); i++)
            {
                merged.erase(merged.begin()+to_erase[i]-i);
            }

            *s = (int) merged.size();
            to_erase.clear();
        }

        list.swap(merged[0]);
    }

    return list;
}

/*
 * merged = []
 * i = 0
 * j = 0
 *
 * WHILE i < left_length or j < right_length
 *      IF left[i] < right[j] THEN
 *          append left[i] to merged
 *          i++
 *
 *      ELSE
 *          append right[j] to merged
 *          j++
 *
 *      ENDIF
 *
 * IF i == left_length THEN
 *  append right[j, -1] to merged
 *
 * ELSE
 *  append left[i, -1] to merged
 * 
 * ENDIF
 *
 * empty right
 * replace left with merged
 * return left
 * 
 * NOTE: Changed 'merge' to return nothing.
 *
 */
void merge(std::vector<int> &left, std::vector<int> &right)
{
    std::vector<int> merged;
    int i = 0;
    int j = 0;

    while ((i < (int) left.size()) && (j < (int) right.size()))
    {
        if (left[i] < right[j])
        {
            merged.push_back(left[i]);
            i++;
        }

        else
        {
            merged.push_back(right[j]);
            j++;
        }
    }

    if (i == (int) left.size())
    {
        if (j == 0)
        {
            for (int k = 0; k < (int) right.size(); k++)
            {
                merged.push_back(right[k]);
            }
        }

        else
        {
            merged.insert(merged.end(), right.begin()+j, right.end());
        }
    }

    else if (j == (int) right.size()) 
    {
        if (i == 0)
        {
            for (int k = 0; k < (int) left.size(); k++)
            {
                merged.push_back(left[k]);
            }
        }

        else
        {
            merged.insert(merged.end(), left.begin()+i, left.end());
        }
    }
    
    left.swap(merged);
    right.clear();
    merged.clear();
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 * 
 * size = right - left
 *
 * IF size > 0 THEN
 *  pivot_ind = partition(list[left, right])
 *  quicksort_inplace(list[left, pivot_ind-1])
 *  quicksort_inplace(list[pivot_ind+1, right])
 *
 * ENDIF
 *
 */

void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    int size = right - left;

    if (size > 0)
    {
        int pivot_ind = partition(list, left, right, size);
        quicksort_inplace(list, left, pivot_ind-1);
        quicksort_inplace(list, pivot_ind+1, right);
    }
    return;
}

/*
 * pivot_ind = right
 * pivot = list[pivot_ind]
 * size = right - left
 * larger = left
 *
 * FOR i in range(left, left+size)
 *  IF i == 0 and list[i] < pivot THEN
 *      larger++
 *
 *  ELSE IF list[i] <= pivot THEN
 *          IF list[i-1] > pivot THEN
 *              temp = list[larger]
 *              shift = i - larger
 *              list[larger] = list[i]
 *          
 *              FOR j in range(shift)
 *                  list[i-j] = list[i-j-1]
 *          
 *              list[larger+1] = temp
 *          
 *          larger++
 *
 *          ENDIF
 *  ENDIF
 *
 * IF larger != right THEN
 *  temp = list[larger]
 *  list[larger] = pivot
 *
 *  FOR i in range(right - larger)
 *      list[right-i] = list[right-i-1] 
 *      
 *  list[larger+1] = temp
 *
 * ENDIF
 *
 * return larger      
 *      
 */
int partition(std::vector<int> &list, int left, int right, int size)
{
    int pivot = list[right];
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
                int temp = list[larger];
                int shift = i - larger;
                list[larger] = list[i];

                for (int j = 0; j < shift; j++)
                {
                    list[i-j] = list[i-j-1];
                }

                list[larger+1] = temp;
            }
                
            larger++;
        }
    }
    
    if (larger != right)
    {
        int temp = list[larger];
        list[larger] = pivot;

        for (int i = 0; i < (right - larger); i++)
        {
            list[right-i] = list[right-i-1];
        }

        list[larger+1] = temp;
    }

    return larger;
}



