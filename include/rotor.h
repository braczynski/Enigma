//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#ifndef ROTOR_H
#define ROTOR_H

#include <vector>

#define ALPHABET_LENGTH 26

class rotor {
private:
    int notch_position_ = 0, rotor_position_ = 0, ring_position_ = 0;
    std::vector<char> combination_;
    bool rev_next_rotor_ = false;

    void print_combination();

    bool rotor_rotation();

public:
    rotor(int initial_position_rotor, int notch_position_on_rotor, int initial_ring_position, std::vector<char> initial_combination);

    void print_information();

    [[nodiscard]] char encrypt_letter(char letter) const;

    [[nodiscard]] char reflect_back(char letter) const;

    void rev_the_rotor();

    [[nodiscard]] bool information_to_next_rotor_to_rev() const;
};

#endif //ROTOR_H
