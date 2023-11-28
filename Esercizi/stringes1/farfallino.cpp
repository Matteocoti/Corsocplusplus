#include "farfallino.h"
#include <iostream>

std::string CodificaFarfallino(const std::string& input) {

    std::string output;
    std::string vowels("aeiouy");

    for (auto c:input) {
        output += c;
        if (vowels.find(c) != std::string::npos) {
            output += std::string{'f', c};
        }
    }

    return output;
}