#ifndef PLUGBOARD_H
#define PLUGBOARD_H

// Plugboard class creates mapping to get input and give out output according to given map file
class Plugboard{
private:
    int list_input_number[52];          // list to hold plugboard parameters
    int number_input;                   // number of parameters in plugboard
public:
    Plugboard(char* map_plugboard);
    int mapToPlugboard(int single_int);  // function to map input/output with plugboard
};

#endif
