#include<iostream>
#include<cstdlib>
#include "p2.h"
using namespace std;

int size(list_t list);
// EFFECTS: Returns the number of elements in "list".
// Returns zero if "list" is empty.

bool memberOf(list_t list, int val);
// EFFECTS: Returns true if the value "val" appears in "list".
// Returns false otherwise.

int dot(list_t v1, list_t v2);
// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
// product of the two vectors. If one list is longer
// than the other, ignore the longer part of the vector.

bool isIncreasing(list_t v);
// EFFECTS: Checks if the list of integers is increasing.
// A list is increasing if and only if no element
// is smaller than its previous element. By default,
// an empty list and a list of a single element are
// increasing.

list_t reverse(list_t list);
// EFFECTS: Returns the reverse of "list".

list_t append(list_t first, list_t second);
// EFFECTS: Returns the list (first second).

bool isArithmeticSequence(list_t v);
// EFFECTS: Checks if the list of integers forms an
// arithmetic sequence. By default, an empty list and
// a list of a single element are arithmetic sequences.

list_t filter_odd(list_t list);
// EFFECTS: Returns a new list containing only the elements of the
// original "list" which are odd in value,
// in the order in which they appeared in list.

list_t filter(list_t list, bool(*fn)(int));
// EFFECTS: Returns a list containing precisely the elements of "list"
// for which the predicate fn() evaluates to true, in the
// order in which they appeared in list.

list_t unique(list_t list);
// EFFECTS: Returns a new list comprising of each unique element
// in "list". The order is determined by the first
// occurrence of each unique element in "list".

list_t insert_list(list_t first, list_t second, unsigned int n);
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
// "first", followed by all elements of "second",
// followed by any remaining elements of "first".

list_t chop(list_t list, unsigned int n);
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
// elements.

static bool odd(int num);
// EFFECTS: Returns true is num is odd, returns false otherwise.

static list_t unique_helper(list_t list);
// EFFECTS: Returns a new list comprising of each unique element
// in "list". The order is determined by the last
// occurrence of each unique element in "list". 

static list_t reserve_list_n(list_t list, int n);
// EFFECTS��Returns a new list consisting of the first n elements in list.

static list_t delete_list_n(list_t list, int n);

// EFFECTS: Returns a new list that deletes the first n elements in list.

int tree_sum(tree_t tree);
// EFFECTS: Returns the sum of all elements in "tree".
// Returns zero if "tree" is empty.

bool tree_search(tree_t tree, int val);
// EFFECTS: Returns true if the value "val" appears in "tree".
// Returns false otherwise.

int depth(tree_t tree);
// EFFECTS: Returns the depth of "tree", which equals the number of
// layers of nodes in the tree.
// Returns zero if "tree" is empty.

int tree_max(tree_t tree);
// REQUIRES: "tree" is non-empty.
//
// EFFECTS: Returns the largest element in "tree".

list_t traversal(tree_t tree);
// EFFECTS: Returns the elements of "tree" in a list using an
// in-order traversal. An in-order traversal prints
// the "left most" element first, then the second-left-most,
// and so on, until the right-most element is printed.

bool tree_hasMonotonicPath(tree_t tree);
// EFFECTS: Returns true if and only if "tree" has at least one
// root-to-leaf path such that all the elements along the
// path form a monotonically increasing or decreasing
// sequence.

bool tree_allPathSumGreater(tree_t tree, int sum);
// REQUIRES: tree is not empty
//
// EFFECTS: Returns true if and only if for each root-to-leaf
// path of "tree", the sum of all elements along the path
// is greater than "sum".

bool covered_by(tree_t A, tree_t B);
// EFFECTS: Returns true if tree A is covered by tree B.

bool contained_by(tree_t A, tree_t B);
// EFFECTS: Returns true if tree A is covered by tree B
// or a subtree of B.

static int max(int a, int b);
// EFFECTS: Returns the maximum of a and b.

static bool tree_hasMonotonicPath_helper(tree_t tree, bool(*fn)(int,int));
// EFFECTS: Returns true if there exists a monotonic path in left
// subtree or right subtree.

