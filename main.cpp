#include <iostream>
#include <vector>
#include <string>

#include "enigma.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    const std::vector<std::vector<char>> historical_rotors = {
        // Rotor I
        {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O',
            'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'},

        // Rotor II
        {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H','W',
            'T','M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'},

        // Rotor III
        {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z',
            'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'},

        // Rotor IV
        {'E', 'S', 'O', 'V', 'P', 'Z', 'J', 'A', 'Y', 'Q', 'U', 'I', 'R',
            'H', 'X', 'L', 'N', 'F', 'T', 'G', 'K', 'D', 'C', 'M', 'W', 'B'},

        // Rotor V
        {'V', 'Z', 'B', 'R', 'G', 'I', 'T', 'Y', 'U', 'P', 'S', 'D', 'N',
            'H', 'L', 'X', 'A', 'W', 'M', 'J', 'Q', 'O', 'F', 'E', 'C', 'K'}
    };

    const std::vector<std::vector<char>> historical_refrector = {
        // Version B
        {'Y', 'R', 'U', 'H', 'Q', 'S', 'L', 'D', 'P', 'X', 'N', 'G', 'O',
            'K', 'M', 'I', 'E', 'B', 'F', 'Z', 'C', 'W', 'V', 'J', 'A', 'T'},

        // Version C Kriegsmarine
        {'F', 'V', 'P', 'J', 'I', 'A', 'O', 'Y', 'E', 'D', 'R', 'Z','X',
            'W','G', 'C', 'T', 'K', 'U', 'Q', 'S', 'B', 'N', 'M', 'H', 'L'},
    };
    const std::vector<char> pair = {
        // Rotor I
        {0, 'X', 0, 0, 0, 'R', 'U', 0, 0, 'Z', 'W', 0, 0,
            0, 0, 0, 0, 'F', 0, 0, 'G', 0, 'K', 'B', 0, 'J'},
    };

    rotor rotor_first(0, 14, 0,historical_rotors[0]);
    rotor rotor_second(0, 18, 0, historical_rotors[1]);
    rotor rotor_third(0, 23, 0, historical_rotors[2]);
    reflector reflector('B', historical_refrector[0]);
    plugboard plugboard(pair);
    enigma_m3 historical_enigma_m3(rotor_first, rotor_second, rotor_third, reflector, plugboard);

    historical_enigma_m3.print_information();

    std::cout << "Type Message" << std::endl;
    std::string message;
    std::getline(std::cin, message);
    //message = "HELLO WORLD IM ENIGMA";
    //message = "MRNCJ MXFJM EE SEAMCC";

    std::string message_encrypted = historical_enigma_m3.encrypt_the_message(message);

    std::cout << message_encrypted;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.