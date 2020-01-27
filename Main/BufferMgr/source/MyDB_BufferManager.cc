
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include <string>
#include <utility>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr tablePtr, long i) {
    string pageId = tablePtr->getName() + "_" + to_string(i);
    pagePtr pagePtr;
    char * pageBufferPosition;
    if (idToPage.find(pageId) == idToPage.end()) {
        pageBufferPosition = nextAvailablePosition();
        // pin->false anony->false
        pagePtr = make_shared<MyDB_Page>(this, tablePtr->getStorageLoc(), pageBufferPosition, pageId, false, false, i);
        idToPage[pageId] = pagePtr;
        // readFile from disk
        pagePtr->readFile();
    }
    else {
        pagePtr = idToPage.find(pageId)->second;
        // if buffered before
        if (pagePtr->getBuffer() == nullptr) {
            pageBufferPosition = nextAvailablePosition();
            pagePtr->setBuffer(pageBufferPosition);
        }
    }
    lruManager->update(pageId, pagePtr);
    MyDB_PageHandle pageHandle = make_shared<MyDB_PageHandleBase>(pagePtr);
	return pageHandle;
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
    string pageId;
    long pageNum;
    if (availableAnonyId.empty()) {
        pageNum = (long) anonyTotalCount;
        pageId = "_" + to_string(anonyTotalCount);
        anonyTotalCount++;
    } else {
        pageNum = (long) availableAnonyId[0];
        pageId = "_" + to_string(availableAnonyId[0]);
    }

    pagePtr pagePtr;
    char * pageBufferPosition;
    if (idToPage.find(pageId) == idToPage.end()) {
        pageBufferPosition = nextAvailablePosition();
        // pin->false anony->true
        pagePtr = make_shared<MyDB_Page>(this, tempFile, pageBufferPosition, pageId, false, true, pageNum);
        idToPage[pageId] = pagePtr;
        // readFile from disk
        pagePtr->readFile();
    }
    else {
        pagePtr = idToPage.find(pageId)->second;
        // if buffered before
        if (pagePtr->getBuffer() == nullptr) {
            pageBufferPosition = nextAvailablePosition();
            pagePtr->setBuffer(pageBufferPosition);
        }
    }
    lruManager->update(pageId, pagePtr);
//    updateLRUCache(pageId, pagePtr);
    MyDB_PageHandle pageHandle = make_shared<MyDB_PageHandleBase>(pagePtr);
    return pageHandle;

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
    unpinMe->unpinPage();
}

MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile) {
    this->pageSize = pageSize;
    this->numPages = numPages;
    this->tempFile = std::move(tempFile);

    bufferPool = (char *) malloc((this -> numPages * this -> pageSize) * sizeof(char));

    if (!bufferPool) {
        perror("Failed to allocate memory.");
        abort();
    }

    for (int i = 0; i < numPages; i++) {
        this -> availableBufferLoc.push(bufferPool + i * pageSize);
    }

    this -> anonyTotalCount = 0;
    lruManager = make_shared<MyDB_LRUManager>(numPages);

}

MyDB_BufferManager :: ~MyDB_BufferManager () {
    free(bufferPool);
}


char *MyDB_BufferManager::nextAvailablePosition() {
    char * nextPosition;
    if (!availableBufferLoc.empty()) {
         nextPosition = availableBufferLoc.front();
         availableBufferLoc.pop();
    }
    else {
        pagePtr nextEvictPage = lruManager->nextAvailablePage();
        nextPosition = nextEvictPage->getBuffer();
        nextEvictPage->setBuffer(nullptr);
        nextEvictPage->writeFile();
    }
    return nextPosition;
}

//pagePtr MyDB_BufferManager::updateLRUCache(pagePtr) {
//    return pagePtr();
//}

void MyDB_BufferManager::updateAvailableBufferLoc() {

}

void MyDB_BufferManager::safeExit() {

}

size_t MyDB_BufferManager::getPageSize() {
    return this -> pageSize;
}

#endif


