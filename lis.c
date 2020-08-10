#include <stdio.h>
#include <math.h>
#define hx 20
#define hy 40
#define wx (2*hx)
#define wy (2*hy)
#define CH '*'
static const float delta = M_PI/4.0;
static const float rate = 1.0f;
static const float dTH = 0.01f;

int x_lis(int a,float theta) {
  return (int)hx*(1.0f-rate*cos(a*theta)); 
}
int y_lis(int b,float theta) {
  return (int)hy*(1.0f-rate*cos(b*theta+delta)); 
}
void clear(char s[wx][wy]) {
  int x,y;
  for (x=0;x<wx;x++) for (y=0;y<wy;y++) s[x][y]=' ';
}
void draw(char s[wx][wy]) {
  int x,y;
  for (x=0;x<wx;x++) {
    for (y=0;y<wy;y++) putchar(s[x][y]);
    putchar('\n');
  }
}
void plot(int a,int b,char s[wx][wy]) {
  float th;
  for (th=0.0;th<2*M_PI;th+=dTH) {
    int x=x_lis(a,th),y=y_lis(b,th);
    s[x][y]=CH;
  }
}
int main(void) {
   char scr[wx][wy];
   for (int a=1;a<7;a++)
     for (int b=1;b<7;b++) { 
       clear(scr); plot(a,b,scr); draw(scr);
     }
}
