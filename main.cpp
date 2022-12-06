#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Crime.h"
#include "radix_sort.h"
#include "merge_sort.h"
#include "menu.h"

using namespace std;

int main() {
    
    // Open file
    ifstream input;
    input.open("CT_2013_2021_reduced.csv");
    if ( !input.is_open() ) {
        cerr << "Error Opening File\n";
        return -1;
    }

    vector<Crime*> dataSet;

    string line;
    // Clears first line which contains column headers
    getline(input, line);

    // Reads data in from file
    while ( getline(input, line) ) {
        Crime* tempInput = new Crime;

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
                    tempInput->year = stoi(cell);
                    break;
                case 2:
                    tempInput->agency = cell;
                    break;
                case 6:
                    tempInput->state = cell;
                    break;
                case 16:
                    if ( cell == "" ) {
                        tempInput->age = 0;
                    } else {
                        tempInput->age = stoi(cell);
                    }
                    break;
                case 24:
                    tempInput->descCode = stoi(cell);
                    break;
                case 27:
                    tempInput->desc = cell;
                    break;
                case 28:
                    tempInput->valueStolen = stoi(cell);
                    break;
                case 29:
                    tempInput->valueRec = stoi(cell);
                    break;
            }
        }

        dataSet.push_back(tempInput);

    }

//    // Testing Adding Random Values TODO: remove
//    for ( unsigned int i = 0; i < 20; i++) {
//        Crime* temp = new Crime;
//        temp->age = rand()%999;
//        temp->valueStolen = rand()%999;
//        dataSet.push_back(temp);
//    }
//
//    // Testing Sorting TODO: remove
//    for (auto item : dataSet) {
//        cout << item->age << ", ";
//    }
//    cout << "\n";
//    mergeSort(&dataSet, 1);
//    for (auto item : dataSet) {
//        cout << item->age << ", ";
//    }
//    cout << "\n";
//    radixSort(&dataSet, 2);
//    for (auto item : dataSet) {
//        cout << item->valueStolen << ", ";
//    }
    cout << "\n";

    // Menu objects
    static const char *const menu_title =
            " __  __              \n"
            "|  \\/  |___ _ _ _  _ \n"
            "| |\\/| / -_) ' \\ || |\n"
            "|_|  |_\\___|_||_\\_,_|\n"
            "======================\n";

    static const char *const main_menu_options =
            "(1) Sort Data\n"
            "(2) Search Data\n"
            "(3) Sort Comparison\n"
            "(exit)\n\n"
            ;

    static const char *const input_prompt =
            "Input: "
            ;

    char wheel[] = {'\\','|','/', '-'}; // For loading animation

    static const char *const sorting_menu =
            "\n"
            "+--------------------+\n"
            "| Sorting Algorithms |\n"
            "+--------------------+\n"
            "| (1) Radix          |\n"
            "| (2) Merge          |\n"
            "+--------------------+\n"
            ;

    static const char *const characteristic_menu =
            "\n"
            "+----------------------+\n"
            "|   Characteristics    |\n"
            "+----------------------+\n"
            "| (1) Year             |\n"
            "| (2) Offender Age     |\n"
            "| (3) Value Stolen     |\n"
            "| (4) Value Recovered  |\n"
            "| (5) Description Code |\n"
            "+----------------------+\n"
            ;

    // Menu loop
    string inputString="";

    while ( inputString != "exit" ) {
        // FIXME: Implement menu
        cout << menu_title;
        cout << main_menu_options;
        cout << input_prompt;
        cin >> inputString;

        // For testing
        if (inputString == "exit") {
            continue;
        }

        string sortInput = "";
        string characteristicInput = "";
        switch(stoi(inputString)) {

            // Sort Data
            case 1:
                // TODO: Create sorting menu
                // Select sorting algorithm
                while (inputString != "y") { // Keep looping the sort menu if user does not confirm their choices
                    cout << sorting_menu;
                    cout << input_prompt;
                    cin >> sortInput;

                    cout << characteristic_menu;
                    cout << input_prompt;
                    cin >> characteristicInput;

                    cout << "\n";
                    // Print back the selected options and ask to confirm the choices
                    if (sortInput == "1") {
                        cout << "Sort: Radix" << endl;
                    } else if (sortInput == "2") {
                        cout << "Sort: Merge" << endl;
                    }

                    switch (stoi(characteristicInput)) { // Print back the selected characteristic
                        case 1:
                            cout << "Characteristic: Year" << endl;
                            break;

                        case 2:
                            cout << "Characteristic: Offender Age" << endl;
                            break;

                        case 3:
                            cout << "Characteristic: Value Stolen" << endl;
                            break;

                        case 4:
                            cout << "Characteristic: Value Recovered" << endl;
                            break;

                        case 5:
                            cout << "Characteristic: Description Code" << endl;
                            break;
                    }

                    cout << "\n";

                    cout << "Are these choices correct? (Y/n) ";
                    cin >> inputString;
                }

                cout << "\n";
                cout << "We can now search the data in log(n) time!\n\n";
                break;

            // Search Data
            case 2:
                // TODO: Create searching menu
                break;

            case 3:

                cout << "\n";

                // Measure merge sort time
                auto mergeStart = chrono::high_resolution_clock::now();
                mergeSort(&dataSet, 2);
                auto mergeStop = chrono::high_resolution_clock::now();
                auto mergeDuration = chrono::duration_cast<chrono::microseconds>(mergeStop - mergeStart);

                auto radixStart = chrono::high_resolution_clock::now();
                radixSort(&dataSet, 1);
                auto radixStop = chrono::high_resolution_clock::now();
                auto radixDuration = chrono::duration_cast<chrono::microseconds>( radixStop - radixStart);

                cout << "Radix Sort (microseconds): " << radixDuration.count() << endl;
                cout << "Merge Sort (microseconds): " << mergeDuration.count() << "\n" << endl; // Added extra newline to sperate from Main Menu
        }

    }

    input.close();

    for ( unsigned int i = 0; i < dataSet.size(); i++ ){
        delete dataSet[i];
    }

    return 0;
}