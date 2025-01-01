#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>

int main() {
    std::vector<uint8_t> hexValues = {
        0x7a, 0x78, 0x78, 0x78, 0x77, 0x76, 0x76, 0x76, 
        0x76, 0x74, 0x74, 0x61, 0x6d, 0x73, 0x73, 0x73, 
        0x73, 0x64, 0x71, 0x71, 0x71, 0x70, 0x6e, 0x6e, 
        0x74, 0x6a, 0x6a, 0x6a, 0x69, 0x66, 0x66, 0x65, 
        0x72, 0x74, 0x61, 0x61
    };
    std::swap(hexValues[11], hexValues[33]);
    std::reverse(hexValues.begin(), hexValues.end());
    std::swap(hexValues[11], hexValues[23]);
    std::swap(hexValues[3], hexValues[18]);

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