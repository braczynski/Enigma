//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#include <iostream>
#include <string>
#include "enigma_custom.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

enigma_custom::enigma_custom(std::vector<rotor> rotors, reflector reflector, plugboard plugboard)
    :   rotors_(std::move(rotors)),
    reflector_(std::move(reflector)),
    plugboard_(std::move(plugboard)) {}

void enigma_custom::rotor_revolution() {
    rotors_[0].rev_the_rotor();

    for(int i = 1;i < rotors_.size(); i++ ) {
        if (rotors_[i-1].information_to_next_rotor_to_rev() == true) {
            rotors_[i].rev_the_rotor();
        }
    }
}

void enigma_custom::rotors_encrypt(char &letter_encrypted) const {
    for(int i = 0;i < rotors_.size(); i++ ) {
        letter_encrypted = rotors_[i].encrypt_letter(letter_encrypted);
    }
}

void enigma_custom::rotors_reflect_back(char &letter_encrypted) const {
    for(int i = rotors_.size()-1;i >= 0; i--) {
        letter_encrypted = rotors_[i].reflect_back(letter_encrypted);
    }
};

char enigma_custom::encrypt_the_letter(char letter) {

    rotor_revolution();

    char letter_encrypted = plugboard_.encrypt_the_letter(letter);

    rotors_encrypt(letter_encrypted);

    letter_encrypted = reflector_.encrypt_the_letter(letter_encrypted);

    rotors_reflect_back(letter_encrypted);

    letter_encrypted = plugboard_.encrypt_the_letter(letter_encrypted);

    return letter_encrypted;
};

//Encode and Decode
std::string enigma_custom::encrypt_the_message(std::string message) {
    std::string message_encrypted;
    for (const char letter: message) {
        if (letter >= 'A' && letter <= 'Z') {
            message_encrypted.push_back(encrypt_the_letter(letter));
        } else {
            message_encrypted.push_back(letter);
        }
    }

    return message_encrypted;
};
