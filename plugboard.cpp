//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#include <iostream>
#include "plugboard.h"

plugboard::plugboard(std::vector<char> combination) :
    pair_(std::move(combination)) {}

void plugboard::print_pair() {
    char letter = 'A';

    for (char i : pair_) {
        if (i != 0) {
            std::cout << letter << "->" << i << " ";

        } else {
            std::cout << letter << "->" << letter << " ";
        }

        letter++;
    }

    std::cout << std::endl;
};

char plugboard::encrypt_the_letter(const char letter) const {
    char LetterEncrypted;

    if (pair_[letter - 'A'] != 0) {
        LetterEncrypted = pair_[letter - 'A'];
    } else {
        LetterEncrypted = letter;
    }

    return LetterEncrypted;
};

void plugboard::print_information() {
    std::cout << "Information about Plugboard" << std::endl;
    std::cout << "Pair is :";

    print_pair();
};