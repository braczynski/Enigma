//
// Created by Bartłomiej Raczyński on 13.07.2025.
//

#include "char_operation.h"

int char_to_int(const char letter) {
    if (letter >= 'A' && letter <= 'Z')
        return letter  - 'A';
    if (letter  >= 'a' && letter  <= 'z')
        return letter  - 'a';
    return -1;
}

char int_to_char(const int letter) {
    return static_cast<char>(letter + 'A');
}
