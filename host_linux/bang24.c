// Peter Allan 2015
// Test with $ xxd -c3 -p <1MB_file> | sort | uniq -c -d
// The sum of (count-1) will be the collisions returned here.
// This utility is much quicker and offers the offset convenience.
// Empirical testing suggests that a range of 3464-3770 will test
// for a TRNG with 1% false rejection.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKS 349525 // floor(2^20/3)

uint32_t data[BLOCKS];

static int uint32_cmp(const void *l1, const void *l2) // for qsort()
{
  if(*(uint32_t *)l1 > *(uint32_t *)l2) return -1;
  if(*(uint32_t *)l1 < *(uint32_t *)l2) return 1;
  return 0;
}

int main(int argc, char *argv[])
{
  FILE *fp;
  int32_t i, bangs=0;

  if(argc<2 || argc>3){
    fprintf(stderr,"Usage: bang24 [offset] <filename>\n");
    fprintf(stderr,
"       Calculates the number of collisions of 24-bit words in the first 1MB\n"
"       of <fname>. Optionally, [offset] 1MB blocks can be skipped before\n"
"       testing.\n"
    );
    return 1;
  }
  if((fp=fopen(argv[argc-1],"rb"))==NULL){
    fprintf(stderr,"bang32: Can't open %s for reading.\n",argv[argc-1]);
    return 2;
  }
  if(argc==3 && fseek(fp,atoi(argv[1])*1048576,SEEK_SET)!=0){
    fprintf(stderr,"bang24: Failed to seek to [offset] in file.\n");
    return 3;
  }
  for(i=0;i<BLOCKS;i++){
    data[i]=0;
    if(fread(&(data[i]),3,1,fp)!=1){
      fprintf(stderr,"bang32: Insufficient data.\n");
      return 4;
    }
  }
  fclose(fp);
  qsort(data,BLOCKS,sizeof(uint32_t),uint32_cmp);
  for(i=0;i<BLOCKS-1;i++) if(data[i]==data[i+1]) bangs++;
  printf("%d\t%s\n",bangs,3464<=bangs&&bangs<=3770?"Pass":"Fail");
  return 0;
}