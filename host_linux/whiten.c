// Peter Allan 2015
#include <stdio.h>
#include <unistd.h> // for getopt()
#include <stdlib.h>
#include "ecrypt-sync.h"

#define KEY_ROUNDS 5 // default, one or more
#define EXPANSION 1 // default, more bits, same entropy, x1

int main(int argc, char *argv[])
{
  ECRYPT_ctx x;
  u8 key[32]={31,41,59,26,53,58,97,93,23,84,62,64,33,83,27,95,
               2,88,41,97,16,93,99,37,51, 5,82, 9,74,94,45,92}; // pi
  u8 iv[8]={27,18,28,18,28,45,90,45}; // e
  u8 buf[64], obuf[64];
  int opt, i, j, bytes;
  int key_rounds = KEY_ROUNDS;
  int expansion = EXPANSION;

  while ((opt = getopt(argc, argv, "k:e:h?")) != -1) {
    switch (opt) {
    case 'k':
      key_rounds = atoi(optarg);
      if(key_rounds < 1) {
        fprintf(stderr,"%s: keying_rounds should be 1 or more.\n", argv[0]);
        exit(EXIT_FAILURE);
      }
      break;
    case 'e':
      expansion = atoi(optarg);
	  if(expansion < 1) {
        fprintf(stderr,"%s: expansion_factor should be 1 or more.\n", argv[0]);
        exit(EXIT_FAILURE);
      }
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-k keying_rounds] [-e expansion_factor]\n", argv[0]);
	  fprintf(stderr, "    Takes a high-entropy binary source on stdin and uses ChaCha20 to whiten\n");
	  fprintf(stderr, "    the bitstream, sending it to stdout.\n");
	  fprintf(stderr, "        -k keying_rounds takes an integer 1...2^31, default %d for how many\n", KEY_ROUNDS);
      fprintf(stderr, "           times the input is XORed into the key and initial value.\n");
	  fprintf(stderr, "        -e expansion_factor takes an integer 1...2^31, default %d for the\n", EXPANSION);
      fprintf(stderr, "           number of 64-byte blocks that are output for each 64-byte block\n");
	  fprintf(stderr, "           of input.\n");
      exit(EXIT_FAILURE);
    }
  }

  for(j=0;j<key_rounds;j++){
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
    for(i=1; i<expansion; i++){
      ECRYPT_keystream_bytes(&x,obuf,64);
      fwrite(obuf,1,64,stdout);
    }
  }

  return 0;
}