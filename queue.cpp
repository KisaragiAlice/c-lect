#include <iostream>
using namespace std;
/**　目的： 
 * キューを題材としたクラス、オブジェクトの使い方と、　
 * 例外ハンドリングについて理解を深める
*/
/** キューが空っぽを意味する例外クラス std::exceptionを継承し、識別する */
class EmptyException: std::exception {};
/** キューが満杯を意味する例外クラス std::exceptionを継承し、識別する */
class FullException: std::exception {};

/** 待ち行列キューを表すクラス定義　
 *   メソッド: int dequeue(),   void enqueue(int value)
 *          bool isEmpty(), isFull()
 * 　内部に保持するデータはint型の配列　// Todo pair<string,int>対応
 *   例外発生確認のため、あえてサイズ(Q_LIMIT)は小さめに設定
*/
class Queue {
private:  
  static const int Q_LIMIT=16; // tiny size 
  int data[Q_LIMIT];
  int head=0;int tail=0;
public:
  Queue():head(0),tail(0){}
  ~Queue() { cerr<<"Q deleted."<<endl; } // delete []&data ->NG
  bool isEmpty() { return head==tail; }
  bool isFull() { return head== (tail+1) % Q_LIMIT; }
  int dequeue() {
    if (isEmpty()) throw new EmptyException();
    int value=data[head];
    head=(head+1) % Q_LIMIT;
    return value;
  }
  void enqueue(int value) {
    if (isFull()) throw new FullException();
    data[tail]=value;
    tail=(tail+1) % Q_LIMIT;
  }  
};
/** 単なる格納用ダミーデータ*/
static const int N=12;
static int sample[N]={1,1,2,3,5,8,13,21,34,55,89,55+89};
/**  Queueの利用例 例外対応(1)　
 *   Full例外を捕捉する、作為的な操作
 *  enqueue()>dequeue()　
 * 　Full例外時の本来対応は、enqueue()をwait()して、dequeue()優先で空きを作る
 * 　ここでは、例外を受けたら、オブジェクトを削除して処理を停止　　
*/
void test_full(void) {
  Queue *que = new Queue();
  int c=0;  
  while(true) 
    try {  // enqueue() > dequeue() -> Full Q
	  for (int i=0;i<N;i++) {
     	      que->enqueue(sample[c]);
	      cout << "<<< enqueue:"<< sample[c] << endl;c=(c+1)%N;
          }
          for (int i=0;i<N-3;i++)
              cout << ">> dequeue:" << que->dequeue() << endl;
     } catch (FullException  *f) {
        cerr<< "Caught except: Full Q^" << endl; delete que; delete f;return;
     } catch (EmptyException *e) {
        cerr<< "Caught except: Empty Q^" << endl; delete que; delete e;return;
     } catch (std::exception *e) {
        cerr<< "Caught std::exception^" << e->what()<< endl; delete que; delete e;return;
     } catch (...) { cerr<< "anonymous exception^" << endl; delete que; throw; }
}
/**  Queueの利用例 例外対応(2)　
 *   Empty例外を捕捉する、作為的な操作
 *   enqueue() < dequeue()　
 * 　 Empty例外時の本来対応は、dequeue()をwait()して、enqueue()優先でデータを受け取る
 * 　ここでは、例外を受けたら、オブジェクトを削除して処理を停止　　
*/
void test_empty() { // enqueue() < dequeue() -> Empty Q
  Queue *que = new Queue();
  for (int c=0;true;) 
     try { 
         for (int i=0;i<N-3;i++) {
     	      que->enqueue(sample[c]);
	      cout << "<< enqueue:"<< sample[c] << endl; c=(c+1)%N;
         }
         for (int i=0;i<N;i++)
             cout << ">>> dequeue:" << que->dequeue() << endl;
     } catch (FullException  *f) {
        cerr<< "Caught except: Full Q^" << endl; delete que; delete f;return;
     } catch (EmptyException *e) {
        cerr<< "Caught except: Empty Q^" << endl; delete que; delete e;return;
     } catch (std::exception *e) {
        cerr<< "Caught std::exception^" << e->what()<< endl; delete que; delete e;return;
     } catch (...) { cerr<< "anonymous exception^" << endl; delete que; throw; }
}

int main(void) {
  set_terminate([](){cerr<<"on terminate()->exit(1);"<<endl; exit(1);});
  try {
    test_full(); test_empty();
  } catch (std::exception *e) { cerr<< "std::exception, " << e->what() << endl; return -1; }
}
