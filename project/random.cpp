//This file includes all functions that return random variables.

#include "global.h"
#include "random.h"
#include <time.h>


int uniformInt()
{
  //return a result for a link delay between 1 and 10 seconds.
  return rand() % 10 + 1;
}


double uniformDouble()
{
  //return a value for bandwidth between 0 and 1 mbps
	return (double)rand() / (double)RAND_MAX;
}

double exponential(double lambda)
{
  //return a random variable using exponential distribution with given lambda
  return (-1.0/lambda)*(log(uniformDouble()));
}
