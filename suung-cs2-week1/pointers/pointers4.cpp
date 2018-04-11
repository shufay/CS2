/**
 * @file pointers4.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 4: Typecasting vs. address-of
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief performs type castings
 */
int main(int argc, char *argv[])
{
    int a = 5, *b;
    void *c;

    // Now make `b` point to `a`.
    b = (int *) &a; // pointer b must be assigned to an address.

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    cout << "The value pointed by `b` is " << *b << endl;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // Allocate an array of 10 ints.
    c = malloc(10 * sizeof(int));

    // Get the address of the array.

    // 'c' is a pointer to the first chunk of memory allocated. '&c'
    // is the address of the pointer variable 'c'. We want 'b' to 
    // point the same location as 'c', not the address of 'c'. 
    b = (int *) c;

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    b[2] = 5;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    return 0;
}
