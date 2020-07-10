#include <stdio.h>
void print_qs(int data[],int low,int high) {
     for (int i=low;i<high;i++) printf("[%d]",data[i]);
     puts("");
}
void quicksort(int data[],int low,int high) {
    if (low<high) {
        int i=low,j=high;
        int m=(low+high)/2;
        int pivot=data[m];
        // printf("low=[%d],high=[%d], mid=[%d],pivot=[%d]\n",low,high,m,pivot);
        while (i<=j) {
            while(data[i]<pivot) i=i+1;
            while(pivot<data[j]) j=j-1;
            if (i<=j) {
              // printf("exchanging  i=[%d],j=[%d]\n",i,j);
              int t=data[i];data[i] = data[j];data[j] = t;
              i++;j--;
            }
        }
        quicksort(data,low,j);
        quicksort(data,i,high);
    }
}
void test_quick() {
    int data[] = {58,12,39,90,49,26,68,47,15,39};
    quicksort(data,0,9);
    print_qs(data,0,9);
}
void main(void) {
    test_quick();
} 
