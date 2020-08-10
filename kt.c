#include <stdio.h>
#include <stdbool.h>
#define M 8
static const short mv_x[M] = {-2,-2,-1,-1,1,1,2,2};
static const short mv_y[M] = {-1,1,-2,2,-2,2,-1,1};
#define N 7
void init(short board[N][N]) {
  short x,y;
  for (x=0;x<N;x++)
    for (y=0;y<N;y++) board[x][y]=-1; //all empty
}
bool safe(short x,short y,short board[N][N]) {
  return (0<=x && x<N) && (0<=y && y<N) && board[x][y]<0;
}
void solution(short board[N][N]) {
  short x,y;
  for (x=0;x<N;x++) {
    for (y=0;y<N;y++)
      printf("[%2d]",board[x][y]);
    putchar('\n');
  }
  putchar('\n'); return;
}
void find(short n,short x,short y,short board[N][N]) {
  if (safe(x,y,board)) {
    board[x][y]=n;  // try to set
    if (n>=N*N-1) solution(board);
    else {
      int k;
      for (k=0;k<M;k++) {
	int dx=mv_x[k],dy=mv_y[k];
	find(n+1,x+dx,y+dy,board); // DFS
      }
    }
    board[x][y]=-1; // undo, reset
  }
  return;
}
int main(void) {
  short board[N][N];
  init(board);
  find(0,0,0,board);
  return 0;
}
