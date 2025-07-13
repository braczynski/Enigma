//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>

class reflector {
private:
    char version_;
    std::vector<char> combination_;

    void print_combination();

public:
    reflector(char reflector_version, std::vector<char> reflector_combination);

    [[nodiscard]] char encrypt_the_letter(char letter) const;

    void print_information();

};

#endif //REFLECTOR_H
