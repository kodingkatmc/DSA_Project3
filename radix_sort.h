#pragma once
#include <vector>
#include "Crime.h"

using namespace std;

unsigned int getData ( Crime* data, unsigned int stat ) {
    switch ( stat ) {
        case 0:
            return data->year;
        case 1:
            return data->age;
        case 2:
            return data->valueStolen;
        case 3:
            return data->valueRec;
        case 4:
            return data->descCode;
    }
    return 0;
}

void radixSort( vector<Crime*>* dataSet, unsigned int stat ) {

    // Store original input pointer
    vector<Crime*>* original = dataSet;
    // Save dataSet length;
    unsigned int size = (*dataSet).size();
    // Create and fill second vector
    vector<Crime*>* rebuild = new vector<Crime*>;
    vector<Crime*>* tempValues = new vector<Crime*>;
    for ( unsigned int i=0; i < size; i++) {
        Crime* temp = new Crime;
        rebuild->push_back(temp);
        tempValues->push_back(temp);
    }
    // Count array for counts
    unsigned int* count = new unsigned int[16];

    // Iterations Loop (8 iterations over 4 bits each accounts for 32 bit numbers)
    for ( unsigned int iter = 0; iter < 8; iter++ ) {
        
        // Zero Counts
        for ( unsigned int i=0; i < 16; i++ ) {
            count[i] = 0;
        }

        // Counting loop
        for ( unsigned int i=0; i < size; i++ ) {
            unsigned int data = getData(dataSet->at(i), stat);
            count[data >> (iter*4) & 0xf]++;
        }

        // Prefix-Sum loop
        for ( unsigned int i=1; i < size; i++ ) {
            count[i] += count[i-1];
        }

        // Rebuild Array
        for ( int i=size-1; i >= 0; i-- ) {
            // Calcualte offset index
            unsigned int data = getData(dataSet->at(i), stat);
            unsigned int index = (data >> (iter*4)) & 0xf;
            
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
    for ( unsigned int i = 0; i < size ; i++ ){
        delete tempValues->at(i);
    }
    delete tempValues;
    delete rebuild;
    delete[] count;
    
}
