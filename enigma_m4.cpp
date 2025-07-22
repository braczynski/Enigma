//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#include <iostream>
#include <string>
#include "enigma_m4.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

enigma_m4::enigma_m4(rotor rotor_first, rotor rotor_second, rotor rotor_third, rotor rotor_fourth, reflector reflector, plugboard plugboard)
    :   rotor_first_(std::move(rotor_first)),
    rotor_second_(std::move(rotor_second)),
    rotor_third_(std::move(rotor_third)),
    rotor_fourth_(std::move(rotor_fourth)),
    reflector_(std::move(reflector)),
    plugboard_(std::move(plugboard)) {}

void enigma_m4::rotor_revolution() {
    rotor_first_.rev_the_rotor();

    if (rotor_first_.information_to_next_rotor_to_rev() == true) {
        rotor_second_.rev_the_rotor();
    }

    if (rotor_second_.information_to_next_rotor_to_rev() == true) {
        rotor_third_.rev_the_rotor();
    }

    //fourth doesn't revolution
}

void enigma_m4::rotors_encrypt(char &letter_encrypted) const {
    letter_encrypted = rotor_first_.encrypt_letter(letter_encrypted);
    letter_encrypted = rotor_second_.encrypt_letter(letter_encrypted);
    letter_encrypted = rotor_third_.encrypt_letter(letter_encrypted);
    letter_encrypted = rotor_fourth_.encrypt_letter(letter_encrypted);
}

void enigma_m4::rotors_reflect_back(char &letter_encrypted) const {
    letter_encrypted = rotor_fourth_.reflect_back(letter_encrypted);
    letter_encrypted = rotor_third_.reflect_back(letter_encrypted);
    letter_encrypted = rotor_second_.reflect_back(letter_encrypted);
    letter_encrypted = rotor_first_.reflect_back(letter_encrypted);
};

char enigma_m4::encrypt_the_letter(char letter) {

    rotor_revolution();

    char letter_encrypted = plugboard_.encrypt_the_letter(letter);

    rotors_encrypt(letter_encrypted);

    letter_encrypted = reflector_.encrypt_the_letter(letter_encrypted);

    rotors_reflect_back(letter_encrypted);

    letter_encrypted = plugboard_.encrypt_the_letter(letter_encrypted);

    return letter_encrypted;
};

//Encode and Decode
std::string enigma_m4::encrypt_the_message(std::string message) {
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
