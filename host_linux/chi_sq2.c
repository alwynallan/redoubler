/*
   Hacked from librantools.c APA 8/8/2001

   Reported to be translated from Ritter's JavaScript in
	http://www.ciphersbyritter.com/JAVASCRP/NORMCHIK.HTM

   Ritter references Peizer & Pratt from Ling, 1978, JASA 73: 274-283
*/

#include "chi_sq2.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
  #define M_PI 3.14159265358979323846264338327950288419716939
#endif

/* Calculate the p-value for the normal distribution from x */

double NormalP(double x)
{
    double
      d1 = 0.0498673470,
      d2 = 0.0211410061,
      d3 = 0.0032776263,
      d4 = 0.0000380036,
      d5 = 0.0000488906,
      d6 = 0.0000053830;

   double a = fabs(x);
   double t = 1.0 + a*(d1+a*(d2+a*(d3+a*(d4+a*(d5+a*d6)))));

   // to 16th power
   t *= t;  t *= t;  t *= t;  t *= t;
   t = 1.0 / (t+t);  // the MINUS 16th

   if (x >= 0)  t = 1.0 - t;
   return(t);
}

/* Calculate the p-value for the chi-squared distribution with degfree
   degrees of freedom from value x2 */
double ChiSqPN(unsigned long degfree, double x2)
{
   double d, z, s = degfree - 1;

   if (fabs(x2 - s) < 0.1) {
      z = ((double)1.0/3.0) + (0.08/degfree);
      z = -z / sqrt(s+s);
      }
   else {
      d = x2 - degfree + ((double)2.0/3.0) - ((double)0.08/degfree);
      if(degfree==1)
         z = sqrt(x2);
      else
         z = sqrt((s * log(s/x2)) + x2 - s);
      z = (d * z) / fabs(x2-s);
      }

   return NormalP(z);
}

double ChiSqP(unsigned long degfree, double x2 )
{
   double  p, t;
   unsigned long k, a;

   if (degfree >= 50)  return ChiSqPN( degfree, x2 );
   else {

      p = exp( -x2 / 2 );

      if ((degfree & 1) > 0) p *= sqrt( (x2+x2) / M_PI );

      k = degfree;
      while (k >= 2) {
         p *= x2 / k;
         k -= 2;
         }

      t = p;  a = degfree;
      while (t > (1e-7 * p)) {
         a += 2;
         t *= x2 / a;
         p += t;
         }

      return p;
      }
   }
