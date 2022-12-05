#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Crime.h"
#include "radix_sort.h"

using namespace std;

int main() {
    
    // Open file
    ifstream input;
    input.open("CT_2013_2021_very_reduced.csv");
    if ( !input.is_open() ) {
        cerr << "Error Opening File\n";
        return -1;
    }

    vector<Crime> dataSet;

    string line;
    // Clears first line which contains column headers
    getline(input, line);

    // Reads data in from file
    while ( getline(input, line) ) {
        Crime tempInput;

        for ( unsigned int i=0; i<32; i++ ) {
            
            string cell;

            if ( line.substr(0,1) == "\"" ) {
                line = line.substr(line.find("\"")+1);
                cell = line.substr(0,line.find("\""));
                line = line.substr(line.find("\"")+2);
            } else {
                cell = line.substr(0,line.find(","));
                line = line.substr(line.find(",")+1);
            }

            
            // cout << cell;
            switch ( i ) {
                case 0:
                    tempInput.year = stoi(cell);
                    break;
                case 2:
                    tempInput.agency = cell;
                    break;
                case 6:
                    tempInput.state = cell;
                    break;
                case 16:
                    if ( cell == "" ) {
                        tempInput.age = 0;
                    } else {
                        tempInput.age = stoi(cell);
                    }
                    break;
                case 24:
                    tempInput.descCode = stoi(cell);
                    break;
                case 27:
                    tempInput.desc = cell;
                    break;
                case 28:
                    tempInput.valueStolen = stoi(cell);
                    break;
                case 29:
                    tempInput.valueRec = stoi(cell);
                    break;
            }
        }

        dataSet.push_back(tempInput);        

    }

    // Testing output TODO: remove
    cout << dataSet[0].year << ", " << dataSet[0].age << ", " << dataSet[0].valueStolen << ", " << dataSet[0].valueRec << ", " << dataSet[0].descCode << ", " << dataSet[0].agency << ", " << dataSet[0].state << ", " << dataSet[0].desc << "\n";

    // // Testing Sorting TODO: remove
    // for ( unsigned int i = 0; i < 1; i++) {
    //     Crime temp;
    //     temp.age = rand()*999;
    //     dataSet.push_back(temp);
    // }

    // Menu loop
    string inputString="";
    while ( inputString != "exit" ) {
        cin >> inputString;

        radixSort(&dataSet, 1);

        for (auto item : dataSet) {
            cout << item.age << ", ";
        }
        cout << "\n";

        // FIXME: Implement menu
    }

    input.close();


    return 0;
}