static bool increase(int a, int b);
// EFFECTS: Returns true if a<=b.

static bool decrease(int a, int b);
// EFFECTS��Returns true is a>=b.

static bool contained_by_helper(tree_t A, tree_t B, tree_t(*fn)(tree_t));
// EFFECTS: Returns true if A is contained by B.

tree_t insert_tree(int elt, tree_t tree);
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that
// the resulting tree is also a sorted binary tree.

int size(list_t list) {
	if (list_isEmpty(list)) return 0;
	return (1 + size(list_rest(list)));
}

bool memberOf(list_t list, int val) {
	if (list_isEmpty(list))return false;
	if (list_first(list) == val) return true;
	return memberOf(list_rest(list), val);
}

int dot(list_t v1, list_t v2) {
	if (size(v1) == 1 || size(v2) == 1) return list_first(v1)*list_first(v2);
	return (list_first(v1)*list_first(v2) + dot(list_rest(v1), list_rest(v2)));
}

bool isIncreasing(list_t v) {
	if (size(v) == 0 || size(v) == 1) return true;
	if (list_first(v) <= list_first(list_rest(v))) return isIncreasing(list_rest(v));
	return false;
}

list_t reverse(list_t list) {
	if (size(list) == 0) return list;
	return append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
}

list_t append(list_t first, list_t second) {
	if (list_isEmpty(first)) return second;
	return list_make(list_first(first), append(list_rest(first), second));
}

bool isArithmeticSequence(list_t v) {
	int vsize = size(v);
	if (vsize == 0 || vsize == 1 || vsize == 2) return true;
	if (list_first(v) + list_first(list_rest(list_rest(v))) == 2 * list_first(list_rest(v)))
		return isArithmeticSequence(list_rest(v));
	return false;
}

list_t filter_odd(list_t list) {
	return filter(list, odd);
}

static bool odd(int num){
	if (num % 2 != 0) return true;
	return false;
}

list_t filter(list_t list, bool(*fn)(int)) {
	if (list_isEmpty(list))return list;
	if (fn(list_first(list)))
		return list_make(list_first(list), filter(list_rest(list),fn));
	return filter(list_rest(list), fn);
}

list_t unique(list_t list) {
	return unique_helper(reverse(list));
}

static list_t unique_helper(list_t list) {
	if (size(list) == 0 || size(list) == 1)return list;

	list_t unique_list = unique_helper(list_rest(list));
	int first = list_first(list);
	if (memberOf(unique_list, first))
		return unique_list;
	return append(unique_list,list_make(first,list_make()));
}

list_t insert_list(list_t first, list_t second, unsigned int n) {
	list_t v1 = reserve_list_n(first, n);
	list_t v2 = delete_list_n(first, n);
	return append(append(v1, second), v2);
}

static list_t reserve_list_n(list_t list, int n) {
	if (n == size(list))return list;
	if (n == 0) return list_make();
	return list_make(list_first(list), reserve_list_n(list_rest(list), n - 1));
}

static list_t delete_list_n(list_t list, int n) {
	if (n == size(list)) return list_make();
	if (n == 0) return list;
	return delete_list_n(list_rest(list), n - 1);
}

list_t chop(list_t list, unsigned int n) {
	return reserve_list_n(list, size(list) - n);
}

int tree_sum(tree_t tree) {
	if (tree_isEmpty(tree)) return 0;
	return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int val) {
	if (tree_isEmpty(tree)) return false;
	if (val == tree_elt(tree)) return true;
	return (tree_search(tree_left(tree), val) || tree_search(tree_right(tree), val));
}

int depth(tree_t tree) {
	if (tree_isEmpty(tree)) return 0;
	return(max(depth(tree_left(tree)), depth(tree_right(tree)))+1);
}

static int max(int a, int b) {
	if (a >= b) return a;
	return b;
}

