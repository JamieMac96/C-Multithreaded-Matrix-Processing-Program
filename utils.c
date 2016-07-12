#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

float getTime(){
  double t;
  struct timeval myTime;
  gettimeofday(&myTime, NULL);
  return t = myTime.tv_sec+(myTime.tv_usec/1000000.0);
}
