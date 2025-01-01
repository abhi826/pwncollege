#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <fcntl.h>  
#include <unistd.h> 


void sys_exit(long param_1,int param_2)

{
                    /* WARNING: Subroutine does not return */
  exit(param_2);
}

ulong sys_sleep(long param_1,uint param_2)

{
  ulong ret = sleep(param_2);
  return ret;
}

ulong sys_write(long param_1,int param_2,void *param_3,size_t param_4)

{
  ulong ret = write(param_2,param_3,param_4);
  return ret;
}

ulong sys_open(long param_1,char *param_2,int param_3)

{
  ulong ret = open(param_2,param_3);
  return ret;
}


ulong sys_read(long param_1,int param_2,void *param_3,size_t param_4)

{
  ulong ret = read(param_2,param_3,param_4);
  return ret;
}

ulong read_register(long param_1,char param_2)

{
  ulong uVar1;
  
  if (param_2 == ' ') {
    uVar1 = (ulong)*(char *)(param_1 + 0x100);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(char *)(param_1 + 0x101);
  }
  else if (param_2 == '\x02') {
    uVar1 = (ulong)*(char *)(param_1 + 0x102);
  }
  else if (param_2 == '\x01') {
    uVar1 = (ulong)*(char *)(param_1 + 0x103);
  }
  else if (param_2 == '\b') {
    uVar1 = (ulong)*(char *)(param_1 + 0x104);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(char *)(param_1 + 0x105);
  }
  else if (param_2 == '\x04') {
    uVar1 = (ulong)*(char *)(param_1 + 0x106);
  }
  else {
    printf("unknown register");
  }
  return uVar1;
}

void write_register(long param_1,char param_2,char param_3)

{
  if (param_2 == ' ') {
    *(char *)(param_1 + 0x100) = param_3;
  }
  else if (param_2 == '\x10') {
    *(char *)(param_1 + 0x101) = param_3;
  }
  else if (param_2 == '\x02') {
    *(char *)(param_1 + 0x102) = param_3;
  }
  else if (param_2 == '\x01') {
    *(char *)(param_1 + 0x103) = param_3;
  }
  else if (param_2 == '\b') {
    *(char *)(param_1 + 0x104) = param_3;
  }
  else if (param_2 == '@') {
    *(char *)(param_1 + 0x105) = param_3;
  }
  else if (param_2 == '\x04') {
    *(char *)(param_1 + 0x106) = param_3;
  }
  else {
    printf("unknown register");
  }
  return;
}

void write_memory(long param_1,char param_2,char param_3)

{
  *(char *)(param_1 + (int)param_2) = param_3;
  return;
}

void interpret_stm(long param_1,char param_2,char param_3)

{
  char uVar1;
  char uVar2;
  
  uVar1 = read_register(param_1,param_3);
  uVar2 = read_register(param_1,param_2);
  write_memory(param_1,uVar2,uVar1);
  return;
}


void interpret_imm(long param_1,char param_2,char param_3)

{
  write_register(param_1,param_2,param_3);
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

void interpret_sys(long param_1,char param_2,char param_3)

{
  char uVar1;
  char bVar2;
  int uVar4;
  
  if ((param_2 & 1) != 0) {
    uVar1 = sys_open(param_1, (char*)(param_1 + (ulong)*(char *)(param_1 + 0x100)),
                     *(char *)(param_1 + 0x101));
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 2) != 0) {
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (char)uVar4;
    }
    uVar1 = sys_read(param_1,*(char *)(param_1 + 0x100),
                     (void*)(*(char *)(param_1 + 0x101) + param_1),bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 4) != 0) {
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (char)uVar4;
    }
    uVar1 = sys_write(param_1,*(char *)(param_1 + 0x100),
                      (void*)(*(char *)(param_1 + 0x101) + param_1),bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 8) != 0) {
    uVar1 = sys_sleep(param_1,*(char *)(param_1 + 0x100));
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 0x10) != 0) {
    sys_exit(param_1,*(char *)(param_1 + 0x100));
  }
  return;
}

int main(){
  long arr[33];
  long param_1 = reinterpret_cast<long>(arr);
  interpret_imm(param_1,0x10,0x58);
  interpret_imm(param_1,2,8);
  interpret_imm(param_1,0x20,0);
  interpret_sys(param_1,2,0x20);
  interpret_imm(param_1,0x10,0x78);
  interpret_imm(param_1,2,1);
  interpret_imm(param_1,0x20,0x2d);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0xc2);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0xcc);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0xa5);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0x2c);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0x39);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,8);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);
  interpret_imm(param_1,0x20,0x44);
  interpret_stm(param_1,0x10,0x20);
  interpret_add(param_1,0x10,2);

   char* ptr = reinterpret_cast<char*>(arr)+0x78;
   for (int i = 0; i < 8; i++) {
         std::printf("%02X ", static_cast<unsigned char>(ptr[i]));
   }
    std::printf("\n");

    return 0;
}


/*
0x2d	0xc2	0xcc	0xa5	0x2c	0x39	0x08	0x44
python -c 'import sys; sys.stdout.buffer.write(b"\x2d\xc2\xcc\xa5\x2c\x39\x08\x44")'
*/