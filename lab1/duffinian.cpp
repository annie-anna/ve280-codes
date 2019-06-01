#include <iostream>
#include<cmath>
#include <cassert>

using namespace std;

int prime(int num, int* divisor) {
    int i = 2, len = 0;
    for (i = 2; i <= sqrt(num); i++) {
        if (num%i == 0) {
            divisor[len] = i;
            len++;
            if (i != sqrt(num)) {
                divisor[len] = num / i;
                len++;
            }
        }

    }
    return len;
}

bool is_duffinian(int num) {
    int i = 0, j = 0, slen = 0, sum = 0; int divisor[50] = { 0 }, sdivisor[50] = { 0 };
    int len = prime(num, divisor);
    if (len == 0) return false;
    divisor[len] = 1;
    len++;
    divisor[len] = num;
    len++;
    for (i = 0; i < len; i++) {
        sum = sum + divisor[i];
    }
    if (sum % 2 == 0 && num % 2 == 0) return false;
    slen = prime(sum, sdivisor);
    if (slen == 0)return true;
    for (i = 0; i < len; i++) {
        for (j = 0; j < slen; j++) {
            if (divisor[i] == sdivisor[j])return false;
        }
    }
    return true;
}

void test_duffinian() {
    assert(!is_duffinian(6));  // 6 is not a Duffinian number
    // TODO: Add more test cases
    cout << "Duffinian number tests passed!" << endl;
}
