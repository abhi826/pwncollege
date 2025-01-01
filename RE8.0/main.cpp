#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>

int main() {
    std::vector<uint8_t> hexValues = {
        0xf5, 0x61, 0x70, 0x6d, 0x5a, 0x0c, 0x4b, 0x75, 0x2f, 0x7c, 0xad, 0x40, 
        0x44, 0x4d, 0xbc, 0xbf, 0x22, 0xb6, 0x09, 0xd3, 0x17, 0xa7, 0x71, 0xad, 
        0xf3, 0x0f, 0x1a, 0x95, 0xe9, 0x7e, 0x6d, 0x70, 0xdf, 0x16, 0x52
    };
    std::swap(hexValues[11],hexValues[32]);
    for(int i=0;i<hexValues.size();i++){
        switch(i%7){
            case 0:
                hexValues[i] = hexValues[i] ^ 0x66;
                break;
            case 1:
                hexValues[i] = hexValues[i] ^ 0xbb;
                break;
            case 2:
                hexValues[i] = hexValues[i] ^ 0x4f;
                break;
            case 3:
                hexValues[i] = hexValues[i] ^ 0x3a;
                break;
            case 4:
                hexValues[i] = hexValues[i] ^ 0x52;
                break;
            case 5:
                hexValues[i] = hexValues[i] ^ 0xc2;
                break;
            case 6:
                hexValues[i] = hexValues[i] ^ 0x81;
                break;
            default:
                break;
        }
    }

    for(int i=0;i<hexValues.size();i++){
        switch(i%7){
            case 0:
                hexValues[i] = hexValues[i] ^ 0xd0;
                break;
            case 1:
                hexValues[i] = hexValues[i] ^ 0xd1;
                break;
            case 2:
                hexValues[i] = hexValues[i] ^ 0x3d;
                break;
            case 3:
                hexValues[i] = hexValues[i] ^ 0x91;
                break;
            case 4:
                hexValues[i] = hexValues[i] ^ 0x4f;
                break;
            case 5:
                hexValues[i] = hexValues[i] ^ 0xc2;
                break;
            case 6:
                hexValues[i] = hexValues[i] ^ 0xcd;
                break;
            default:
                break;
        }
    }

    for(int i=0;i<hexValues.size();i++){
        switch(i%4){
            case 0:
                hexValues[i] = hexValues[i] ^ 0x83;
                break;
            case 1:
                hexValues[i] = hexValues[i] ^ 0xc9;
                break;
            case 2:
                hexValues[i] = hexValues[i] ^ 0xc1;
                break;
            case 3:
                hexValues[i] = hexValues[i] ^ 0x5;
                break;
        }
    }

    for(int i=0;i<hexValues.size();i++){
        hexValues[i] ^= 0xb2;
    }


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