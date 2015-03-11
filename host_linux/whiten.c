// Peter Allan 2015
#include <stdio.h>
#include "ecrypt-sync.h"

#define KEY_ROUNDS 5 // one or more
#define EXPANSION 1 // more bits, same entropy, set to none

int main()
{
  ECRYPT_ctx x;
  u8 key[32]={31,41,59,26,53,58,97,93,23,84,62,64,33,83,27,95,
               2,88,41,97,16,93,99,37,51, 5,82, 9,74,94,45,92}; // pi
  u8 iv[8]={27,18,28,18,28,45,90,45}; // e
  u8 buf[64], obuf[64];
  int i, j, bytes;

  for(j=0;j<KEY_ROUNDS;j++){
    fread(buf,1,40,stdin);
    for(i=0;i<32;i++) key[i] ^= buf[i];
    for(i=0;i<8;i++) iv[i] ^= buf[i+32];
  }
  ECRYPT_keysetup(&x,key,256,64);
  ECRYPT_ivsetup(&x,iv);
  while(!feof(stdin)){
    bytes = fread(buf, 1, 64, stdin);
    ECRYPT_encrypt_bytes(&x,buf,obuf,bytes);
    fwrite(obuf,1,bytes,stdout);
    // should re-initialize iv every 195 million years for REDOUBLER
    for(i=1; i<EXPANSION; i++){
      ECRYPT_keystream_bytes(&x,obuf,64);
      fwrite(obuf,1,64,stdout);
    }
  }
  return 0;
}
