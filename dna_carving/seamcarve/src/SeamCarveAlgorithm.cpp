/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"
#include <algorithm>
#include <iostream>

#define min(x, y)           ((x) < (y) ? (x) : (y))

/*
 * @brief Finds cost of pixel in row 'r' and column 'c'.
 * 
 * @param cost_arr The cost array.
 *
 * @param smap The saliency map.
 * 
 * @param w Width of the saliency map.
 *
 * @param c Column of pixel.
 *
 * @param r Row of pixel.
 *
 * @return The cost of the pixel.
 */
unsigned int find_cost(unsigned int **cost_arr, unsigned int **smap, int w, int c, int r)
{
	unsigned int saliency = smap[c][r];

	if (r == 0)
	{
		cost_arr[c][r] = saliency;
        return cost_arr[c][r];
	}

	else
	{
		if (cost_arr[c][r] == 0)
		{
			unsigned int *three_above = new unsigned int;
            int elems;

			if (c == 0)
			{
				three_above[0] = find_cost(cost_arr, smap, w, 0, r-1);
				three_above[1] = find_cost(cost_arr, smap, w, 1, r-1);
                elems = 2;
			}

			else if (c == w-1)
			{
				three_above[0] = find_cost(cost_arr, smap, w, w-2, r-1);
				three_above[1] = find_cost(cost_arr, smap, w, w-1, r-1);
                elems = 2;
			}

			else
			{
				three_above[0] = find_cost(cost_arr, smap, w, c-1, r-1);
				three_above[1] = find_cost(cost_arr, smap, w, c, r-1);
				three_above[2] = find_cost(cost_arr, smap, w, c+1, r-1);
                elems = 3;	
			}

            cost_arr[c][r] = saliency + *std::min_element(three_above, three_above+elems);
			delete[] three_above;
		}

	    return cost_arr[c][r];
	}

}
/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    // Create cost array
    unsigned int **cost_arr = new unsigned int*[w];

    for (int i = 0; i < w; i++)
    {
    	cost_arr[i] = new unsigned int[h];

    	for (int j = 0; j < h; j++)
    	{
    		cost_arr[i][j] = 0; // Initialize value to 0
    	}
    }

    // Fill cost array. Iterate through last row because each 'find'
    // propagates upwards.
    for (int i = 0; i < w; i++)
    {
    	find_cost(cost_arr, smap, w, i, h-1);
    }

    // Find lowest cost in last row.
    unsigned int min = cost_arr[0][h-1];
    int min_ind = 0;

    for (int i = 0; i < w; i++)
    {
    	if (cost_arr[i][h-1] < min)
    	{
    		min_ind = i;
    		min = cost_arr[i][h-1];
    	}
    }

    // Create seam
    unsigned int *seam = new unsigned int[h];

    // Last pixel in seam is the pixel with min cost found earlier.
    seam[h-1] = min_ind;

    // Iterate through rest of rows. Trace seam path up.
    int begin;
    int end;

    for (int j = h-2; j > -1; j--)
    {
        if (min_ind == 0)
        {
            begin = 0;
            end = 2;
        }

        else if (min_ind == w-1)
        {
            begin = -1;
            end = 1;
        }

        else
        {
            begin = -1;
            end = 2;
        }

        for (int i = begin; i < end; i++)
        {
            unsigned int check = min - cost_arr[min_ind+i][j];

            if (check == smap[min_ind][j+1])
            {
                seam[j] = min_ind+i;
                min = cost_arr[min_ind+i][j];
                min_ind += i;
                break;
            }
        }
    }

    for (int i = 0; i < w; i++)
    {
    	delete[] cost_arr[i];
    }

    delete[] cost_arr;
    return seam;
}

