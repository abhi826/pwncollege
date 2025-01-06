#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <fcntl.h>  
#include <unistd.h> 

void FUN_0010171d(long param_1,undefined param_2,undefined param_3)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = FUN_00101343(param_1,param_2);
  bVar2 = FUN_00101343(param_1,param_3);
  *(undefined *)(param_1 + 0x106) = 0;
  if (bVar1 < bVar2) {
    *(byte *)(param_1 + 0x106) = *(byte *)(param_1 + 0x106) | 8;
  }
  if (bVar2 < bVar1) {
    *(byte *)(param_1 + 0x106) = *(byte *)(param_1 + 0x106) | 2;
  }
  if (bVar1 == bVar2) {
    *(byte *)(param_1 + 0x106) = *(byte *)(param_1 + 0x106) | 1;
  }
  else {
    *(byte *)(param_1 + 0x106) = *(byte *)(param_1 + 0x106) | 4;
  }
  if ((bVar1 == 0) && (bVar2 == 0)) {
    *(byte *)(param_1 + 0x106) = *(byte *)(param_1 + 0x106) | 0x10;
  }
  return;
}


undefined FUN_001014c6(long param_1,byte param_2)

{
  return *(undefined *)(param_1 + (int)(uint)param_2);
}

void FUN_001016c6(undefined8 param_1,undefined param_2,undefined param_3)

{
  undefined uVar1;
  
  uVar1 = FUN_00101343(param_1,param_3);
  uVar1 = FUN_001014c6(param_1,uVar1);
  FUN_001013f5(param_1,param_2,uVar1);
  return;
}

void FUN_00101548(undefined8 param_1,undefined param_2,undefined param_3)

{
  char cVar1;
  char cVar2;
  
  cVar1 = FUN_00101343(param_1,param_2);
  cVar2 = FUN_00101343(param_1,param_3);
  FUN_001013f5(param_1,param_2,cVar2 + cVar1);
  return;
}

void FUN_001014e7(long param_1,byte param_2,undefined param_3)

{
  *(undefined *)(param_1 + (int)(uint)param_2) = param_3;
  return;
}

ulong FUN_00101343(long param_1,char param_2)

{
  ulong uVar1;
  
  if (param_2 == '\b') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x100);
  }
  else if (param_2 == '\x01') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x101);
  }
  else if (param_2 == ' ') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x102);
  }
  else if (param_2 == '\x04') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x103);
  }
  else if (param_2 == '@') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x104);
  }
  else if (param_2 == '\x10') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x105);
  }
  else if (param_2 == '\x02') {
    uVar1 = (ulong)*(byte *)(param_1 + 0x106);
  }
  else {
    uVar1 = FUN_00101249(param_1,"unknown register");
  }
  return uVar1;
}

void FUN_00101667(undefined8 param_1,undefined param_2,undefined param_3)

{
  undefined uVar1;
  undefined uVar2;
  
  uVar1 = FUN_00101343(param_1,param_3);
  uVar2 = FUN_00101343(param_1,param_2);
  FUN_001014e7(param_1,uVar2,uVar1);
  return;
}

void FUN_00101876(long param_1,byte param_2,undefined param_3)

{
  undefined uVar1;
  byte bVar2;
  uint uVar3;
  
  if ((param_2 & 4) != 0) {
    uVar1 = FUN_00101271(param_1,param_1 + (ulong)*(byte *)(param_1 + 0x100),
                         *(undefined *)(param_1 + 0x101),*(undefined *)(param_1 + 0x102));
    FUN_001013f5(param_1,param_3,uVar1);
  }
  if ((param_2 & 2) != 0) {
    uVar3 = 0x100 - *(byte *)(param_1 + 0x101);
    bVar2 = *(byte *)(param_1 + 0x102);
    if (uVar3 <= bVar2) {
      bVar2 = (byte)uVar3;
    }
    uVar1 = FUN_001012a3(param_1,*(undefined *)(param_1 + 0x100),
                         (ulong)*(byte *)(param_1 + 0x101) + param_1,bVar2);
    FUN_001013f5(param_1,param_3,uVar1);
  }
  if ((param_2 & 0x10) != 0) {
    uVar3 = 0x100 - *(byte *)(param_1 + 0x101);
    bVar2 = *(byte *)(param_1 + 0x102);
    if (uVar3 <= bVar2) {
      bVar2 = (byte)uVar3;
    }
    uVar1 = FUN_001012d5(param_1,*(undefined *)(param_1 + 0x100),
                         (ulong)*(byte *)(param_1 + 0x101) + param_1,bVar2);
    FUN_001013f5(param_1,param_3,uVar1);
  }
  if ((param_2 & 8) != 0) {
    uVar1 = FUN_00101324(param_1,*(undefined *)(param_1 + 0x100));
    FUN_001013f5(param_1,param_3,uVar1);
  }
  if ((param_2 & 0x20) != 0) {
    FUN_00101307(param_1,*(undefined *)(param_1 + 0x100));
  }
  return;
}


