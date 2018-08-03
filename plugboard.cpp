#include <fstream>
#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(char* map_plugboard):number_input(0){
    ifstream in_stream(map_plugboard);
    int n;
    while(in_stream >>n>>ws)
        list_input_number[number_input++] = n;
    in_stream.close();
}

int Plugboard::mapToPlugboard(int single_int){
    for(int i =0 ; i < number_input ; ++i){
        if((single_int == list_input_number[i]) && (i%2==0))
            return list_input_number[i+1];
        if((single_int == list_input_number[i]) && (i%2!=0))
            return list_input_number[i-1];
    }
    return single_int;
}
