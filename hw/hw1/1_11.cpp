#include <iostream>
#include "time.h"
using namespace std;

int fun(int n) {
    int r;
    int s = 0;
    for (int q = 1; q < n; q++)
        s = s + q;
    for (r = s; r > 2; r--)
        s--;
    return r * s;
}

int main()
{
    /* clock_t clock(void) returns the number of clock ticks 
       elapsed since the program was launched.To get the number  
       of seconds used by the CPU, you will need to divide by  
       CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical 
       32 bit system.  */
    clock_t start, end; 
  
    /* Recording the starting clock tick.*/
    start = clock(); 
  
    int a = fun(10); 
  
    // Recording the end clock tick. 
    end = clock(); 
  
    // Calculating total time taken by the program. 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << a << endl;
    cout << "Time taken by program is : " << fixed  
         << time_taken; 
    cout << " sec " << endl; 
    return 0; 
}