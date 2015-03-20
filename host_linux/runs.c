/**************************************************************************************/
/* runs.c computes the runs test of bits in a binary file                             */
/* APA Consulting, 2000                                                               */
/* Free to everyone forever, not fit for any particular purpose                       */
/* Compiler:  GCC MINGW32 (http://www.xraylith.wisc.edu/~khan/software/gnu-win32)     */
/* Reference: Handbook of Applied Cryptography                                        */
/*            Chapter 5 - Pseudorandom Bits and Sequences                             */
/*            Alfred J. Menezes, Paul C. van Oorschot, and Scott A. Vanstone          */
/*            CRC Press, ISBN: 0-8493-8523-7, 1996                                    */
/*            http://www.cacr.math.uwaterloo.ca/hac/                                  */
/**************************************************************************************/

#define LOGNAME "rng_test.log"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "chi_sq2.h"

void err(char *msg)
{
  if(msg) fprintf(stderr,"\nruns: %s\n",msg);
  fprintf(stderr,"\nUsage: runs [fname]\n");
  fprintf(stderr,"Performs a runs test on a binary file to test for randomness. If [fname] is\n");
  fprintf(stderr,"ommitted then stdin is used. Also writes file 'runs.dat' with details.\n");
  exit(-1);
}

int main(int argc, char *argv[])
{
  int mask[]={1,2,4,8,16,32,64,128};
  int max[]={0,0};
  int c, i, k, k2, state, bit, run;
  unsigned long bytes;
  unsigned long *bg[2];
  double n, ei;
  double x4=0., px4;
  FILE *fo;

  if(argc==1){
    fo=stdin;
    k=32; // we have to guess
  }
  else if(argc==2){
    if((fo=fopen(argv[1],"rb"))==NULL) err("Error opening file for input");
    if(fseek(fo,0L,SEEK_END)<0) err("fseek() positioning error");
    bytes=ftell(fo);
    if(fseek(fo,0L,SEEK_SET)<0) err("fseek() positioning error");
    n=(double)bytes*8.;
    for(k=1;((n-k+3)/pow(2.,k+2))>=5.;k++); k--; /* calculates k */
  }
  else err("Too many arguments");
  if((bg[0]=calloc(k+1,sizeof(unsigned long)))==NULL) err("can't allocate memory");
  if((bg[1]=calloc(k+1,sizeof(unsigned long)))==NULL) err("can't allocate memory");
  c=fgetc(fo);
  bytes=1;
  state=c&mask[0]?1:0;
  run=1;
  bit=1;
  do{
    while(bit<8){
      if((c&mask[bit]?1:0)==state){
        run++;
      }
      else{
        if(run<=k) bg[state][run]++;
	else       bg[state][0]++;
	if(max[state] < run) max[state]=run;
        state=!state;
        run=1;
      }
      bit++;
    }
  bit=0;
  } while((c=fgetc(fo))>=0 && bytes++);
  if(argc==2) fclose(fo);
  else{
    n=(double)bytes*8.;
    for(k2=1;((n-k2+3)/pow(2.,k2+2))>=5.;k2++); k2--;
    if(k2<k) k=k2;
  }
  fo=fopen("runs.dat","w");
  fprintf(fo,"File: %s, %lu bytes\n",argv[1],bytes);
  fprintf(fo," %3s %14s %12s %12s\n","i","ei","Gi","Bi");
  for(i=1;i<=k;i++){
    ei=(n-i+3)/pow(2.,i+2.);
    fprintf(fo," %3d %14.1lf %12lu %12lu\n",i,ei,bg[0][i],bg[1][i]);
    x4+=pow(bg[0][i]-ei,2.)/ei+pow(bg[1][i]-ei,2.)/ei;
  }
  fprintf(fo,">%3d %14s %12lu %12lu\n",k,"",bg[0][0],bg[1][0]);
  fprintf(fo,"Longest Gap=%d Block=%d\n",max[0],max[1]);
  px4=chi_sq2(x4,2.*k-2.);
  fprintf(fo,"x4=%lf px4=%lf\n",x4,px4);
  fclose(fo);
  printf("x4=%lf p-value=%lf\n",x4,px4);
  printf("Test (1%% false rejection): %s\n",0.005<px4&&px4<0.995?"Pass":"Fail");
  fo=fopen(LOGNAME,"a");
  fprintf(fo,"%-27s %-24s %9ld %9.7lf\n","runs",argv[1],bytes,px4);
  fclose(fo);
  free(bg[0]); free(bg[1]);
  return 0;
}
