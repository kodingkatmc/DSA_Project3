#pragma once
#include <vector>
#include "Crime.h"

using namespace std;

void radixSort( vector<Crime*>* dataSet, unsigned int stat ) {

    // Store original input pointer
    vector<Crime*>* original = dataSet;
    // Save dataSet length;
    unsigned int size = (*dataSet).size();
    // Create and fill second vector
    vector<Crime*>* rebuild = new vector<Crime*>(size);
    // Count array for counts
    unsigned int* count = new unsigned int[256];

    // Iterations Loop (4 iterations over 8 bits each accounts for 32 bit numbers)
    for ( unsigned int iter = 0; iter < 4; iter++ ) {
        
        // Zero Counts
        for ( unsigned int i=0; i < 256; i++ ) {
            count[i] = 0;
        }

        // Counting loop
        for ( unsigned int i=0; i < size; i++ ) {
            unsigned int data = (dataSet->at(i))->getData(stat);
            count[data >> (iter*8) & 0xff]++;
        }

        // Prefix-Sum loop
        for ( unsigned int i=1; i < 256; i++ ) {
            count[i] += count[i-1];
        }

        // Rebuild Array
        for ( int i=size-1; i >= 0; i-- ) {
            // Calcualte offset index
            unsigned int data = (dataSet->at(i))->getData(stat);
            unsigned int index = (data >> (iter*8)) & 0xff;
            
            count[index]--;

            rebuild->at(count[index]) = dataSet->at(i);
        }

        // Swap pointers
        vector<Crime*>* tempPointer = dataSet;
        dataSet = rebuild;
        rebuild = tempPointer;


    }

    // Copy data from output to original array if necessary
    if (dataSet != original) {
        for ( unsigned int i=0; i < size; i++ ) {
            original->at(i) = dataSet->at(i);
        }
    }

    // Delete extra data
    delete rebuild;
    delete[] count;
    
}
