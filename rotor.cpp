#include <fstream>
#include "rotor.h"

Rotor::Rotor( char* rotor_file,int rotor_pos_)
    :rotor_pos(rotor_pos_){

    std::ifstream in_file_rotor(rotor_file);
    int n, i =0;
    while(in_file_rotor >> n>> std::ws ){
        if(i < 26){
            list_rotor_fwd[i] = n;
            list_rotor_bwd[n] = i;
        }else if(i>= 26){
            list_notch[i-26] = n;
        }
        i++;
	      number_notch = i-26;
    }
    in_file_rotor.close();
}

int Rotor::getRotorPos(){
    return rotor_pos;
}

int Rotor::mod(int input){
    return (input+26)%26;
}

int Rotor::mapToRotor_fwd(int input){
    return list_rotor_fwd[input];
}

int Rotor::mapToRotor_bwd(int input){
    return list_rotor_bwd[input];
}

void Rotor::rotate(){
    rotor_pos = mod(rotor_pos+1);
}

// Need to have for loop to check rotor with many notches
bool Rotor::hasFullyRotated(int rot_pos){
    for(int i =0; i < number_notch ; i++){
        if(rot_pos == list_notch[i])
            return true;
    }
    return false;
}
