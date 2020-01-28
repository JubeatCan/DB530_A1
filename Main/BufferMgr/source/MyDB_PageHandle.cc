
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {
	char * bufferLoc = handlePagePtr->getBuffer();
	if (bufferLoc == nullptr) {
        handlePagePtr->bufferMe();
        bufferLoc = handlePagePtr->getBuffer();
	}
	//update lru
	handlePagePtr->lruUpdateToHead();
    return bufferLoc;
}

void MyDB_PageHandleBase :: wroteBytes () {
    //update lru
    handlePagePtr->lruUpdateToHead();
    handlePagePtr->setDirty(true);
}

void MyDB_PageHandleBase :: pinPage() {
    handlePagePtr->setPinStatus(true);
}

void MyDB_PageHandleBase :: unpinPage() {
    handlePagePtr->setPinStatus(false);
}

MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
//    cout << handlePagePtr->getNumberOfHandler() << endl;
    handlePagePtr->decreaseCounter();
    // Anon + ram -> removefromLRU  pagehandle#
    if (handlePagePtr->getNumberOfHandler() == 0) {
        if (!handlePagePtr->getAnonymous() && handlePagePtr->getPinStatus()) {
            handlePagePtr->setPinStatus(false);
        }
        else if (handlePagePtr->getAnonymous() && handlePagePtr->getBuffer() != nullptr){
            handlePagePtr->setPinStatus(false);
            handlePagePtr->evictMe();
            handlePagePtr->setBuffer(nullptr);
        }
    }
}

MyDB_PageHandleBase::MyDB_PageHandleBase(pagePtr handlePagePtr) {
    this -> handlePagePtr = handlePagePtr;
    handlePagePtr->increaseCounter();
}

#endif

