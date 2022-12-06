#pragma once
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
        leftArray[i] = dataSet->at(i + left);
    }
    for ( int i = 0; i < sizeRight; ++i) {
        rightArray[i] = dataSet->at(i + middle + 1);
    }

    // Merge the two arrays together
    int i = 0; // Index for dataSet
    int x = 0; // Index for left array
    int y = 0; // Index for right array
    while ( x < sizeLeft && y < sizeRight ) {

        // leftArray[x] <= rightArray[y]
        if (leftArray[x]->getData(stat) <= rightArray[y]->getData(stat)) {
            dataSet->at(i + left) = leftArray[x];
            ++x;
        }
        // rightArray[y] > leftArray[x]
        else {
            dataSet->at(i + left) = rightArray[y];
            ++y;
        }
        ++i; // Increment index
    }

    // Append leftover values
    for ( ; x < sizeLeft; ++x ) {
       dataSet->at(i + left) = leftArray[x];
       ++i;
    }

    for ( ; y < sizeRight; ++y ) {
        dataSet->at(i + left) = rightArray[y];
        ++i;
    }

}

void mergeSortHelper(vector<Crime*>* dataSet, unsigned int stat, int start, int end) {

    if ( start < end ) { // Base case for array size 1
        int middle = start + (end - start) / 2; // Use this formula for average to prevent integer overflow
        mergeSortHelper(dataSet, stat, start, middle);
        mergeSortHelper(dataSet, stat, middle + 1, end);
        merge(dataSet, stat, start, middle, end);
    }
}


void mergeSort(vector<Crime*>* dataSet, unsigned int stat) {

    mergeSortHelper(dataSet, stat, 0, dataSet->size() - 1);
    
}