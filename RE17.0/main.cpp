#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <fcntl.h>  
#include <unistd.h> 




ulong read_register(long param_1,char param_2)

{
  ulong uVar1;
  
  if (param_2 == '\b') {
    uVar1 = (ulong)*(char *)(param_1 + 0x100);
  }
  else if (param_2 == ' ') {
    uVar1 = (ulong)*(char *)(param_1 + 0x101);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(char *)(param_1 + 0x102);
  }
  else if (param_2 == '\x04') {
    uVar1 = (ulong)*(char *)(param_1 + 0x103);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(char *)(param_1 + 0x104);
  }
  else if (param_2 == '\x02') {
    uVar1 = (ulong)*(char *)(param_1 + 0x105);
  }
  else if (param_2 == '\x01') {
    uVar1 = (ulong)*(char *)(param_1 + 0x106);
  }
  else {
    uVar1 = crash(param_1,"unknown register");
  }
  return uVar1;
}



void interpret_sys(long param_1,char param_2,char param_3)

{
  char uVar1;
  char bVar2;
  char uVar3;
  uint uVar4;
  
  if ((param_2 & 4) != 0) {
    puts("[s] ... open");
    uVar1 = sys_open(param_1,param_1 + (ulong)*(char *)(param_1 + 0x100),
                     *(char *)(param_1 + 0x101),*(char *)(param_1 + 0x102));
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 0x10) != 0) {
    puts("[s] ... read_memory");
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (char)uVar4;
    }
    uVar1 = sys_read(param_1,*(char *)(param_1 + 0x100),
                     (ulong)*(char *)(param_1 + 0x101) + param_1,bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 1) != 0) {
    puts("[s] ... write");
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (byte)uVar4;
    }
    uVar1 = sys_write(param_1,*(char *)(param_1 + 0x100),
                      (ulong)*(byte *)(param_1 + 0x101) + param_1,bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 2) != 0) {
    puts("[s] ... sleep");
    uVar1 = sys_sleep(param_1,*(char *)(param_1 + 0x100));
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 8) != 0) {
    puts("[s] ... exit");
    sys_exit(param_1,*(char *)(param_1 + 0x100));
  }
  if (param_3 != '\0') {
    bVar2 = read_register(param_1,param_3);
    uVar3 = describe_register(param_3);
    printf("[s] ... return value (in register %s): %#hhx\n",uVar3,(ulong)bVar2);
  }
  return;
}

void write_register(long param_1,char param_2, char param_3)

{
  if (param_2 == '\b') {
    *(char *)(param_1 + 0x100) = param_3;
  }
  else if (param_2 == ' ') {
    *(char *)(param_1 + 0x101) = param_3;
  }
  else if (param_2 == '@') {
    *(char *)(param_1 + 0x102) = param_3;
  }
  else if (param_2 == '\x04') {
    *(char *)(param_1 + 0x103) = param_3;
  }
  else if (param_2 == '\x10') {
    *(char *)(param_1 + 0x104) = param_3;
  }
  else if (param_2 == '\x02') {
    *(char *)(param_1 + 0x105) = param_3;
  }
  else if (param_2 == '\x01') {
    *(char *)(param_1 + 0x106) = param_3;
  }
  else {
    printf("unknown register");
  }
  return;
}

void interpret_imm(long param_1,char param_2,char param_3)

{
  write_register(param_1,param_2,param_3);
  return;
}

char read_memory(long param_1,char param_2)

{
  return *(char *)(param_1 + (int)(uint)param_2);
}


void write_memory(long param_1,char param_2,char param_3)

{
  *(char *)(param_1 + (int)(uint)param_2) = param_3;
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


void interpret_stm(long param_1,char param_2,char param_3)

{
  char uVar1;
  char uVar2;

  uVar1 = read_register(param_1,param_3);
  uVar2 = read_register(param_1,param_2);
  write_memory(param_1,uVar2,uVar1);
  return;
}

void interpret_ldm(long param_1,char param_2,char param_3)

{
  char uVar1;
  uVar1 = read_register(param_1,param_3);
  uVar1 = read_memory(param_1,uVar1);
  write_register(param_1,param_2,uVar1);
  return;
}

void interpret_cmp(long param_1,undefined param_2,undefined param_3)

{
  char bVar1;
  char bVar2;

  bVar1 = read_register(param_1,param_2);
  bVar2 = read_register(param_1,param_3);
  *(char *)(param_1 + 0x106) = 0;
  if (bVar1 < bVar2) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 0x10;
  }
  if (bVar2 < bVar1) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 1;
  }
  if (bVar1 == bVar2) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 8;
  }
  else {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 4;
  }
  if ((bVar1 == 0) && (bVar2 == 0)) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 2;
  }
  return;
}

