//
// Created by alex on 12/6/22.
//

#ifndef DSA_PROJECT3_LINEAR_SEARCH_H
#define DSA_PROJECT3_LINEAR_SEARCH_H

#include <vector>
#include "Crime.h"

std::vector<Crime*> linearSearch(vector<Crime*> &dataSet, unsigned int target, int stat) {

    std::vector<Crime*> matches;

    for ( auto crime : dataSet) {

        // Add to matches if current crime stat matches target
        if ( crime->getData(stat) == target) {
            matches.push_back(crime);
        }
    }

    return matches;
}


#endif //DSA_PROJECT3_LINEAR_SEARCH_H
