#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    // The known final sorted and transformed result (expected 17-byte answer)
    std::vector<uint8_t> hexValues = {
        0x58, 0x58, 0x5B, 0x5B, 0x5A, 0x5A, 0x5F, 0x5F,
        0x51, 0x5E, 0x5E, 0x51, 0x50, 0x50, 0x55, 0x54,
        0x54, 0x57, 0x49, 0x4C, 0x4B, 0x4D, 0x4D, 0x43,
        0x4F, 0x4F, 0x40, 0x48, 0x43
    };

    std::swap(hexValues[19], hexValues[27]);
    std::swap(hexValues[23], hexValues[27]);

    // Step 1: Reverse the second XOR transformation
    for (size_t i = 0; i < hexValues.size(); i++) {
        hexValues[i] ^= 0x39;
    }
    std::swap(hexValues[8], hexValues[10]);



    // Output the resulting array, which is the sorted original input
    std::cout << "Sorted original input (after reversing XOR transformations): ";
    for (const auto &val : hexValues) {
        //std::cout << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)val << " ";
        std::cout << (char)val;
    }
    std::cout << std::endl;

    return 0;
}

/*
python -c 'import sys; sys.stdout.buffer.write(b"\x61\x62\x63\x63\x64\x68\x69\x6B\x6E\x70\x70\x72\x72\x73\x73\x74\x77")'


*/