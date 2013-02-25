#include <iostream>
#include "list.h"
#include "debug.h"

using cpp_lab1::List;
bool testNewListIsEmpty(){
	List a;
	return a.empty();
}

bool testNotEmptyAfterInsert() {
	List a;
	a.insert(4);
	return !a.empty();
}

bool testEmptyAfterInsertAndRemove() {
	List a;
	a.insert(3);
	a.remove(3,List::EQUAL);
	return a.empty();
}

bool testRemoveFirstElement() {
	List a;
	a.insert(3);
	a.insert(5);
	a.insert(8);
	int ps = a.size();
	a.remove(8,List::EQUAL);
	return a.size() + 1 == ps;
}

bool testRemoveLastElement() {
	List a;
	a.insert(3);
	a.insert(5);
	a.insert(8);
	int ps = a.size();
	a.remove(3,List::EQUAL);
	return a.size() + 1 == ps;
}

int main() {
	TRACE("testNewListIsEmpty");
	assert(testNewListIsEmpty());
	TRACE("testNotEmptyAfterInsert");
	assert(testNotEmptyAfterInsert());
	TRACE("testEmptyAfterInsertAndRemove");
	assert(testEmptyAfterInsertAndRemove());
	TRACE("testRemoveFirstElement");
	assert(testRemoveFirstElement());
	TRACE("testRemoveLastElement");
	assert(testRemoveLastElement());

}
