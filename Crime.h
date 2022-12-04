#pragma once
#include <string>

using namespace std;

struct Crime{
    // Sortable values
    unsigned int year;
    unsigned int age;
    float valueStolen;
    float valueRec;
    int descCode; // TODO: maybe not use

    //Other Values
    string agency;
    string state;
    string desc;
};