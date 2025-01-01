#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <fcntl.h>  
#include <unistd.h> 
/*
/flag
/ = 0x2F
f = 0x66
l = 0x6c
a = 0x61
g = 0x67

python -c 'import sys; sys.stdout.buffer.write(b"\x66\x6C\x61\x67")'
*/

/*
breakpoint 1: 0x11D8
           2: 0x18D3

breakpoint for sys_read (.text + C55)
breakpoint for sys_write (.text + CF2)
breakpoint for sys_open (.text + BB8)

  interpret_imm(param_1,0x40,0x79);
  interpret_imm(param_1,0x10,4);
  interpret_imm(param_1,4,0);
*/

void write_memory(long param_1,char param_2,char param_3)

{
  *(char *)(param_1 + (int)param_2) = param_3;
  return;
}

char read_memory(long param_1,char param_2)

{
  return *(char *)(param_1 + (int)param_2);
}


void write_register(long param_1,char param_2,char param_3)

{
    if (param_2 == '\x04') {
        *(char *)(param_1 + 0x100) = param_3;
    }
    else if (param_2 == '\x40') {
        *(char *)(param_1 + 0x101) = param_3;
    }
    else if (param_2 == '\x10') {
        *(char *)(param_1 + 0x102) = param_3;
    }
    else if (param_2 == '\b') {
        *(char *)(param_1 + 0x103) = param_3;
    }
    else if (param_2 == '\x02') {
        *(char *)(param_1 + 0x104) = param_3;
    }
    else if (param_2 == '\x01') {
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

ulong read_register(long param_1,char param_2)

{
  ulong uVar1;
  
  if (param_2 == '\x04') {
    uVar1 = (ulong)*(char *)(param_1 + 0x100);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(char *)(param_1 + 0x101);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(char *)(param_1 + 0x102);
  }
  else if (param_2 == '\b') {
    uVar1 = (ulong)*(char *)(param_1 + 0x103);
  }
  else if (param_2 == '\x02') {
    uVar1 = (ulong)*(char *)(param_1 + 0x104);
  }
  else if (param_2 == '\x01') {
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



char* describe_register(char param_1)

{
  char *puVar1;
  
  if (param_1 == '\x04') {
    puVar1 = "a";
  }
  else if (param_1 == '@') {
    puVar1 = "b";
  }
  else if (param_1 == '\x10') {
    puVar1 = "c";
  }
  else if (param_1 == '\b') {
    puVar1 = "d";
  }
  else if (param_1 == '\x02') {
    puVar1 = "s";
  }
  else if (param_1 == '\x01') {
    puVar1 = "i";
  }
  else if (param_1 == ' ') {
    puVar1 = "f";
  }
  else if (param_1 == '\0') {
    puVar1 = "NONE";
  }
  else {
    puVar1 = "?";
  }
  return puVar1;
}


void interpret_imm(long param_1,char param_2,char param_3)

{
  char* uVar1;
  
  uVar1 = describe_register(param_2);
  printf("[s] IMM %s = %#hhx\n",uVar1,(ulong)param_3);
  write_register(param_1,param_2,param_3);
  return;
}

char sys_open(long param_1,char *param_2,int param_3)

{
  return open(param_2,param_3);
}

char sys_read(long param_1,int param_2,void *param_3,size_t param_4)

{
 return read(param_2,param_3,param_4);
}

char sys_write(long param_1,int param_2,void *param_3,size_t param_4)

{
  return write(param_2,param_3,param_4);
}


char sys_sleep(long param_1,uint param_2)

{
  return sleep(param_2);
}

char sys_exit(long param_1,int param_2)

{
                    /* WARNING: Subroutine does not return */
   exit(param_2);
   return 0;
}




void interpret_sys(long param_1,char param_2,char param_3)

{
  char uVar1;
  char bVar2;
  char* uVar3;
  uint uVar4;
  
  uVar3 = describe_register(param_3);
  printf("[s] SYS %#hhx %s\n",(ulong)param_2,uVar3);
  if ((param_2 & 4) != 0) {
    puts("[s] ... open");
    uVar1 = sys_open(param_1, (char*)(param_1 + (ulong)*(char *)(param_1 + 0x100)),
                     *(char *)(param_1 + 0x101));
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 2) != 0) {
    puts("[s] ... read_memory");
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (char)uVar4;
    }
    uVar1 = sys_read(param_1,*(char *)(param_1 + 0x100),
                     (void*)((ulong)*(char *)(param_1 + 0x101) + param_1),bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 0x20) != 0) {
    puts("[s] ... write");
    uVar4 = 0x100 - *(char *)(param_1 + 0x101);
    bVar2 = *(char *)(param_1 + 0x102);
    if (uVar4 <= bVar2) {
      bVar2 = (char)uVar4;
    }
    uVar1 = sys_write(param_1,*(char *)(param_1 + 0x100),
                      (void*)((ulong)*(char *)(param_1 + 0x101) + param_1),bVar2);
    write_register(param_1,param_3,uVar1);
  }
  if ((param_2 & 1) != 0) {
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

void interpret_stm(long param_1,char param_2,char param_3)

{
  char uVar1;
  char uVar2;
  char* uVar3;
  char* uVar4;
  
  uVar3 = describe_register(param_3);
  uVar4 = describe_register(param_2);
  printf("[s] STM *%s = %s\n",uVar4,uVar3);
  uVar1 = read_register(param_1,param_3);
  uVar2 = read_register(param_1,param_2);
  write_memory(param_1,uVar2,uVar1);
  return;
}

void interpret_add(long param_1,char param_2,char param_3)

{
  char cVar1;
  char cVar2;
  char* uVar3;
  char* uVar4;
  
  uVar3 = describe_register(param_3);
  uVar4 = describe_register(param_2);
  printf("[s] ADD %s %s\n",uVar4,uVar3);
  cVar1 = read_register(param_1,param_2);
  cVar2 = read_register(param_1,param_3);
  write_register(param_1,param_2,cVar2 + cVar1);
  return;
}

void interpret_ldm(long param_1,char param_2,char param_3)

{
  char uVar1;
  char* uVar2;
  char* uVar3;
  
  uVar2 = describe_register(param_3);
  uVar3 = describe_register(param_2);
  printf("[s] LDM %s = *%s\n",uVar3,uVar2);
  uVar1 = read_register(param_1,param_3);
  uVar1 = read_memory(param_1,uVar1);
  write_register(param_1,param_2,uVar1);
  return;
}

void interpret_cmp(long param_1,char param_2,char param_3)

{
  char bVar1;
  char bVar2;
  char* uVar3;
  char* uVar4;
  
  uVar3 = describe_register(param_3);
  uVar4 = describe_register(param_2);
  printf("[s] CMP %s %s\n",uVar4,uVar3);
  bVar1 = read_register(param_1,param_2);
  bVar2 = read_register(param_1,param_3);
  *(char *)(param_1 + 0x106) = 0;
  if (bVar1 < bVar2) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 8;
  }
  if (bVar2 < bVar1) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 4;
  }
  if (bVar1 == bVar2) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 2;
  }
  else {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 1;
  }
  if ((bVar1 == 0) && (bVar2 == 0)) {
    *(char *)(param_1 + 0x106) = *(char *)(param_1 + 0x106) | 0x10;
  }
  return;
}


int main(){
  char bVar1;
  char bVar2;
  char bVar3;
  char bVar4;
  long arr[33];
  long param_1 = reinterpret_cast<long>(arr);
  
  interpret_imm(param_1,0x40,0x79);
  interpret_imm(param_1,0x10,4);
  interpret_imm(param_1,4,0);
  interpret_sys(param_1,2,4);
  interpret_imm(param_1,0x40,0x99);
  interpret_imm(param_1,0x10,1);
  interpret_imm(param_1,4,0xce);
  interpret_stm(param_1,0x40,4);
  interpret_add(param_1,0x40,0x10);
  interpret_imm(param_1,4,6);
  interpret_stm(param_1,0x40,4);
  interpret_add(param_1,0x40,0x10);
  interpret_imm(param_1,4,0x67);
  interpret_stm(param_1,0x40,4);
  interpret_add(param_1,0x40,0x10);
  interpret_imm(param_1,4,0x4c);
  interpret_stm(param_1,0x40,4);
  interpret_add(param_1,0x40,0x10);
  interpret_imm(param_1,0x40,0x99);
  interpret_ldm(param_1,0x40,0x40);
  interpret_imm(param_1,4,0x79);
  interpret_ldm(param_1,4,4);
  interpret_cmp(param_1,4,0x40);
  bVar1 = *(char *)(param_1 + 0x106);
  interpret_imm(param_1,0x40,0x9a);
  interpret_ldm(param_1,0x40,0x40);
  interpret_imm(param_1,4,0x7a);
  interpret_ldm(param_1,4,4);
  interpret_cmp(param_1,4,0x40);
  bVar2 = *(char *)(param_1 + 0x106);
  interpret_imm(param_1,0x40,0x9b);
  interpret_ldm(param_1,0x40,0x40);
  interpret_imm(param_1,4,0x7b);
  interpret_ldm(param_1,4,4);
  interpret_cmp(param_1,4,0x40);
  bVar3 = *(char *)(param_1 + 0x106);
  interpret_imm(param_1,0x40,0x9c);
  interpret_ldm(param_1,0x40,0x40);
  interpret_imm(param_1,4,0x7c);
  interpret_ldm(param_1,4,4);
  interpret_cmp(param_1,4,0x40);
  bVar4 = *(char *)(param_1 + 0x106);
  interpret_imm(param_1,4,1);
  interpret_imm(param_1,0x40,0);
  interpret_imm(param_1,0x10,1);
  if ((bVar4 & 2) == 0 || ((bVar3 & 2) == 0 || ((bVar2 & 2) == 0 || (bVar1 & 2) == 0))) {
    interpret_imm(param_1,8,0x49);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x4e);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x43);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x4f);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x52);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x52);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x45);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x43);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x54);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x21);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,4,1);
  }
  else {
    interpret_imm(param_1,8,0x43);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x4f);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x52);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x52);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x45);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x43);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x54);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x21);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x20);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x59);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x6f);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x75);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x72);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x20);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x66);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x6c);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x61);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x67);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x3a);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,10);
    interpret_stm(param_1,0x40,8);
    interpret_sys(param_1,0x20,4);
    interpret_imm(param_1,8,0x2f);
    interpret_imm(param_1,0x40,0);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,8,0x66);
    interpret_imm(param_1,0x40,1);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,8,0x6c);
    interpret_imm(param_1,0x40,2);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,8,0x61);
    interpret_imm(param_1,0x40,3);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,8,0x67);
    interpret_imm(param_1,0x40,4);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,8,0);
    interpret_imm(param_1,0x40,5);
    interpret_stm(param_1,0x40,8);
    interpret_imm(param_1,4,0);
    interpret_imm(param_1,0x40,0);
    interpret_sys(param_1,4,4);
    interpret_imm(param_1,0x10,100);
    interpret_sys(param_1,2,0x10);
    interpret_imm(param_1,4,1);
    interpret_sys(param_1,0x20,0x10);
    interpret_imm(param_1,4,0);
  }
  interpret_imm(param_1,8,10);
  interpret_stm(param_1,0x40,8);
  interpret_sys(param_1,0x20,4);
  interpret_sys(param_1,8,4);
  return 0;
}