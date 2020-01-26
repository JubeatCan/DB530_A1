#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <memory>
#include <MyDB_Table.h>

using namespace std;

class MyDB_Page;
typedef shared_ptr<MyDB_Page> pagePtr;

class MyDB_Page {
public:

    MyDB_Page();
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
    string pageId;
    int handlerCounter;
    bool dirty;
    bool pin;
    bool anonymous;
    bool buffered;
    // bufferLocation, if not null-ptr -> already in buffer
    char * bufferLoc;
    string fileLoc;

    bool getBuffered();

    void setBuffered();
};

#endif //PAGE_H
