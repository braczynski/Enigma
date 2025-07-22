//
// Created by Bartłomiej Raczyński on 13.07.2025.
//
#include <iostream>
#include <vector>
#include "rotor.h"
#include "char_operation.h"

rotor::rotor(const int initial_position_rotor, const int notch_position_on_rotor, const int initial_ring_position, std::vector<char> initial_combination)
    : notch_position_(notch_position_on_rotor),
      rotor_position_(initial_position_rotor),
      ring_position_(initial_ring_position),
      combination_(std::move(initial_combination)) {}

rotor::rotor(const int initial_position_rotor, const int notch_position_on_rotor, const int notch_position_on_rotor_2, const int initial_ring_position, std::vector<char> initial_combination)
    : notch_position_(notch_position_on_rotor),
    notch_position_2_(notch_position_on_rotor_2),
    rotor_position_(initial_position_rotor),
    ring_position_(initial_ring_position),
    combination_(std::move(initial_combination)) {}

void rotor::print_combination() {
    char letter = 'A';

    for (const char i : combination_) {
        std::cout << letter << "->" << i << " ";
        letter++;
    }

    std::cout << std::endl;
}

bool rotor::rotor_rotation() {

    if (rotor_position_ == notch_position_ || rotor_position_ == notch_position_2_) {
        rev_next_rotor_ = true;
    } else {
        rev_next_rotor_ = false;
    }

    if (rotor_position_ < ALPHABET_LENGTH) {
        rotor_position_++;
    } else {
        rotor_position_ = 0;
    }

    return rev_next_rotor_;
}

void rotor::print_information() {
        std::cout << "Information about Rotor" << std::endl;
        std::cout << "Initial Position: " << rotor_position_ << std::endl;
        std::cout << "NotchPosition = " << notch_position_ << std::endl;
        std::cout << "Combination is :";

        print_combination();
}

char rotor::encrypt_letter(const char letter) const {
    const int offset = rotor_position_ + ring_position_;
    char letter_encrypted = combination_[(char_to_int(letter) + offset) % ALPHABET_LENGTH];

    const int encryption = (char_to_int(letter_encrypted) - offset + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    //add ALPHABET_LENGTH because (i - offset) may be negative

    letter_encrypted = int_to_char(encryption);

    return letter_encrypted;
}

char rotor::reflect_back(char letter) const {
    const int offset = rotor_position_ + ring_position_;

    const int encryption = (char_to_int(letter) + offset) % ALPHABET_LENGTH;

    letter = int_to_char(encryption);

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        if (combination_[i] == letter) {
            return int_to_char(((i - offset) + ALPHABET_LENGTH) % ALPHABET_LENGTH);
            //add ALPHABET_LENGTH because (i - offset) may be negative
        }
    }

    return 0;
}

void rotor::rev_the_rotor() {
    rotor_rotation();
}

bool rotor::information_to_next_rotor_to_rev() const {
    return rev_next_rotor_;
}
