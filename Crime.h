#pragma once
#include <string>

using namespace std;

struct Crime{
    // Sortable values
    unsigned int year;
    unsigned int age;
    unsigned int valueStolen;
    unsigned int valueRec;
    unsigned int descCode;

    //Other Values
    string agency;
    string state;
    string desc;

};