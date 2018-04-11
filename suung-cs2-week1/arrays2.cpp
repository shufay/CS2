/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 1000000

using namespace std;

int max(int *arr, int n)
{
    if (n == 0)
    {
        return 0;
    }

	int max = 0;

	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	return max;
}

double mean(int *arr, int n)
{
    if (n == 0)
    {
        return 0;
    }

	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}

	return sum / n;
}

void ascend(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
}		

/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int *test_values = new int[TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
       real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    // more test arrays
    int *test2 = new int[5]{1, 2, 3, 4, 5};
    int len2 = 5;

    int *test3 = new int[3]{3, 2, 1};
    int len3 = 3;

    int *test4 = new int[4]{2, 4, 6, 8};
    int len4 = 4;
    
    // test_values
    cout << "test_values" << endl;
    cout << "max value: " << max(test_values, real_size) << endl;
    cout << "arithmetic mean: " << mean(test_values, real_size) << endl;
    ascend(test_values, real_size);
    cout << "array elements after ascend(test_values, real_size): " << endl;

    for (int i = 0; i < real_size; i++)
    {
        cout << test_values[i] << endl;
    }

    cout << endl;

    // test2
    cout << "test2" << endl;
    cout << "max value: " << max(test2, len2) << endl;
    cout << "arithmetic mean: " << mean(test2, len2) << endl;
    ascend(test2, len2);
    cout << "array elements after ascend(test2, len2): " << endl;

    for (int i = 0; i < len2; i++)
    {
        cout << test2[i] << endl;
    }

    cout << endl;

    // test3
    cout << "test3" << endl;
    cout << "max value: " << max(test3, len3) << endl;
    cout << "arithmetic mean: " << mean(test3, len3) << endl;
    ascend(test3, len3);
    cout << "array elements after ascend(test3, len3): " << endl;

    for (int i = 0; i < len3; i++)
    {
        cout << test3[i] << endl;
    }

    cout << endl;

    // test4
    cout << "test4" << endl;
    cout << "max value: " << max(test4, len4) << endl;
    cout << "arithmetic mean: " << mean(test4, len4) << endl;
    ascend(test4, len4);
    cout << "array elements after ascend(test4, len4): " << endl;

    for (int i = 0; i < len4; i++)
    {
        cout << test4[i] << endl;
    }
    
    return 0;
}
