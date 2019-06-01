#include <iostream>
#include <cassert>

using namespace std;

int convert(int num, int* dig, int base){
    int len=0;
    while(num!=0){
        dig[len]=num%base;
        num=num/base;
        len++;
    }
    return len;
}

bool is_alternating(int num, int base) {
    int dig[30]={0}; int i=0;
    int len=convert(num, dig, base);
    int flag=dig[0]%2;
    for(i=1;i<len;i=i+2){
        if(flag==1){
            if(dig[i]%2!=0) return false;
            if(i+1<len && dig[i+1]%2!=1) return false;
        }
        else if(flag==0){
            if(dig[i]%2!=1) return false;
            if(i+1<len && dig[i+1]%2!=0) return false;
        }
    }
    return true;
}

void test_alternating() {
    assert(!is_alternating(24, 10));  // 24 is not an alternating number in base 10
    // TODO: Add more test cases
    cout << "Alternating number tests passed!" << endl;
}
