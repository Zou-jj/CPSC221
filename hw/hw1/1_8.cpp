#include <iostream>
#include "time.h"
using namespace std;

static long timeCount = 0;

int coffee(int n) {
    int s = n * n;
    for (int q = 0; q < n; q++)
        s = s - q;
        timeCount++;
    for (int q = n; q > 0; q--)
        s = s - q;
        timeCount++;
    return s + 2;
}

int mocha(int n) {
    int r = 0;
    for (int i=0; i<=n; i = i+16)
        for (int j=0; j<i; j++)
            r++;
            timeCount++;
    return r;
}

int fun(int n) {
    int j=0;
    for (int k = 16; coffee(k) * mocha(k) - k <= n; k+=16) {
        j++;
        timeCount++;
        // cout << "I am having so much pain with asymptotics!" << endl;
    }
    return j;
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
  
    int a = fun(16*100000000); 
  
    // Recording the end clock tick. 
    end = clock(); 
  
    // Calculating total time taken by the program. 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << a << endl;
    cout << "Time taken by program is : " << fixed  
         << time_taken; 
    cout << " sec " << endl; 
    cout << "Time count is " << timeCount << endl;
    return 0; 
}