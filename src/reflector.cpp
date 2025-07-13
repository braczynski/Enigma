//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#include <iostream>
#include "reflector.h"

reflector::reflector(char reflector_version, std::vector<char> reflector_combination)
    :   version_(reflector_version),
        combination_(std::move(reflector_combination)) {}

void reflector::print_combination() {
    char letter = 'A';

    for (const char i : combination_) {
        std::cout << letter << "->" << i << " ";
        letter++;
    }

    std::cout << std::endl;
};

char reflector::encrypt_the_letter(const char letter) const {
    const char letter_encrypted = combination_[letter - 'A'];

    return letter_encrypted;
};

void reflector::print_information() {
    std::cout << "Information about Reflector" << std::endl;
    std::cout << "Version = " << version_ << std::endl;
    std::cout << "Combination is :";

    print_combination();
};