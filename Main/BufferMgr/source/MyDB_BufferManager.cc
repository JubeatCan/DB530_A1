
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include <string>
#include <utility>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr tablePtr, long i) {
    string pageId;
    pagePtr pagePtr;
    char * pagePosition;
    if (idToPage.find(pageId) == idToPage.end()) {
        pagePosition = nextAvailablePage();
        pagePtr = make_shared<MyDB_Page>(tablePtr, i, pagePosition, pageId);
        idToPage[pageId] = pagePtr;
        // readFile from disk
        pagePtr->readFile();
        pagePtr->setBuffer(pagePosition);
    }
    else {
        pagePtr = idToPage.find(pageId)->second;
        // if buffered before
        if (pagePtr->getBuffer() == nullptr) {
            pagePosition = nextAvailablePage();
            pagePtr->setBuffer(pagePosition);
        }
    }
    updateLRUCache(pageId, pagePtr);
    MyDB_PageHandle pageHandle = make_shared<MyDB_PageHandleBase>(pagePtr);
	return pageHandle;
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
    this->tempFile = std::move(tempFile);

    bufferPoll = (char *) malloc((numPages * pageSize) * sizeof(char));

    if (!bufferPoll) {
        perror("Failed to allocate memory.");
        abort();
    }

    for (int i = 0; i < numPages; i++) {
        this -> availableBufferLoc.push(bufferPoll + i * pageSize);
    }

    this -> anonyTotalCount = 0;
    lruManager = make_shared<MyDB_LRUManager>(numPages);

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