void FUN_001013f5(long param_1,char param_2,undefined param_3)

{
  if (param_2 == '\b') {
    *(undefined *)(param_1 + 0x100) = param_3;
  }
  else if (param_2 == '\x01') {
    *(undefined *)(param_1 + 0x101) = param_3;
  }
  else if (param_2 == ' ') {
    *(undefined *)(param_1 + 0x102) = param_3;
  }
  else if (param_2 == '\x04') {
    *(undefined *)(param_1 + 0x103) = param_3;
  }
  else if (param_2 == '@') {
    *(undefined *)(param_1 + 0x104) = param_3;
  }
  else if (param_2 == '\x10') {
    *(undefined *)(param_1 + 0x105) = param_3;
  }
  else if (param_2 == '\x02') {
    *(undefined *)(param_1 + 0x106) = param_3;
  }
  else {
    FUN_00101249(param_1,"unknown register");
  }
  return;
}

void FUN_00101513(undefined8 param_1,undefined param_2,undefined param_3)

{
  FUN_001013f5(param_1,param_2,param_3);
  return;
}

int main(){
  // *(undefined *)(param_1 + 0x101) = 0x7c;
  FUN_00101513(param_1,1,0x7c);
  // *(undefined *)(param_1 + 0x102) = 4;
  FUN_00101513(param_1,0x20,4);
  // *(undefined *)(param_1 + 0x100) = 0;
  FUN_00101513(param_1,8,0);
  // 4 bytes read from stdin and stored in param_1 + 0x7c
  //  *(undefined *)(param_1 + 0x100) = 4(bytes read)
  FUN_00101876(param_1,2,8);
  // *(undefined *)(param_1 + 0x101) = 0x9c
  FUN_00101513(param_1,1,0x9c);
  // *(undefined *)(param_1 + 0x102) = 1
  FUN_00101513(param_1,0x20,1);
  // *(undefined *)(param_1 + 0x100) = 0x29
  FUN_00101513(param_1,8,0x29);
  // uVar1 = (ulong)*(byte *)(param_1 + 0x100);
  // uVar2 = (ulong)*(byte *)(param_1 + 0x101);
  // *(undefined *)(param_1 + (int)(uint)uvar2) = uvar1;
  // *(char*)(param_1 + 0x9c) = 0x29
  FUN_00101667(param_1,1,8);
  // cVar1 = (ulong)*(char *)(param_1 + 0x101);
  // cVar1 = 0x9c
  // cVar2 = (ulong)*(byte *)(param_1 + 0x102);
  // cVar2 = 1
  // *(undefined *)(param_1 + 0x101) = cVar1 +cVar2;
  // *(undefined *)(param_1 + 0x101) = 0x9d;
  FUN_00101548(param_1,1,0x20);
  FUN_00101513(param_1,8,0xb);
  FUN_00101667(param_1,1,8);
  FUN_00101548(param_1,1,0x20);
  FUN_00101513(param_1,8,0xdf);
  FUN_00101667(param_1,1,8);
  FUN_00101548(param_1,1,0x20);
  FUN_00101513(param_1,8,0xda);
  FUN_00101667(param_1,1,8);
  FUN_00101548(param_1,1,0x20);
  FUN_00101513(param_1,1,0x9c);
  FUN_001016c6(param_1,1,1);
  FUN_00101513(param_1,8,0x7c);
  FUN_001016c6(param_1,8,8);
  FUN_0010171d(param_1,8,1);
  bVar1 = *(byte *)(param_1 + 0x106);
  FUN_00101513(param_1,1,0x9d);
  FUN_001016c6(param_1,1,1);
  FUN_00101513(param_1,8,0x7d);
  FUN_001016c6(param_1,8,8);
  FUN_0010171d(param_1,8,1);
  bVar2 = *(byte *)(param_1 + 0x106);
  FUN_00101513(param_1,1,0x9e);
  FUN_001016c6(param_1,1,1);
  FUN_00101513(param_1,8,0x7e);
  FUN_001016c6(param_1,8,8);
  FUN_0010171d(param_1,8,1);
  bVar3 = *(byte *)(param_1 + 0x106);
  FUN_00101513(param_1,1,0x9f);
  FUN_001016c6(param_1,1,1);
  FUN_00101513(param_1,8,0x7f);
  FUN_001016c6(param_1,8,8);
  FUN_0010171d(param_1,8,1);
  bVar4 = *(byte *)(param_1 + 0x106);
  FUN_00101513(param_1,8,1);
  FUN_00101513(param_1,1,0);
  FUN_00101513(param_1,0x20,1);
}