/*
python -c 'import sys; sys.stdout.buffer.write(b"\x57\x73\xc9\x0c\x41\xb1\xb1\x42\xb5")'
*/

int main()
{

  char bVar1;
  char bVar2;
  char bVar3;
  char bVar4;
  char bVar5;
  char bVar6;
  char bVar7;
  char bVar8;
  char bVar9;
  
  // *(char *)(param_1 + 0x101) = 0x3a
  interpret_imm(param_1,0x20,0x3a);
  // *(char *)(param_1 + 0x102) = 9
  interpret_imm(param_1,0x40,9);
  // *(char *)(param_1 + 0x100) = 0;
  interpret_imm(param_1,8,0);
  // sys_read(param_1,*(char *)(param_1 + 0x100), (ulong)*(char *)(param_1 + 0x101) + param_1,bVar2);
  // sys_read(param_1, 0, param_1 + 0x3a, 9);
  // *(char *)(param_1 + 0x100) = 9
  interpret_sys(param_1,0x10,8);
  // *(char *)(param_1 + 0x101) = 0x5a
  interpret_imm(param_1,0x20,0x5a);
  // *(char *)(param_1 + 0x102) = 1
  interpret_imm(param_1,0x40,1);
  // *(char *)(param_1 + 0x100) = 5;
  interpret_imm(param_1,8,5);
  // uVar1 = (ulong)*(char *)(param_1 + 0x100);
  // uVar2 = (ulong)*(char *)(param_1 + 0x101);
  // *(char *)(param_1 + uVar2) = uVar1
  // *(char*)(param_1 + 0x5a) = 5
  interpret_stm(param_1,0x20,8);
  /*
  cVar1 = read_register(param_1,param_2);
  cVar1 = (ulong)*(char *)(param_1 + 0x101);
  cVar1 = 0x5a
  cVar2 = read_register(param_1,param_3);
  cVar2 = (ulong)*(char *)(param_1 + 0x102);
  cVar2 = 1
  write_register(param_1,param_2,cVar2 + cVar1);
  *(char *)(param_1 + 0x101) = 0x5b
  */
  interpret_add(param_1,0x20,0x40);
  // *(char *)(param_1 + 0x100) = 0xde;
  interpret_imm(param_1,8,0xde);
  // uVar1 = (ulong)*(char *)(param_1 + 0x100);
  // uVar2 = (ulong)*(char *)(param_1 + 0x101);
  // *(char *)(param_1 + uVar2) = uVar1
  // *(char *)(param_1 + 0x5b) = 0xde
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  interpret_imm(param_1,8,0x7d);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  interpret_imm(param_1,8,0x10);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  interpret_imm(param_1,8,0xd8);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  interpret_imm(param_1,8,0x99);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  interpret_imm(param_1,8,0x7c);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);
  // *(char *)(param_1 + 0x100) = 0xe4
  interpret_imm(param_1,8,0xe4);
  // uVar1 = (ulong)*(char *)(param_1 + 0x100);
  // uVar2 = (ulong)*(char *)(param_1 + 0x101);
  // *(char *)(param_1 + uVar2) = uVar1
  // *(char *)(param_1 + 0x61) = 0xe4
  interpret_stm(param_1,0x20,8);
  // Increment address 0x20 -> 0x62
  // *(char *)(param_1 + 0x101) = 0x62
  interpret_add(param_1,0x20,0x40);
  // *(char *)(param_1 + 0x100) = 0x3b
  interpret_imm(param_1,8,0x3b);
  // uVar1 = (ulong)*(char *)(param_1 + 0x100);
  // uVar2 = (ulong)*(char *)(param_1 + 0x101);
  // *(char *)(param_1 + uVar2) = uVar1
  // *(char *)(param_1 + 0x62) = 0x3b
  interpret_stm(param_1,0x20,8);
  // Increment address 0x20 -> 0x63
  // *(char *)(param_1 + 0x101) = 0x63
  interpret_add(param_1,0x20,0x40);


  // *(char *)(param_1 + 0x101) = 0x3a
  interpret_imm(param_1,0x20,0x3a);
  // *(char *)(param_1 + 0x102) = 1
  interpret_imm(param_1,0x40,1);
  /*
  uVar1 = read_register(param_1,param_3);
  uVar1 = 0x3a
  uVar1 = read_memory(param_1,uVar1);
  uVar1 = (first bye of user input)
  write_register(param_1,param_2,uVar1);
  // *(char *)(param_1 + 0x100) = (first byte of user input)
  */
  interpret_ldm(param_1,8,0x20);
  // *(char *)(param_1 + 0x103) = 0xae
  interpret_imm(param_1,4,0xae);
  /*
  cVar1 = read_register(param_1,param_2);
  cVar1 = (ulong)*(char *)(param_1 + 0x100);
  cVar1 = (first byte of user Input)
  cVar2 = read_register(param_1,param_3);
  cVar2 = (ulong)*(char *)(param_1 + 0x103);
  cVar2 = 0xae
  write_register(param_1,param_2,cVar2 + cVar1);
  *(char *)(param_1 + 0x100) = (first byte of user Input ) + 0xae
  */
  interpret_add(param_1,8,4);
  // uVar1 = (ulong)*(char *)(param_1 + 0x100);
  // uVar2 = (ulong)*(char *)(param_1 + 0x101);
  // *(char *)(param_1 + uVar2) = uVar1
  // *(char *)(param_1 + 0x3a) = (first byte of user Input ) + 0xae
  interpret_stm(param_1,0x20,8);
  // *(char *)(param_1 + 0x101) = 0x3b
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0x6b);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0xb4);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,4);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0x97);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0xe8);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0xcb);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0xa2);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);

  interpret_ldm(param_1,8,0x20);
  interpret_imm(param_1,4,0x86);
  interpret_add(param_1,8,4);
  interpret_stm(param_1,0x20,8);
  interpret_add(param_1,0x20,0x40);


  // *(char *)(param_1 + 0x101) = 0x5a
  interpret_imm(param_1,0x20,0x5a);
  /*
  uVar1 = read_register(param_1,param_3);
  uVar1 = 0x5a
  uVar1 = read_memory(param_1,uVar1);
  uVar1 = (first byte of answer)
  write_register(param_1,param_2,uVar1);
  // *(char *)(param_1 + 0x101) = (first byte of answer)
  */
  interpret_ldm(param_1,0x20,0x20);
  // *(char *)(param_1 + 0x100) = 0x3a
  interpret_imm(param_1,8,0x3a);
  /*
  uVar1 = read_register(param_1,param_3);
  uVar1 = 0x3a
  uVar1 = read_memory(param_1,uVar1);
  uVar1 = (first byte of input)
  write_register(param_1,param_2,uVar1);
  // *(char *)(param_1 + 0x100) = (first byte of input)
  */
  interpret_ldm(param_1,8,8);
  // *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 8;
  interpret_cmp(param_1,8,0x20);
  bVar1 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x5b);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x3b);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar2 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x5c);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x3c);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar3 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x5d);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x3d);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar4 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x5e);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x3e);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar5 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x5f);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x3f);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar6 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x60);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x40);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar7 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x61);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x41);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar8 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,0x20,0x62);
  interpret_ldm(param_1,0x20,0x20);
  interpret_imm(param_1,8,0x42);
  interpret_ldm(param_1,8,8);
  interpret_cmp(param_1,8,0x20);
  bVar9 = *(byte *)(param_1 + 0x106);
  interpret_imm(param_1,8,1);
  interpret_imm(param_1,0x20,0);
  interpret_imm(param_1,0x40,1);
  if ((bVar9 & 8) == 0 ||
      ((bVar8 & 8) == 0 ||
      ((bVar7 & 8) == 0 ||
      ((bVar6 & 8) == 0 ||
      ((bVar5 & 8) == 0 ||
      ((bVar4 & 8) == 0 || ((bVar3 & 8) == 0 || ((bVar2 & 8) == 0 || (bVar1 & 8) == 0)))))))) {
    interpret_imm(param_1,4,0x49);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x4e);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x43);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x4f);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x52);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x52);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x45);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x43);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x54);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x21);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,8,1);
  }
  else {
    interpret_imm(param_1,4,0x43);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x4f);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x52);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x52);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x45);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x43);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x54);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x21);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x20);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x59);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x6f);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x75);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x72);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x20);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x66);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x6c);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x61);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x67);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x3a);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,10);
    interpret_stm(param_1,0x20,4);
    interpret_sys(param_1,1,8);
    interpret_imm(param_1,4,0x2f);
    interpret_imm(param_1,0x20,0);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,4,0x66);
    interpret_imm(param_1,0x20,1);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,4,0x6c);
    interpret_imm(param_1,0x20,2);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,4,0x61);
    interpret_imm(param_1,0x20,3);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,4,0x67);
    interpret_imm(param_1,0x20,4);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,4,0);
    interpret_imm(param_1,0x20,5);
    interpret_stm(param_1,0x20,4);
    interpret_imm(param_1,8,0);
    interpret_imm(param_1,0x20,0);
    interpret_sys(param_1,4,8);
    interpret_imm(param_1,0x40,100);
    interpret_sys(param_1,0x10,0x40);
    interpret_imm(param_1,8,1);
    interpret_sys(param_1,1,0x40);
    interpret_imm(param_1,8,0);
  }
  interpret_imm(param_1,4,10);
  interpret_stm(param_1,0x20,4);
  interpret_sys(param_1,1,8);
  interpret_sys(param_1,8,8);
  return;
}







}