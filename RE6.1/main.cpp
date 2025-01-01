#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    // The known final sorted and transformed result (expected 17-byte answer)
    std::vector<uint8_t> hexValues = {
        0xBC, 0x8A, 0xC6, 0xBE, 0x8C, 0xCD, 0xB4, 0x83,
        0xCB, 0xAD, 0x98, 0xD7, 0xAF, 0x9B, 0xD6, 0xA9, 0x9F
    };

    // Step 1: Reverse the second XOR transformation
    for (size_t i = 0; i < hexValues.size(); i++) {
        if (i % 3 == 2) {
            hexValues[i] ^= 0x8F;
        } else if (i % 3 == 1) {
            hexValues[i] ^= 0x04;
        } else {
            hexValues[i] ^= 0xA7;
        }
    }

    // Step 2: Reverse the first XOR transformation
    for (size_t i = 0; i < hexValues.size(); i++) {
        if (i % 3 == 2) {
            hexValues[i] ^= 0x2A;
        } else if (i % 3 == 1) {
            hexValues[i] ^= 0xEC;
        } else {
            hexValues[i] ^= 0x7A;
        }
    }

    // Output the resulting array, which is the sorted original input
    std::cout << "Sorted original input (after reversing XOR transformations): ";
    for (const auto &val : hexValues) {
        std::cout << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)val << " ";
        //std::cout << (char)val;
    }
    std::cout << std::endl;

    return 0;
}

/*
python -c 'import sys; sys.stdout.buffer.write(b"\x61\x62\x63\x63\x64\x68\x69\x6B\x6E\x70\x70\x72\x72\x73\x73\x74\x77")'


*/