int tree_max(tree_t tree) {
	int elt = tree_elt(tree);
	if (depth(tree) == 1)return tree_elt(tree);

	tree_t left = tree_left(tree);
	tree_t right = tree_right(tree);
	if (!tree_isEmpty(left)) {
		if(!tree_isEmpty(right))
			return max(elt, max(tree_max(left), tree_max(right)));
		else return max(elt, tree_max(left));
	}
	else return max(elt, tree_max(right));
}

list_t traversal(tree_t tree) {
	if (tree_isEmpty(tree)) return list_make();

	list_t list_top = list_make(tree_elt(tree), list_make());
	list_t temp = append(traversal(tree_left(tree)), list_top);
	return append(temp, traversal(tree_right(tree)));
}

bool tree_hasMonotonicPath(tree_t tree) {
	return (tree_hasMonotonicPath_helper(tree, increase) || tree_hasMonotonicPath_helper(tree, decrease));
}

static bool tree_hasMonotonicPath_helper(tree_t tree, bool(*fn)(int,int)) {
	if (tree_isEmpty(tree))return false;
	if (depth(tree) == 1)return true;

	tree_t left = tree_left(tree);
	tree_t right = tree_right(tree);
	int ans1=0, ans2=0;
	int elt = tree_elt(tree);
	if (!tree_isEmpty(left)) {
		if (fn(elt,tree_elt(left))) ans1 = tree_hasMonotonicPath_helper(left,fn);
	}
	if (ans1) return true;
	if(!tree_isEmpty(right)) {
		if (fn(elt,tree_elt(right))) ans2 = tree_hasMonotonicPath_helper(right,fn);
	}
	if (ans2) return true;
	else return false;
}

static bool increase(int a, int b) {
	if (a <= b) return true;
	else return false;
}

static bool decrease(int a, int b) {
	if (a >= b) return true;
	else return false;
}

bool tree_allPathSumGreater(tree_t tree, int sum) {
	int elt = tree_elt(tree);
	if (depth(tree) == 1) {
		if (elt > sum) return true;
		return false;
	}
	tree_t left=tree_left(tree);
	tree_t right = tree_right(tree);
	if (!tree_isEmpty(left)) {
		if (!tree_isEmpty(right)) {
			if (tree_allPathSumGreater(left, sum - elt)&& tree_allPathSumGreater(right, sum - elt))
				return true;
			else return false;
		}
		else {
			if (tree_allPathSumGreater(left, sum - elt)) return true;
			else return false;
		}
	}
	else {
		if (tree_allPathSumGreater(right, sum - elt)) return true;
		else return false;
	}
}

bool covered_by(tree_t A, tree_t B) {
	if (tree_isEmpty(A)) return true;
	if (tree_isEmpty(B)) {
		if (tree_isEmpty(A)) return true;
		return false;
	}
	if (tree_elt(A)== tree_elt(B)) {
		return (covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B)));
	}
	else return false;
}

bool contained_by(tree_t A, tree_t B) {
	return(contained_by_helper(A, B, tree_left) || contained_by_helper(A, B, tree_right));
}

static bool contained_by_helper(tree_t A, tree_t B, tree_t (*fn)(tree_t)) {
	if (covered_by(A, B)) return true;
	if (tree_isEmpty(B))return false;
	B = fn(B);
	if (contained_by_helper(A, B, tree_left) || contained_by_helper(A, B, tree_right))
		return true;
	return false;
}

tree_t insert_tree(int elt, tree_t tree) {
	tree_t empty_tree = tree_make();
	if (tree_isEmpty(tree))
		return tree_make(elt, empty_tree, empty_tree);

	tree_t left = tree_left(tree);
	tree_t right = tree_right(tree);
	int top_elt = tree_elt(tree);
	if (depth(tree) == 1) {
		if (elt < top_elt)
			return tree_make(top_elt, tree_make(elt, empty_tree, empty_tree), right);
		else return tree_make(top_elt, left, tree_make(elt, empty_tree, empty_tree));
	}
	if (elt < top_elt)
		return tree_make(top_elt,insert_tree(elt, left),right);
	else return tree_make(top_elt,left,insert_tree(elt, right));
}