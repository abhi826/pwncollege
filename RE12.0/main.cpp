#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>

int main() {
    std::vector<char> arr(264);
    arr[103] = 169;
    arr[104] = 122;
    arr[105] = 215;
    arr[106] = 51;
    arr[107] = 221;
    arr[108] = 230;
    std::string ans;
    for(int i=0;i<arr.size();i++){
        if(!arr[i])continue;
        ans += (char)arr[i];
    }
    std::cout<<ans<<std::endl;
    return 0;
}

/*
python -c 'import sys; sys.stdout.buffer.write(b"\x61\x62\x63\x63\x64\x68\x69\x6B\x6E\x70\x70\x72\x72\x73\x73\x74\x77")'
python -c 'import sys; sys.stdout.buffer.write(b"\x0c\xf2\x26\x4f\xaa\x4c")' |  /challenge/babyrev-level-12-1

*/