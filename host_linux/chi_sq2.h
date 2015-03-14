/* 
   Chi-Square Probability Function
   Hacked from librantools.c APA 8/8/2001
*/

double ChiSqP(unsigned long degfree, double x2);
/* Calculates the p-value for the chi-squared distribution with degfree
   degrees of freedom from value x2 */

#define chi_sq2(x,v) ChiSqP(v,x)
/*
   returns the probability P(x<X), where X has a chi-square distribution
   with v degrees of freedom

   included for conformity with APA's other hack, chi_sq.c
*/

