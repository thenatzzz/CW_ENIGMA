#ifndef ROTOR_H
#define ROTOR_H

// Rotor class manages each rotor given user by creating mapping and updating position
class Rotor{
private:
    int list_rotor_fwd[26];      // list to store rotor parameter forward (rightmost to leftmost)
    int list_rotor_bwd[26];      // list to store rotor parameter reverse index from list_rotor_fwd
    int rotor_pos;               // current rotor starting position (it updates everytime rotor rotates)
    int number_notch;            // number of notch
    int list_notch[26];          // list to store position of notch
public:
    Rotor( char* rotor_file,int rotor_pos_);
    int getRotorPos();                  // function to get current starting position
    int mod(int input);                 // function to avoid negative number when dealing with range of number
    int mapToRotor_fwd(int input);      // function to get input from right rotor sending to next left rotor
    int mapToRotor_bwd(int input);      // function to get input from left rotor sending to next right rotor
    void rotate();                      // function to update current rotor starting position
    bool hasFullyRotated(int rot_pos);    // function to check whether rotor hits notch or not
};

#endif
