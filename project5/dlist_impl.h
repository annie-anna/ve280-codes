#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__
template <class T>
bool Dlist<T>::isEmpty() const {
	return(first==nullptr||last==nullptr);
}

template<class T>
void Dlist<T>::insertFront(T *op) {
	node* np = new node;
	np->op = op;
	np->next = first;
	np->prev = nullptr;
	if(!isEmpty())first->prev = np;
	else last = np;
	first = np;
}

template<class T>
void Dlist<T>::insertBack(T *op) {
	node* np = new node;
	np->op = op;
	np->prev = last;
	np->next = nullptr;
	if (!isEmpty())last->next = np;
	else first = np;
	last = np;
}

template<class T>
T * Dlist<T>::removeFront() {
	if (isEmpty()) {
		emptyList e;
		throw e;
	}
	node* victim = first;
	T* result = first->op;
	first = first->next;
	if (isEmpty()) last = first;
	else first->prev = nullptr;
	delete victim;
	return result;
}

template<class T>
T * Dlist<T>::removeBack() {
	if (isEmpty()) {
		emptyList e;
		throw e;
	}
	node* victim = last;
	T* result = last->op;
	last = last->prev;
	if (isEmpty()) first = last;
	else last->next = nullptr;
	delete victim;
	return result;
}

template<class T>
Dlist<T>::Dlist() :first(0), last(0) {}

template<class T>
Dlist<T>::Dlist(const Dlist<T> &l) {
	first = nullptr;
	last = nullptr;
	copyAll(l);
}

template<class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l) {
	if (this != &l) {	
		removeAll();
		copyAll(l);
	}
	return *this;
}

template<class T>
Dlist<T>::~Dlist() {
	removeAll();
}

template<class T>
void Dlist<T>::removeAll() {
	while (!isEmpty()) {
		T* op = removeFront();
		delete op;
	}
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
	T* op = new T(*(l.last)->op);
	insertFront(op);
	node* current = (l.last)->prev;
	while (current!=nullptr) {
		T* op = new T(*current->op);
		insertFront(op);
		current = current->prev;
	}
}
#endif
