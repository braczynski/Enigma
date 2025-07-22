//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#ifndef ENIGMA_M4_H
#define ENIGMA_M4_H

#include <string>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

class enigma_m4 {
private:
    rotor rotor_first_;
    rotor rotor_second_;
    rotor rotor_third_;
    rotor rotor_fourth_;
    reflector reflector_;
    plugboard plugboard_;

    void rotor_revolution();

    void rotors_encrypt(char &letter_encrypted) const;
    void rotors_reflect_back(char &letter_encrypted) const;

    char encrypt_the_letter(char letter);
public:
    enigma_m4(rotor rotor_first, rotor rotor_second, rotor rotor_third, rotor rotor_fourth, reflector reflector, plugboard plugboard);

    //Encode and Decode
    std::string encrypt_the_message(std::string message);
};

#endif //ENIGMA_H
