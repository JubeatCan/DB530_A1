
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <memory>
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
	return nullptr;
}

void MyDB_PageHandleBase :: wroteBytes () {

}

void MyDB_PageHandleBase :: pinPage() {
    handlePagePtr->setPinStatus(true);
}

void MyDB_PageHandleBase :: unpinPage() {
    handlePagePtr->setPinStatus(false);
}

MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
    handlePagePtr->decreaseCounter();
}

MyDB_PageHandleBase::MyDB_PageHandleBase(pagePtr handlePagePtr) {
    handlePagePtr = handlePagePtr;
    handlePagePtr->increaseCounter();
}

#endif

