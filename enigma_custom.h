#ifndef ENIGMA_CUSTOM_H
#define ENIGMA_CUSTOM_H

#include <vector>
#include <string>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

class enigma_custom
{
private:
    std::vector<rotor> rotors_;
    reflector reflector_;
    plugboard plugboard_;

    void rotor_revolution();

    void rotors_encrypt(char &letter_encrypted) const;
    void rotors_reflect_back(char &letter_encrypted) const;

    char encrypt_the_letter(char letter);
public:
    enigma_custom(std::vector<rotor> rotors, reflector reflector, plugboard plugboard);

    //Encode and Decode
    std::string encrypt_the_message(std::string message);
};

#endif //ENIGMA_H
