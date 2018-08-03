#ifndef REFLECTOR_H
#define REFLECTOR_H

// Reflector class creates mapping to get input and give out output according to given map file
class Reflector{
private:
    int number_input;           // list to hold reflector parameters
    int list_input_number[26];  // number of parameters in reflector
public:
    Reflector( char* map_reflector);
    int mapToReflector(int single_int); // function to map input/output with reflector
};

#endif
