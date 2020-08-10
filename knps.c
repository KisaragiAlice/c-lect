#include <stdio.h>
#include <stdlib.h>
typedef struct _item {
  char  *name;
  short value;
  short weight;
  struct _item *nex;
} Item;
Item *add(Item *list,Item *it) {
  Item *p; for(p=list;p->nex!=NULL;p=p->nex);
  p->nex=it;
}
#define N 7
Item *set_problem(void) {
  static Item items[N]={
    {"diamond",5,4,NULL},{"saphire",5,3,NULL},{"emerald",7,3,NULL},
    {"ruby",8,4,NULL},{"pearl",4,1,NULL},{"gold",9,5,NULL},{"plutinum",11,6,NULL}};
  int i;
  for (i=1;i<N;i++) add(&items[0],&items[i]);
  return &items[0];
}
int maxval_knapsack(Item *select,int rest_w) {
  if (rest_w==0 || select==NULL) return 0;
  else  
    if (select->weight > rest_w)  //too heavy,skip it
       return maxval_knapsack(select->nex,rest_w);
    else {
      Item *candidate = select;
      int val_in  = maxval_knapsack(select->nex,rest_w-(candidate->weight));
      val_in += select->value;
      int val_out = maxval_knapsack(select->nex,rest_w);
      return (val_in > val_out) ? val_in : val_out;
    }
}
int main(void) {
  Item *items = set_problem();
  int capacity=10;
  int ans = maxval_knapsack(items,capacity);
  printf("Max value %d\n",ans); return ans;
}
