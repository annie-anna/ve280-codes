#include <iostream>
#include <cassert>

using namespace std;

int factorial(int n){
    if(n==0) return 1;
    else return (n*factorial(n-1));
}

bool is_jordan_polya(int num) {
    int i;

    for (i = 0; i < 11; i++) {
        if (num == factorial(i))return true;
        if (num < factorial(i))break;
    }
    for (i = 2; i < 11; i++) {
        if (num%factorial(i) == 0) {
            if (is_jordan_polya(num / factorial(i)))return true;
        }
    }
    return false;
}

void test_jordan_polya() {
    assert(!is_jordan_polya(5));  // 5 is not a Jordan-Polya number
    // TODO: Add more test cases
    cout << "Jordan-Polya number tests passed!" << endl;
}
