#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <memory>
#include "MyDB_Table.h"
#include "MyDB_BufferManager.h"

using namespace std;

class MyDB_Page;
class MyDB_BufferManager;
typedef shared_ptr<MyDB_Page> pagePtr;

class MyDB_Page : public enable_shared_from_this<MyDB_Page>{
public:

    MyDB_Page(MyDB_BufferManager *, string &, char *, string &, bool, bool, long);
    ~MyDB_Page();
    string getPageId();

    void increaseCounter();

    void decreaseCounter();

    int getNumberOfHandler();

    bool getPinStatus();

    void setPinStatus(bool);

    bool getDirty();

    void setDirty(bool);

    bool getAnonymous();

    char * getBuffer();

    void setBuffer(char *);

    string getFileLoc();

    void readFile();

    // write back to disk
    void writeFile();

    void evictMe();

    void bufferMe();

    void lruUpdateToHead();



private:

    string pageId;
    int handlerCounter;
    bool dirty;
    bool pin;
    bool anonymous;
    //bool buffered;
    // bufferLocation, if not null-ptr -> already in buffer
    char * bufferLoc;
    string fileLoc;
    MyDB_BufferManager *bufferManager;
    long pageNum;

};

#endif //PAGE_H
