#include <stdio.h>
#define ImageW 360
#define ImageH 240
#define Header 54
#define ImageSize (ImageW*3*ImageH)
const static int red[3]={0,0,-1};   // {B,G,R}
const static int blue[3]={-1,21,0}; // {B,G,R}
const static int white[3]={-1,-1,-1}; // {B,G,R}
#define Ixy(x,y)  (3*(x)+3*(y)*ImageW)
void bit_color(char* image,int x,int y,const int col[3]) {
  int ixy=Ixy(x,y);
  for (int i=0;i<3;i++) *(image+ixy+i)=col[i];
}
void set_(char *p,int offset,char data) { *(p+offset)=data; }
void set_int(char *p,int offset,int data) { *(int*)(p+offset)=data; }
void set_short(char *p,int offset,short data) {*(short*)(p+offset)=data; }
int main(void) {
  char header[Header]={};
  set_(header,0,66); set_(header,1,77);
  set_int(header,2,ImageSize+Header);
  set_int(header,10,Header); set_int(header,14,40);
  set_int(header,18,ImageW); set_int(header,22,ImageH);
  set_short(header,26,1); set_short(header,28,24);

  char image[ImageSize]={};// bitmap data
  for (int y=0;y<ImageH;y++) { // tri-color
    for (int x=0;x<ImageW/3;x++) bit_color(image,x,y,blue); // Blue
    for (int x=ImageW/3;x<ImageW/3*2;x++) bit_color(image,x,y,white); // White
    for (int x=ImageW/3*2;x<ImageW;x++) bit_color(image,x,y,red); // Red
  }
  
  FILE* fp;  
  if (NULL==(fp=fopen("tri-color.bmp","wb"))) return -1;
  fwrite(header,Header,1,fp);
  fwrite(image,ImageSize,1,fp);
  fclose(fp);
  return 0;
}
  
