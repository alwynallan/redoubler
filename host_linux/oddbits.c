// oddbits.c - takes bitstream on stdin and sends just the odd (or even or XORed) bits to stdout
// Peter Allan <alwynallan@gmail.com> 2015, public domain
// After compile 'ln oddbits evenbits && ln oddbits xorbits'
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <libgen.h> // for non-GNU basename()

int main(int argc, char **argv)
{
  int odd, i, j, c1, c2;
  uint8_t lut[65536], to, te;

  if(!strcmp(basename(argv[0]),"oddbits")) odd=1;
  else if(!strcmp(basename(argv[0]),"evenbits")) odd=0;
  else if(!strcmp(basename(argv[0]),"xorbits")) odd=2;
  else{
    fprintf(stderr,"%s: Should be named oddbits or evenbits or xorbits.\n",basename(argv[0]));
    return 1;
  }

  // note convention: byte is bits b7,b6,b5,b4,b3,b2,b1,b0 and oddbits are b7,b5,b3,b1
  if(odd==0 || odd==1)
    {for(i=0;i<65536;i++) for(lut[i]=0,j=0;j<8;j++) if((i>>(j*2+odd))&1) lut[i] |= 1<<j;}
  else{ // odd==2
    for(i=0;i<65536;i++){
      to=0;
      te=0;
      for(j=0;j<8;j++){
        if((i>>(j*2+1))&1) to |= 1<<j;
        if((i>>(j*2  ))&1) te |= 1<<j;
      }
      lut[i]= to ^ te; // there must be a simpler way
      //fprintf(stderr,"lut[%d]=%d\n",i,(int)lut[i]);
    }
  }

  // assumes something about endian-ness, you might care
  while((c1=getchar())>=0 && (c2=getchar())>=0) putchar(lut[c1|(c2<<8)]);
  if(c1>=0) putchar(lut[c1]); // last byte, zero-padded

  return 0;
}