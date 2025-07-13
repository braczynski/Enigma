//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <vector>

class plugboard {
private:
    std::vector<char> pair_;

    void print_pair();

public:
    explicit plugboard(std::vector<char> combination);

    [[nodiscard]] char encrypt_the_letter(char letter) const;

    void print_information();

};

#endif //PLUGBOARD_H
