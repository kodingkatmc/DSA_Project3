#pragma once
#include <vector>
#include "Crime.h"

vector<Crime*> binarySearchHelper(vector<Crime*> dataSet, unsigned int query, unsigned int stat, unsigned int start, unsigned int end) {
    
    unsigned int middle =  start + (end - start) / 2;
    unsigned int data = dataSet[middle]->getData(stat);
    
    if ( data == query ) {
        vector<Crime*> results;
        results.push_back(dataSet[middle]);

        unsigned int i = middle-1;
        while ( start <= i && i <= end && dataSet[i]->getData(stat) == query ) {
            results.push_back(dataSet[i]);
            i--;
        }
        
        i = middle+1;
        while ( start <= i && i <= end && dataSet[i]->getData(stat) == query ) {
            results.push_back(dataSet[i]);
            i++;
        }
        return results;
    }
    
    if ( start == end ) {
        return {};
    }

    if ( data < query ) {
        return binarySearchHelper(dataSet, query, stat, middle+1, end);
    } else if ( data > query ) {
        return binarySearchHelper(dataSet, query, stat, start, middle);
    }
    return {};
}

vector<Crime*> binarySearch(vector<Crime*> &dataSet, unsigned int query, unsigned int stat) {
    return binarySearchHelper(dataSet, query, stat, 0, dataSet.size()-1);
}
