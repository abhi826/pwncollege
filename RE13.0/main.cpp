#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>

void write_memory(long param_1, char param_2,char param_3)

{
  *(char *)(param_1 + (uint)param_2) = param_3;
  return;
}

ulong read_register(long param_1,char param_2)

{
  ulong uVar1;
  
  if (param_2 == '\x02') {
    uVar1 = (ulong)*(char *)(param_1 + 0x100);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(char *)(param_1 + 0x101);
  }
  else if (param_2 == '\x04') {
    uVar1 = (ulong)*(char *)(param_1 + 0x102);
  }
  else if (param_2 == '\x01') {
    uVar1 = (ulong)*(char *)(param_1 + 0x103);
  }
  else if (param_2 == ' ') {
    uVar1 = (ulong)*(char *)(param_1 + 0x104);
  }
  else if (param_2 == '\b') {
    uVar1 = (ulong)*(char *)(param_1 + 0x105);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(char *)(param_1 + 0x106);
  }
  else {
     printf("unknown register");
  }
  return uVar1;
}

void write_register(long param_1,char param_2, char param_3)

{
  if (param_2 == '\x02') {
    *(char *)(param_1 + 0x100) = param_3;
  }
  else if (param_2 == '\x10') {
    *(char *)(param_1 + 0x101) = param_3;
  }
  else if (param_2 == '\x04') {
    *(char *)(param_1 + 0x102) = param_3;
  }
  else if (param_2 == '\x01') {
    *(char *)(param_1 + 0x103) = param_3;
  }
  else if (param_2 == ' ') {
    *(char *)(param_1 + 0x104) = param_3;
  }
  else if (param_2 == '\b') {
    *(char *)(param_1 + 0x105) = param_3;
  }
  else if (param_2 == '@') {
    *(char *)(param_1 + 0x106) = param_3;
  }
  else {
    printf("unknown register");
  }
  return;
}

void interpret_imm(long param_1, char param_2, char param_3)

{
  write_register(param_1,param_2,param_3);
  return;
}

void interpret_stm(long param_1,char param_2,char param_3)

{
  ulong uVar1;
  ulong uVar2;
  uVar1 = read_register(param_1,param_3);
  uVar2 = read_register(param_1,param_2);
  write_memory(param_1,uVar2,uVar1);
  return;
}

void interpret_add(long param_1,char param_2,char param_3)

{
  char cVar1;
  char cVar2;
  
  cVar1 = read_register(param_1,param_2);
  cVar2 = read_register(param_1,param_3);
  write_register(param_1,param_2,cVar2 + cVar1);
  return;
}


int main() {
        long param[33];
        long param_1 =(long)param;
        interpret_imm(param_1,0x10,0x58);
        interpret_imm(param_1,4,1);
        interpret_imm(param_1,2,0xde);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0x56);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0xaf);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0x53);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0x5c);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0xd9);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0x68);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        interpret_imm(param_1,2,0xbc);
        interpret_stm(param_1,0x10,2);
        interpret_add(param_1,0x10,4);
        
        char* ptr = reinterpret_cast<char*>(param) + 88;
        for (int i = 0; i < 8; i++) {
            std::printf("%02X ", static_cast<unsigned char>(ptr[i]));
        }
        std::printf("\n");
        return 0;
}

/*
DE 56 AF 53 5C D9 68 BC
python -c 'import sys; sys.stdout.buffer.write(b"\xDE\x56\xAF\x53\x5c\xD9\x68\xBC")'

*/