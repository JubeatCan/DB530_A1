#ifndef LRU_MGR_C
#define LRU_MGR_C

#include "MyDB_LRUManager.h"

MyDB_LRUManager::MyDB_LRUManager(int numPages) {
    this -> capacity = numPages;
}

MyDB_LRUManager::~MyDB_LRUManager() {

}

void MyDB_LRUManager::update(string pageId, pagePtr pagePointer) {
    if (pageId_cacheIt.find(pageId) == pageId_cacheIt.end()) {
        if (pageId_cacheIt.size() < capacity) {
            LRUCache.emplace_back(pageId, pagePointer);
            pageId_cacheIt.emplace(pageId, LRUCache.rbegin());
        } else if (pageId_cacheIt.size() == capacity) {
            pagePtr ptr = this->nextAvailablePage();
            LRUCache.erase(pageId_cacheIt[ptr->getPageId()]);
            pageId_cacheIt.erase(ptr->getPageId());

            LRUCache.emplace_back(pageId, pagePointer);
            pageId_cacheIt.emplace(pageId, LRUCache.rbegin());
        } else {
            perror("Something is wrong with the LRU.");
            abort();
        }
    } else {
        LRUCache.erase(pageId_cacheIt[pageId]);
        LRUCache.emplace_back(pageId, pagePointer);
        pageId_cacheIt.erase(pageId);
        pageId_cacheIt.emplace(pageId, LRUCache.rbegin());
    }
}

void MyDB_LRUManager::evictSinglePage(const string& pageId) {
    if (pageId_cacheIt.find(pageId) == pageId_cacheIt.end()) {
        perror("Cannot find the page to evict.");
    } else {
        LRUCache.erase(pageId_cacheIt[pageId]);
        pageId_cacheIt.erase(pageId);
    }
}

pagePtr MyDB_LRUManager::nextAvailablePage() {
    for (auto it = LRUCache.begin(); it != LRUCache.end(); next(it, 1)) {
        if (!it->second->getPinStatus()) {
            return it->second;
        }
    }
    perror("Buffer is all pinned.");
    return pagePtr();
}

#endif