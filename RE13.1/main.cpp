#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>

void FUN_00101415(long param_1,char param_2, char param_3)

{
  if (param_2 == '\x01') {
    *(char *)(param_1 + 0x100) = param_3;
  }
  else if (param_2 == '\x10') {
    *(char *)(param_1 + 0x101) = param_3;
  }
  else if (param_2 == '@') {
    *(char *)(param_1 + 0x102) = param_3;
  }
  else if (param_2 == '\b') {
    *(char *)(param_1 + 0x103) = param_3;
  }
  else if (param_2 == '\x04') {
    *(char *)(param_1 + 0x104) = param_3;
  }
  else if (param_2 == '\x02') {
    *(char *)(param_1 + 0x105) = param_3;
  }
  else if (param_2 == ' ') {
    *(char *)(param_1 + 0x106) = param_3;
  }
  else {
    printf("unknown register");
  }
  return;
}


ulong FUN_00101363(long param_1, char param_2)

{
  ulong uVar1;
  
  if (param_2 == '\x01') {
    uVar1 = (ulong)*(char *)(param_1 + 0x100);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(char *)(param_1 + 0x101);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(char *)(param_1 + 0x102);
  }
  else if (param_2 == '\b') {
    uVar1 = (ulong)*(char *)(param_1 + 0x103);
  }
  else if (param_2 == '\x04') {
    uVar1 = (ulong)*(char *)(param_1 + 0x104);
  }
  else if (param_2 == '\x02') {
    uVar1 = (ulong)*(char *)(param_1 + 0x105);
  }
  else if (param_2 == ' ') {
    uVar1 = (ulong)*(char *)(param_1 + 0x106);
  }
  else {
    printf("unknown register");
  }
  return uVar1;
}

void FUN_00101507(long param_1,char param_2,char param_3)

{
  *(char *)(param_1 + (uint)param_2) = param_3;
  return;
}

void FUN_00101533(long param_1,char param_2, char param_3)

{
    FUN_00101415(param_1,param_2,param_3);
    return;
}

void FUN_00101687(long param_1,char param_2,char param_3)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar1 = FUN_00101363(param_1,param_3);
  uVar2 = FUN_00101363(param_1,param_2);
  FUN_00101507(param_1,uVar2,uVar1);
  return;
}

void FUN_00101568(long param_1,char param_2,char param_3)

{
  char cVar1;
  char cVar2;
  
  cVar1 = FUN_00101363(param_1,param_2);
  cVar2 = FUN_00101363(param_1,param_3);
  FUN_00101415(param_1,param_2,cVar2 + cVar1);
  return;
}


int main(){
    long arr[33];
    long param_1 = reinterpret_cast<long>(arr);
    FUN_00101533(param_1,0x10,0x68);
    FUN_00101533(param_1,0x40,1);
    FUN_00101533(param_1,1,0x1c);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0xac);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0x99);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0xfc);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0x38);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0x11);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0x48);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    FUN_00101533(param_1,1,0xa5);
    FUN_00101687(param_1,0x10,1);
    FUN_00101568(param_1,0x10,0x40);
    char* ptr = reinterpret_cast<char*>(arr) + 0x68;
    for (int i = 0; i < 8; i++) {
         std::printf("%02X ", static_cast<unsigned char>(ptr[i]));
    }
    std::printf("\n");
    return 0;
}

/*
1C AC 99 FC 38 11 48 A5
python -c 'import sys; sys.stdout.buffer.write(b"\x1C\xAC\x99\xFC\x38\x11\x48\xA5")'

*/