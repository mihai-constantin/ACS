/*
 *  Author: Constantin Mihai - 321CD
 */

#include <iostream>
#include <algorithm>
#include "algo.h"
using namespace std;

int main() {
    
    #ifdef ALGO1
        test_algo1();
    
    #elif ALGO2
        test_algo2();
    
    #endif
    
    return 0;
    
}
