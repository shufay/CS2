/**
 * @file fileio.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 */

#include "fileio.hpp"
#include <fstream>
#include <string>
#include <iostream>

/**
 * @brief Reads the integers in file and fills nums with these integers.
 *
 * @param file: File containing integers, one per line.
 * @param nums: Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, std::vector<int> &nums)
{
    std::string num;
    std::ifstream myfile(file);
    if (myfile.is_open())
    {
        while (std::getline(myfile, num))
        {
            nums.push_back(atoi(num.c_str()));
        }
    }

    myfile.close();
}
