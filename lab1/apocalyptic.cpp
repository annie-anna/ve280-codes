#include <iostream>
#include <cassert>

using namespace std;

bool is_apocalyptic(int num) {
    char str[16000] = {'1'};
    int i = 0, p = 2, j = 0, len = 1; int carrier[16000] = { 0 };

    for (j = 1; j < 16000; j++)str[j] = '0';
    for (j = 0; j < num; j++) {
        for (i = 0; i < len; i++) {
            if ((str[i] - 48)*p + carrier[i] < 10) {
                str[i] = (str[i] - 48)*p + carrier[i] + 48;
                carrier[i] = 0;
            }
            else {
                str[i] = (str[i] - 48)*p + carrier[i] + 38;
                carrier[i] = 0;
                carrier[i + 1]=1;
                if (i == len - 1) {
                    len++;
                }

            }
        }
    }
    for (j = 0; j < len-2; j++) {
        if (str[j] == '6'&& str[j + 1] == '6'&&str[j + 2] == '6')return true;
    }
    return false;
}

void test_apocalyptic() {
    assert(is_apocalyptic(157));  // 2^157 is an apocalyptic number
    assert(!is_apocalyptic(2666)); //2^2666 is not an apocalyptic number
    cout << "apocalyptic number tests passed!" << endl;
}