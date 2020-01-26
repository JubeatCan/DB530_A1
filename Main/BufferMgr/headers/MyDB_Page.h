#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <memory>
#include <MyDB_Table.h>


using namespace std;

class MyDB_Page;
typedef shared_ptr<MyDB_Page> pagePtr;
typedef pair<MyDB_TablePtr, long> pageId;

class MyDB_Page {
public:

    MyDB_Page(char * bufferLoc, string fileLoc, long i);

    ~MyDB_Page();

    string getPageId();

    void increaseCounter();

    void decreaseCounter();

    int getNumberOfHandler();

    void getPinStatus();

    void setPinStatus(bool);

    bool getDirty();

    void setDirty(bool);

    bool getAnonymous();

    void setAnonymous(bool);

    char * getBuffer();

    void setBuffer(char *);

    string getFileLoc();


private:
    pageId pageId;
    int handlerCounter;
    bool dirty;
    bool pin;
    bool anonymous;

    // bufferLocation, if not null-ptr -> already in buffer
    char * bufferLoc;
    string fileLoc;

};

#endif //PAGE_H
