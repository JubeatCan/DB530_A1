
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include <string>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr tablePtr, long i) {
	return nullptr;		
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	return nullptr;		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr tablePtr, long i) {
    MyDB_PageHandle pageHandle = getPage(tablePtr, i);
    pageHandle->pinPage();
	return pageHandle;
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
    MyDB_PageHandle pageHandle = getPage();
    pageHandle->pinPage();
	return pageHandle;
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
    this->pageSize = pageSize;
    this->numPages = numPages;
    this->tempFile = tempFile;

    bufferPoll = (char *) malloc((numPages * pageSize) * sizeof(char));

    if (!bufferPoll) {
        perror("Failed to allocate memory.");
        abort();
    }

    for (int i = 0; i < numPages; i++) {
        this -> availableBufferLoc.push(bufferPoll + i * pageSize);
    }

    this -> anonyTotalCount = 0;
    lruManager = make_shared<MyDB_LRUManager>();

}

MyDB_BufferManager :: ~MyDB_BufferManager () {
    free(bufferPoll);
}

char *MyDB_BufferManager::bufferLocForSinglePage() {
    return nullptr;
}

pagePtr MyDB_BufferManager::updateLRUCache(pagePtr) {
    return pagePtr();
}

void MyDB_BufferManager::updateAvailableBufferLoc() {

}

void MyDB_BufferManager::safeExit() {

}

#endif


