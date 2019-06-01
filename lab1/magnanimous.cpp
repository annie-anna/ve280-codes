#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

bool is_magnanimous(int num) {
    int len=0,i=0,j=0,divisor=1; int sum[10]={0};
    int integer=num;
    while(integer!=0){
        integer=integer/10;
        len++;
    }
    for(i=0;i<len-1;i++){
        divisor=divisor*10;
        sum[i]=num/divisor+num%divisor;
    }
    for(i=0;i<len-1;i++){
        for(j=2;j<=sqrt(sum[i]);j++){
            if(sum[i]%j==0) return false;
        }
    }
    return true;
}

void test_magnanimous() {
    assert(!is_magnanimous(15));  // 15 is not a magnanimous number
    // TODO: Add more test cases
    cout << "Magnanimous number tests passed!" << endl;
}
