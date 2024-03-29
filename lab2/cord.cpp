#include <string>
#include<iostream>
#include "cord.h"

using namespace std;

size_t cord_length(cord_t R) {
    if (R == nullptr) {
        return 0;
    } else {
        return R->len;
    }
}

cord_t cord_new(const std::string &s) {
    if (s.length()) {
        return new cord{s.length(), nullptr, nullptr, s};
    } else {
        return nullptr;
    }
}

cord_t cord_join(cord_t R, cord_t S) {
    if (R == nullptr) {
        return S;
    }
    if (S == nullptr) {
        return R;
    }
    return new cord{cord_length(R) + cord_length(S), R, S, ""};
}

string cord_tostring(cord_t R) {
    // TODO: Your implementation here
	if (R->left == nullptr && R->right == nullptr) return R->data;
	else return cord_tostring(R->left)+ cord_tostring(R->right);
}

char cord_charat(cord_t R, size_t i)
/*@requires 0 <= i && i < cord_length(R); @*/
{
    // TODO: Your implementation here
	if (R->left == nullptr && R->right == nullptr) return (R->data)[i];
	else if (i < (R->left)->len) return cord_charat(R->left,i);
	else return cord_charat(R->right,i - (R->left)->len);
}

cord_t cord_sub(cord_t R, size_t lo, size_t hi)
/*@requires 0 <= lo && lo <= hi && hi <= cord_length(R); @*/
{
    // TODO: Your implementation here
	if (lo == hi)return nullptr;
	if (lo == 0 && hi == cord_length(R))return R;
	if (R->left == nullptr && R->right == nullptr) 
		return cord_new((R->data).substr(lo, hi - lo));
	if (hi <= (R->left)->len) 
		return cord_join(cord_sub(R->left, lo, hi), nullptr);
	if (lo >= (R->left)->len) 
		return cord_join(nullptr, cord_sub(R->right, lo - (R->left)->len, hi - (R->left)->len));
	return cord_join(cord_sub(R->left, lo, (R->left)->len), cord_sub(R->right, 0, hi - (R->left)->len));
}

void cord_print(cord_t R) {
	if (R == nullptr) { cout << "( )"; return; }
	if (R->left == nullptr && R->right == nullptr) {
		cout << "( \"" << R->data << "\" )";
		return;
	}
	cout << "( ";
	cord_print(R->left);
	cout << " ";
	cord_print(R->right);
	cout << " )";
	return;
}

bool is_cord(cord *c) {
    if (c == nullptr) {
        return true;
    }
    if (c->left == nullptr && c->right == nullptr && c->len && c->len == c->data.length()) {
        return true;
    }
    if (c->left != nullptr && c->right != nullptr) {
        if (c->left->len == 0 || c->right->len == 0 | c->len != c->left->len + c->right->len) {
            return false;
        }
        if (is_cord(c->left) && is_cord(c->right)) {
            return true;
        }
    }
    return false;
}
