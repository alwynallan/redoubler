#include <stdio.h>
#include "ecrypt-sync.h"

#define KEY_ROUNDS 5 // one or more

int main()
{
    ECRYPT_ctx x;
	u8 key[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u8 iv[8]={0,0,0,0,0,0,0,0};
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
	}
	return 0;
}