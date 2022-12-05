#include <vector>
#include "Crime.h"

using namespace std;

// Borrowing structure from merge sort pseudocode on Sorting PPT page 88
void merge(vector<Crime*>* dataSet, unsigned int stat, int left, int middle, int right) {

    // Create size variables
    int sizeLeft = (middle - left) + 1;
    int sizeRight = right - middle;

    // Create arrays to hold parts of array
    Crime* leftArray[sizeLeft];
    Crime* rightArray[sizeRight];

    // Fill arrays
    for ( int i = 0; i < sizeLeft; ++i) {
        leftArray[i] = dataSet->at(i);
    }
    for ( int i = (middle + 1); i < sizeRight; ++i) {
        rightArray[i] = dataSet->at(i);
    }

    // Merge the two arrays together
    int i = 0; // Index for dataSet
    int x = 0; // Index for left array
    int y = 0; // Index for right array
    while ( x < sizeLeft && y < sizeRight ) {

        // leftArray[x] <= rightArray[y]
        if (getData(leftArray[x], stat) <= getData(rightArray[y], stat)) {
            dataSet->at(i) = leftArray[x];
            ++x;
        }
        // rightArray[y] > leftArray[x]
        else {
            dataSet->at(i) = rightArray[y];
            ++y;
        }
        ++i; // Increment index
    }

    // Append leftover values
    for ( ; x < sizeLeft; ++x ) {
       dataSet->at(i) = leftArray[x];
       ++i;
    }

    for ( ; y < sizeRight; ++y ) {
        dataSet->at(i) = rightArray[y];
        ++i;
    }

}

void mergeSort(vector<Crime*>* dataSet, unsigned int stat, int start, int end) {

    if ( start < end ) { // Base case for array size 1
        int middle = start + (end - start) / 2; // Use this formula for average to prevent integer overflow
        mergeSort(dataSet, stat, start, middle);
        mergeSort(dataSet, stat, middle + 1, end);
        merge(dataSet, stat, start, middle, end);
    }
}

