#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include "enigma.h"
#include "errors.h"

using namespace std;

const int MAX_NUM_LETTER = 26;

Enigma::Enigma(int argc,  char* plugboard_file,char* reflector_file, vector<char*> rotor_file,  char* rotor_pos_file)
    :plugboard(plugboard_file), reflector(reflector_file){

    ifstream in_file_pos(rotor_pos_file);
    int p, i =0;
    while(in_file_pos >> p >> ws){
        rotor_pos[i] = p;
        i++;
        number_notch = i;
    }
    in_file_pos.close();

    if(argc<=3){
        rotor_number = 0;
     }else if(argc >= 5){
        rotor_number = argc-4;

        // build new Rotor pointer and push each in vector
        for(int i = 0; i< rotor_number; ++i)
            rotor.push_back(new Rotor(rotor_file[i],rotor_pos[i]));
     }
}

Enigma::~Enigma(){
    if(rotor_number ==0)
        return;
    else
        for(int i = 0 ; i < rotor_number;i++)
            delete rotor[i];
}

int Enigma::mod(int input){
    return (input+MAX_NUM_LETTER)%MAX_NUM_LETTER;
}

char Enigma::encryptMessage(char single_char){

    int single_int = charToInt(single_char);

    single_int = plugboard.mapToPlugboard(single_int);

    if(rotor_number > 0){
        rotateRotor();

        // Message comes in from rightmost rotor to leftmost rotor
        for(int i = rotor_number-1; i>= 0; i--){

	           single_int = rotor[i]->mod(single_int+rotor[i]->getRotorPos());
	           single_int = rotor[i]->mapToRotor_fwd(single_int);
	           single_int = rotor[i]->mod(single_int-rotor[i]->getRotorPos());
	      }
    }

    single_int = reflector.mapToReflector(single_int);

    if(rotor_number > 0){

        // Messgage comes out from leftmost rotor to rightmost rotor
        for(int i = 0; i < rotor_number; i++){

	           single_int = rotor[i]->mod(single_int+rotor[i]->getRotorPos());
	           single_int = rotor[i]->mapToRotor_bwd(single_int);
	           single_int = rotor[i]->mod(single_int-rotor[i]->getRotorPos());
        }
    }
    single_int = plugboard.mapToPlugboard(single_int);

    return intToChar(single_int);
}

// rightmost rotor always turns ; if else statement to help check whether starting position hits notch or not
// also if else statement with rotor_aldy_turn fn helps to make sure that middle rotors will not keep toggling left rotor
void Enigma::rotateRotor(){
    // First rotor always rotates.
    bool rotor_aldy_turn[rotor_number] = {0};
    for(int i  = rotor_number-1; i >= 0; i--){
        if(i == (rotor_number-1)){
             rotor[i]->rotate();
             rotor_aldy_turn[i] = true;
        }else if( (rotor_aldy_turn[i+1]) && (rotor[i+1]->hasFullyRotated(mod(rotor[i+1]->getRotorPos())))){
             rotor[i]->rotate();
             rotor_aldy_turn[i] = true;
        }
    }
}

int Enigma::charToInt(char c){
    return static_cast<int>(c - 'A');
}

char Enigma::intToChar(int i){
    return static_cast<char>(i+65);
}

bool Enigma::isNumeric(string input_string){
    for(int i =0; i< int(input_string.length());i++)
        if(!isdigit(input_string[i]))
            return 0;
    return 1;
}

int Enigma::errorCheckPlugboard(char* plugboard_file){

//################# check for non-numeric character ###########################
    ifstream in_stream1(plugboard_file);
    string input_string;
    if(!in_stream1) // check for file opening
        return 11;

    while(in_stream1 >> input_string>> ws)
        if(!isNumeric(input_string))
            return 4;
    in_stream1.close();

//############### check for self-contact, valid index ##########################
    ifstream in_stream2(plugboard_file);
    int list_input_number[MAX_NUM_LETTER],n, number_input = 0, number_input_=0;
    while(in_stream2 >>n>>ws){
        //check index
        if(n<0 || n > MAX_NUM_LETTER-1)
            return 3;

        //check number input contacts to itself or not
        if(number_input < MAX_NUM_LETTER){
            for(int j =0 ; j < number_input; j++)
                if(list_input_number[j] == n)
                    return 5;
        }

        list_input_number[number_input_++] = n;
        number_input = number_input_;
    }
    in_stream2.close();


//################ check number of parameters is odd or not, and is in valid range or not
    if((number_input%2)!= 0 || number_input > MAX_NUM_LETTER)
        return 6;

    return 0;
}

