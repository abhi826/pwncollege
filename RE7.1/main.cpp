#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    std::vector<uint8_t> hexValues = {
        0x51, 0x0F, 0x4E, 0x17, 0x46, 0x13, 0x4D, 0x0A,
        0x56, 0x0B, 0x4F, 0x13, 0x51, 0x04, 0x5E, 0x12,
        0x4B, 0x1E, 0x4A, 0x1F, 0x55, 0x13, 0x5C, 0x12,
        0x40, 0x11, 0x52
    };

    for(int i=0;i<hexValues.size();i++){
        if(i%2==1){
            hexValues[i] ^= 0x7D;

        }
        else{
            hexValues[i] ^= 0x24;
        }
    }
    std::swap(hexValues[15],hexValues[17]);
    std::swap(hexValues[5],hexValues[25]);
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