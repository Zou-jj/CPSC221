#include <cmath>
#include <iostream>
#include <stack>
#include <queue>

using std::stack;
using std::queue;
using namespace std;

int partition(vector<int> & x, int lo, int hi) {
    int p = lo;
    for( int i=lo+1; i <= hi; i++ )
      if( x[i] < x[lo] ) { p++; swap(x[p], x[i]); }
    swap(x[p], x[lo]);
    printf("p:%d x[p]:%d\n", p, x[p]);
    return p;
}

void qsort(vector<int> & x, int lo, int hi) 
{
  if (lo < hi) {
    int pivot = partition(x, lo, hi); 
    qsort(x, lo, pivot-1);
    qsort(x, pivot+1, hi);
  }
}

int main(){
    printf("hello\n");
    vector<int> a = {1,3,4,2};
    qsort(a, 0, 3);
    for(int index = 0; index < a.size(); index++){
        printf("%d", a[index]);
    }
}