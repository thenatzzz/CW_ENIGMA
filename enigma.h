#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

/* Enigma class manages to do encryption and error checking by calling other components

   Encryption is done single character by character then printing out

   Constuctor of Enigma class manages to create rotors according to arguments given by user
   and feed component files into component's constructor as to build diffent mappings  */
class Enigma{
private:
    int rotor_number;           // number of rotor in Enigma machine
    std::vector<Rotor*> rotor;  // vector to store pointer to Rotor
    Plugboard plugboard;
    Reflector reflector;
    int number_notch;           // number of notch got from rot.pos file which sometimes does not match number of rotor
    int rotor_pos[100];         // list to store rotor starting position
public:
    Enigma(int argc,char* plugboard_file,char* reflector_file,std::vector<char*> rotor_file,char* rotor_pos_file);
    ~Enigma();
    int mod(int input);                     // function to avoid negative number when dealing with range of number
    char encryptMessage(char single_char);  // function to encrypt single character then print out
    void rotateRotor();                     // function to update rotor position (rightmost rotor always rotates)
    int charToInt(char c);                  // function to turn single character to single integer
    char intToChar(int i);                  // function to turn single integer to single character
    bool isNumeric(std::string input_string);            // function to check whether single string is numeric or not
    int errorCheckPlugboard(char* plugboard_file);       // function to check all errors in plugboard file
    int errorCheckRotor(std::vector<char*> rotor_file);  // function to check all errors in rotor file
    int errorCheckReflector(char* reflector_file);       // function to check all errors in reflector file
    int errorCheckPosRotor(char* position_file);         // function to check all errors in rotor starting position file
    int errorChecking(char* plugboard_file,std::vector<char*> rotor_file,char* reflector_file,char* position_file);
};

#endif
