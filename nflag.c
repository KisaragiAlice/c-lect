#include <stdio.h>
#define ImageW 360
#define ImageH 240
#define Header 54
#define ImageSize (ImageW*3*ImageH)
const static int red[3]={0,0,-1};   // {B,G,R}
const static int blue[3]={-1,21,0}; // {B,G,R}
const static int white[3]={-1,-1,-1}; // {B,G,R}
const static int turmeric[3]={20,191,250};
const static int black[3]={0,0,0};
#define Ixy(x,y)  (3*(x)+3*(y)*ImageW)
void bit_color(char* image,int x,int y,const int col[3]) {
  int ixy=Ixy(x,y);
  for (int i=0;i<3;i++) *(image+ixy+i)=col[i];
}
void set_(char *p,int offset,char data) { *(p+offset)=data; }
void set_int(char *p,int offset,int data) { *(int*)(p+offset)=data; }
void set_short(char *p,int offset,short data) {*(short*)(p+offset)=data; }
#define OX (ImageW/2)
#define OY (ImageH/2)
#define RR (ImageW/5)
int in_circle(int x,int y) { return (x-OX)*(x-OX)+(y-OY)*(y-OY)<=RR*RR;}

// National Flag images
void deutch(char* image) {
  for (int y=0;y<ImageH/3;y++) 
    for (int x=0;x<ImageW;x++) bit_color(image,x,y,turmeric);
  for (int y=ImageH/3;y<ImageH/3*2;y++) 
    for (int x=0;x<ImageW;x++) bit_color(image,x,y,red);
  for (int y=ImageH/3*2;y<ImageH;y++) 
    for (int x=0;x<ImageW;x++) bit_color(image,x,y,black);
}
void france(char* image) {
  for (int y=0;y<ImageH;y++) { // tri-color
    for (int x=0;x<ImageW/3;x++) bit_color(image,x,y,blue); // Blue
    for (int x=ImageW/3;x<ImageW/3*2;x++) bit_color(image,x,y,white); // White
    for (int x=ImageW/3*2;x<ImageW;x++) bit_color(image,x,y,red); // Red
  }
}
void japan(char* image) {
  for (int y=0;y<ImageH;y++) { 
    for (int x=0;x<ImageW;x++)
      if (in_circle(x,y)) bit_color(image,x,y,red); // Red
      else bit_color(image,x,y,white); // White
  }
}
// define Italy
const static int rosso[3]={57,41,206};
const static int bianco[3]={233,238,240};
const static int verde[3]={99,135,0};
void italy(char* image) {
  for (int y=0;y<ImageH;y++) { 
    for (int x=0;x<ImageW/3;x++) bit_color(image,x,y,verde); // Green
    for (int x=ImageW/3;x<ImageW/3*2;x++) bit_color(image,x,y,bianco); // White
    for (int x=ImageW/3*2;x<ImageW;x++) bit_color(image,x,y,rosso); // Red
  }
}
// 応用:ロシア、オランダ、ベルギー、ハンガリー、ポーランド等を作成せよ

int main(void) {
  char header[Header]={};
  set_(header,0,66); set_(header,1,77);
  set_int(header,2,ImageSize+Header);
  set_int(header,10,Header); set_int(header,14,40);
  set_int(header,18,ImageW); set_int(header,22,ImageH);
  set_short(header,26,1); set_short(header,28,24);

  char image[ImageSize]={};// bitmap data
  italy(image); // yet another national_flags
  
  FILE* fp;  
  if (NULL==(fp=fopen("italy.bmp","wb"))) return -1;
  fwrite(header,Header,1,fp);
  fwrite(image,ImageSize,1,fp);
  fclose(fp);

  
  return 0;
}
  
