#include <fstream>
#include "reflector.h"

Reflector::Reflector( char* map_reflector): number_input(0){
    std::ifstream in_stream(map_reflector);
    int n;
    while(in_stream >> n>>std::ws )
        list_input_number[number_input++] =n;

    in_stream.close();
}

int Reflector::mapToReflector(int single_int){
    for(int i =0 ; i < number_input ; ++i){
        if((single_int == list_input_number[i]) && (i%2==0))
            return list_input_number[i+1];
        if((single_int == list_input_number[i]) && (i%2!=0))
            return list_input_number[i-1];
    }
    return single_int;
}
