#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

int main() {
    std::string input;
    std::cout << "Enter 16 space-separated hex values: ";
    std::getline(std::cin, input);

    std::vector<int> hexValues;
    std::istringstream iss(input);
    std::string hexStr;

    while (iss >> hexStr) {
        int value;
        std::stringstream ss;
        ss << std::hex << hexStr;
        ss >> value;
        hexValues.push_back(value);
    }

    for(int i=0;i<hexValues.size();i++){
        if(i%2){
            hexValues[i] ^= 0xC4;

        }
        else{
            hexValues[i] ^= 0x1E;

        }
    }

    for(int i=0;i<hexValues.size();i++){
        if(i%3==2){
            hexValues[i] ^= 0x2D;

        }
        else if(i%3==1){
            hexValues[i] ^= 0x7F;
        }
        else{
            hexValues[i] ^= 0x50;

        }
    }

    for(int i=0;i<hexValues.size();i++){
        hexValues[i] ^= 0x1A;
    }


    for(auto i:hexValues){
        std::cout<<(char)i;
    }

    std::cout<<std::endl;

    return 0;
}
