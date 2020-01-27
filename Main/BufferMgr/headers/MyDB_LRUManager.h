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
class MyDB_Page;
typedef shared_ptr<MyDB_Page> pagePtr;
typedef shared_ptr<MyDB_LRUManager> LRUManager;

class MyDB_LRUManager {
public:

    MyDB_LRUManager(int numPages);

    ~MyDB_LRUManager();

    void update(string, pagePtr);

    void evictSinglePage(const string&);

    pagePtr nextAvailablePage();

    void writeBackDirty();

private:

    list<pair<string, pagePtr>> LRUCache;
    unordered_map<string, list<pair<string, pagePtr>> :: iterator> pageId_cacheIt;
    int capacity;

};

#endif
