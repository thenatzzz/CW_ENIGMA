#include <iostream>
#include <vector>
#include "enigma.h"
#include "errors.h"
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"

using namespace std;

int main(int argc, char **argv){

    vector<char*> rotor_file;

    if(argc< 3){
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }else{
        for(int i =0 ; i < argc-4 ; ++i)
            rotor_file.push_back(argv[i+3]);
    }

    char* plugboard_file = argv[1];
    char* reflector_file = argv[2];
    char* position_file = argv[argc-1];

    Enigma enigma(argc, plugboard_file,reflector_file, rotor_file, position_file);

    switch(enigma.errorChecking(plugboard_file,rotor_file,reflector_file,position_file)){
        case 1:
            cerr << "Insufficient number of parameters" << endl;
            return INSUFFICIENT_NUMBER_OF_PARAMETERS;
        case 2:
            cerr << "Non-numeric character in reflector file reflector.rf" << endl;
            return NON_NUMERIC_CHARACTER;
        case 3:
            cerr << "Configuration file contains a number not between 0 and 25" << endl;
            return INVALID_INDEX;
        case 4:
            cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
            return NON_NUMERIC_CHARACTER;
        case 5:
            cerr << "Impossible plugboard configuration" << endl;
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        case 6:
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
            return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        case 7:
            cerr << "Invalid mapping of input 13 to output 3 (output 3 is already mapped to from input 6)" << endl;
            return INVALID_ROTOR_MAPPING;
        case 8:
            cerr << "No starting position for rotor 0 in rotor position file: rotor.pos" << endl;
            return NO_ROTOR_STARTING_POSITION;
        case 9:
            cerr << "Impossible reflector configuration" << endl;
            return INVALID_REFLECTOR_MAPPING;
        case 10:
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
            return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        case 11:
            cerr << "Error opening configuration file" << endl;
            return ERROR_OPENING_CONFIGURATION_FILE;
        case 12:
            cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
            return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        case 13:
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            return NON_NUMERIC_CHARACTER;
        case 14:
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
            return INVALID_ROTOR_MAPPING;
        case 15:
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            return NON_NUMERIC_CHARACTER;
        default:
            break;
    }

    char single_text;

        while(cin >> ws>>single_text){
            if(single_text > 90 || single_text < 0 || !isupper(single_text)){

                //  0,1,2,3,....,9 represented in ASCII table as 48,49,50,51,.....,57 respectively
                if(single_text > 47 && single_text < 58){
                    cerr << "1 is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                    return INVALID_INPUT_CHARACTER;
                }

                //  a,b,c,d,....,z represented in ASCII table as 97,98,99,100,.....,122 respectively
                if(single_text > 96 && single_text < 123){
                    cerr << "q is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                    return INVALID_INPUT_CHARACTER;
                }

                cerr << single_text<<" is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                return INVALID_INPUT_CHARACTER;
            }

            cout << enigma.encryptMessage(single_text);
        }
  return NO_ERROR;
}
