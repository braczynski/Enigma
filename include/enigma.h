//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#ifndef ENIGMA_H
#define ENIGMA_H

#include <string>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

class enigma_m3 {
private:
    rotor rotor_first_;
    rotor rotor_second_;
    rotor rotor_third_;
    reflector reflector_;
    plugboard plugboard_;

    void rotor_revolution();

    void rotors_encrypt(char &letter_encrypted) const;
    void rotors_reflect_back(char &letter_encrypted) const;

    char encrypt_the_letter(char letter);
public:
    enigma_m3(rotor rotor_first, rotor rotor_second, rotor rotor_third, reflector reflector, plugboard plugboard);

    //Encode and Decode
    std::string encrypt_the_message(std::string message);

    void print_information();
};

#endif //ENIGMA_H
