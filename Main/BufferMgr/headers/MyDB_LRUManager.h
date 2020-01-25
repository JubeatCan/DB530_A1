#ifndef LRU_MGR_H
#define LRU_MGR_H

#include "MyDB_Page.h"
#include "MyDB_Page.h"
#include <unordered_map>
#include <list>
#include <string>
#include <memory>

using namespace std;

class MyDB_LRUManager;
typedef shared_ptr<MyDB_LRUManager> LRUManager;

class MyDB_LRUManager {
public:

    MyDB_LRUManager();

    ~MyDB_LRUManager();

    void update(string PageID);

    void evictSinglePage();

private:

    list<pair<string, pagePtr>> LRUCache;
    unordered_map<string, list<pair<string, pagePtr>> :: iterator> pageId_cacheIt;

};

#endif
