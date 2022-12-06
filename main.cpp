#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Crime.h"
#include "radix_sort.h"
#include "merge_sort.h"
#include "linear_search.h"

using namespace std;

int getNumInput(string menu, string prompt, int begin, int end) {
    string input;
    unsigned int output;
    bool parsable = false;

    while (!parsable) {
        cout << menu;
        cout << prompt;

        cin >> input;
        
        if ( input == "exit" ) {
            return -1;
        }

        try {
            output = stoi(input);
            if ( output >= begin && output <= end) {
                parsable = true;
            } else {
                cout << "Number not in Range (" << begin << "-" << end << ")\n\n";
            }
        } catch (exception) {
            cout << "Input not Parsable\n";
        }
    }
    return output;
}

int main() {
    
    // Open file
    ifstream input;
    input.open("CT_2013_2021.csv");
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
            string temp = line;

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
                    if ( cell == "" ) {
                        tempInput->year = 0;
                    } else {
                        tempInput->year = stoi(cell);
                    }
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
                    if ( cell == "" ) {
                        tempInput->descCode = 0;
                    } else {
                        tempInput->descCode = stoi(cell);
                    }
                    break;
                case 27:
                    tempInput->desc = cell;
                    break;
                case 28:
                    if ( cell == "" ) {
                        tempInput->valueStolen = 0;
                    } else {
                        tempInput->valueStolen = stoi(cell);
                    }
                    break;
                case 29:
                    if ( cell == "" ) {
                        tempInput->valueRec = 0;
                    } else {
                        tempInput->valueRec = stoi(cell);
                    }
                    break;
            }
        }

        dataSet.push_back(tempInput);
    }

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
    bool running = true;

    while ( running ) {

        cout << menu_title;
        int input = getNumInput(main_menu_options, input_prompt, 1, 3);
        if (input == -1) {
            running = false;
            continue;
        }

        int sortInput = 1;
        int characteristicInput = 1;
        auto start = chrono::high_resolution_clock::now();
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        switch (input) {

            // Sort Data
            case 1:
                // Select sorting algorithm
                inputString = "";
                while (inputString != "y") { // Keep looping the sort menu if user does not confirm their choices
                    
                    sortInput = getNumInput(sorting_menu, input_prompt, 1, 2);

                    characteristicInput = getNumInput(characteristic_menu, input_prompt, 1, 5);

                    cout << "\n";
                    // Print back the selected options and ask to confirm the choices
                    if (sortInput == 1) {
                        cout << "Sort: Radix" << endl;
                    } else if (sortInput == 2) {
                        cout << "Sort: Merge" << endl;
                    }

                    switch (characteristicInput) { // Print back the selected characteristic
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

                    cout << "Are these choices correct? (y/n) ";
                    cin >> inputString;
                }

                cout << "\n";
                start = chrono::high_resolution_clock::now();
                if (sortInput == 1) {
                    radixSort(&dataSet, characteristicInput);
                } else if (sortInput == 2) {
                    mergeSort(&dataSet, characteristicInput);
                }
                stop = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>( stop - start );
                
                if (sortInput == 1) {
                    cout << "Radix Sort completed in (microseconds): " << duration.count() << endl;
                } else if (sortInput == 2) {
                    cout << "Merge Sort completed in (microseconds): " << duration.count() << endl;
                }
                
                cout << "We can now search the data in log(n) time!\n\n";
                break;

            // Search Data
            case 2:
                // TODO: Create searching menu
                break;

            case 3:

                cout << "\n";
                characteristicInput = getNumInput(characteristic_menu, input_prompt, 1, 5);

                // Measure merge sort time
                auto mergeStart = chrono::high_resolution_clock::now();
                mergeSort(&dataSet, characteristicInput);
                auto mergeStop = chrono::high_resolution_clock::now();
                auto mergeDuration = chrono::duration_cast<chrono::microseconds>(mergeStop - mergeStart);

                auto radixStart = chrono::high_resolution_clock::now();
                radixSort(&dataSet, characteristicInput);
                auto radixStop = chrono::high_resolution_clock::now();
                auto radixDuration = chrono::duration_cast<chrono::microseconds>( radixStop - radixStart);

                cout << "Radix Sort (microseconds): " << radixDuration.count() << endl;
                cout << "Merge Sort (microseconds): " << mergeDuration.count() << endl << endl; // Added extra newline to sperate from Main Menu

                break;
        }

    }

    input.close();

    for ( unsigned int i = 0; i < dataSet.size(); i++ ){
        delete dataSet[i];
    }

    return 0;
}