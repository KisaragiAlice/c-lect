#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define L 3
#define INTERVAL 1
static const char *inst[L]= {
   "reset\n", "set size square\n","set parametric\n",
};
char *lis(int a,int b,int d) {
  float delta = (float)M_PI/(d+1);
  static const char *format = "plot cos(%d*t),cos(%d*t+%f)\n";
  static char buff[128];
  sprintf(buff,format,a,b,delta);
  return buff;
}
int main(void) {
  FILE *Gplot;
  if(NULL==(Gplot=popen("gnuplot","w")))
    return -1;
  const int N=5;
  const int delta[]={1,2,3,4,5};
  int d=0;
  for(int i=0;i<L;i++) fprintf(Gplot,inst[i]);
  for(int i=1;i<8;i++)
    for (int j=1;j<8;j++) {
      fprintf(Gplot,lis(i,j,delta[d++%N]));
      fflush(Gplot);
      sleep(INTERVAL);
    }
  pclose(Gplot);
  return 0;
}
