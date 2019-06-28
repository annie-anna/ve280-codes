#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

int TriangleNumber(int integer);
// EFFECTS: If the integer is a triangle number, return 1; otherwise, return 0
int Palindrome(int integer);
// EFFECTS: If the integer is a palindrome, return 1; otherwise, return 0
int OdiousNumber(int integer);
// EFFECTS: If the integer is an odious number, return 1; otherwise, return 0
int ExtravagantNumber(int integer);
// MODIFIES: integer
// EFFECTS: If the integer is an extravagant number, return 1; otherwise, return 0
int Digit(int integer);
// EFFECTS: return the number of digits of the integer
int Separate(int integer, int* num, int base);
// MODIFIES: integer, num
// EFFECTS: return the number of digits of the integer in targeted base, put each digit of the integer in num

int main() {
	int integer, test, ans = -1;

	cout << "Please enter the integer and the test number: ";
	cin >> integer >> test;
	while (integer > 10000000 || integer <= 0 || test < 1 || test>4) {//invalid inputs
		cout << "Please enter the integer and the test number: ";
		cin >> integer >> test;
	}
	if (test == 1) ans = TriangleNumber(integer);
	else if (test == 2) ans = Palindrome(integer);
	else if (test == 3) ans = OdiousNumber(integer);
	else if (test == 4) ans = ExtravagantNumber(integer);
	cout << ans << endl;
	return 0;
}

int TriangleNumber(int integer) {
	int n = 1;

	while (n*(n + 1) / 2 != integer) {
		if (n*(n + 1) / 2 > integer)return 0;
		n++;
	}
	return 1;
}

int Palindrome(int integer) {
	int num[10] = { 0 }; int start = 0, end;//num[]: store the transformed binary number

	end = Separate(integer, num, 10) - 1;
	while (num[start] == num[end]) {//compare whether the num is symmetric
		start++;
		end--;
		if (start >= end) return 1;
	}
	return 0;
}

int OdiousNumber(int integer) {
	int bin[30] = { 0 }; int len = 0, i, s = 0;//s is number of 1

	len = Separate(integer, bin, 2);//transform an integer to binary and return the number of digits
	for (i = 0; i < len; i++) {//count number of 1
		if (bin[i] == 1) s++;
	}
	if (s % 2 == 1)return 1;
	else return 0;
}

int ExtravagantNumber(int integer) {
	int len = 0, i; int prime[30] = { 0 }, power[30] = { 0 };//prime[]: store non-repeated prime of prime factorization;power[]:store power of prime factorization
	int dig_prime = 0, dig_power = 0, dig_integer = 0, flag = 0;//dig_prime: number of digits of prime;dig_power: number of digits of power; dig_integer: number of digits of integer; flag: whether the prime is repeated

	dig_integer = Digit(integer);
	for (i = 2; i <= sqrt(integer); i = i + 2) {//find prime factor
		while (integer % i == 0) {//whether j is a prime factor
			flag = 1;
			prime[len] = i;
			power[len]++;
			integer = integer / i;
		}
		if (flag == 1) { len++; flag = 0; }//reset flag for a potential new prime factor
		if (i == 2) i = 1;//difference of every prime factor is at least 2 except for 2 and 3
	}
	if (integer != 1) {
		prime[len] = integer;
		power[len]++;
		len++;
	}
	for (i = 0; i < len; i++) {
		dig_prime = dig_prime + Digit(prime[i]);
		if (power[i] >= 2)dig_power = dig_power + Digit(power[i]);//power[k]=1 should not be counted into total digits
	}
	if (dig_integer < dig_prime + dig_power) return 1;
	else return 0;
}

int Digit(int integer) {
	int num[10] = { 0 };

	return Separate(integer, num, 10);
}

int Separate(int integer, int* num, int base) {
	int len = 0;

	while (integer != 0) {
		num[len] = integer % base;
		integer = integer / base;
		len++;
	}
	return len;
}