int Enigma::errorCheckRotor(vector<char*> rotor_file){

    //Big Loop : check rotor by rotor
    for(int rotor_th = rotor_number-1 ; rotor_th >=0 ; --rotor_th){

//################# check for non-numeric character ###########################
        ifstream in_stream1(rotor_file[rotor_th]);
        string input_string;
        if(!in_stream1) // check for file opening
            return 11;

        while(in_stream1 >> input_string>> ws){
            if(!isNumeric(input_string))
                return 13;
        }
        in_stream1.close();

//############### check for self-contact, valid index ##########################
        ifstream in_stream2(rotor_file[rotor_th]);
        int list_rotor[MAX_NUM_LETTER], n, number_para = 0, quantity_num_rotor = 0;
        while(in_stream2 >> n>> ws ){
            //check index
            if(n<0 || n > MAX_NUM_LETTER-1)
                return 3;

            //check number input contacts to itself or not
            if(number_para < MAX_NUM_LETTER){
                for(int j =0 ; j < number_para; j++)
                    if(list_rotor[j] == n)
                        return 7;
            }

            list_rotor[number_para++] = n;
            quantity_num_rotor = number_para;
        }
        in_stream2.close();

//############### check for number of parameters is enough or not ##############
        if(quantity_num_rotor < MAX_NUM_LETTER)
            return 14;

    }
    return 0;
}

int Enigma::errorCheckReflector(char* reflector_file){
//################# check for non-numeric character ###########################
   ifstream in_stream1(reflector_file);
   string input_string;
   if(!in_stream1)  // check for file opening
      return 11;

   while(in_stream1 >> input_string>> ws){
      if(!isNumeric(input_string))
          return 2;
    }
    in_stream1.close();

//############### check for self-contact, valid index ##########################
    ifstream in_stream2(reflector_file);
    int list_input_number[MAX_NUM_LETTER], n , number_input = 0, number_input_=0;
    while(in_stream2 >>n>>ws){
        //check index
        if(n<0 || n > MAX_NUM_LETTER-1)
            return 3;

        //check number input contacts to itself or not
        if(number_input_ < MAX_NUM_LETTER){
            for(int j =0 ; j < number_input_; j++)
                if(list_input_number[j] == n)
                    return 9;
        }

        list_input_number[number_input_++] = n;
	      number_input = number_input_;
    }
    in_stream2.close();

//############### check for number of parameters and parameter #################
    //check number of parameters is odd or not, and is in valid range or not
    if(number_input > MAX_NUM_LETTER || (number_input%2)!=0 )
        return 12;

    //check number of parameters is enough or not
    if(number_input < MAX_NUM_LETTER){
        return 10;

    }
    return 0;
}

int Enigma::errorCheckPosRotor(char* position_file){
    ifstream in_stream(position_file);
    if(!in_stream) // check for file opening
       return 11;

//################ check if index valid or not #################################
    int p, i =0 , num_notch = 0;
    while(in_stream >> p >> ws){

        if(p<0 || p > MAX_NUM_LETTER-1)
            return 3;

	      i++;
        num_notch = i;
    }
    in_stream.close();

//################# check for non-numeric character ###########################
    ifstream in_stream2(position_file);
    string input_string;
    while(in_stream2 >> input_string>> ws){
        if(!isNumeric(input_string))
            return 15;
    }
    in_stream2.close();

//################# check for starting position ###############################
    if(number_notch != num_notch)
        return 8;

    return 0;
  }

// Error checking function to check error in Enigma components ( file by file and-
// component by component) 
int Enigma::errorChecking(char* plugboard_file,vector<char*> rotor_file,char* reflector_file,char* position_file){

    int result = 1;

    //check error from components to components
    if(result != 0){
        result = errorCheckPlugboard(plugboard_file);
	      if(result != 0) return result;

        if(result == 0){
            result= errorCheckRotor(rotor_file);
	          if(result != 0) return result;

            if(result == 0){
                result = errorCheckPosRotor(position_file);
		            if(result != 0) return result;

                if(result == 0){
                    result= errorCheckReflector(reflector_file);
		                if(result != 0)
			                 return result;
		                else
			                 return 0;
                }
            }
        }

    }
    return 0;
}
