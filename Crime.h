#pragma once
#include <string>

using namespace std;

class Crime{

    public:
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

        Crime();
        unsigned int getData( unsigned int stat );

};

Crime::Crime() {
    year = 0;
    age = 0;
    valueStolen = 0;
    valueRec = 0;
    descCode = 0;

    agency = "";
    state = "";
    desc = "";
}

unsigned int Crime::getData ( unsigned int stat ) {
    switch ( stat ) {
        case 1:
            return this->year;
        case 2:
            return this->age;
        case 3:
            return this->valueStolen;
        case 4:
            return this->valueRec;
        case 5:
            return this->descCode;
    }
    return 0;
}