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

    MyDB_Page(string &, char *, string, bool, bool);
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

    void setAnonymous(bool);

    char * getBuffer();

    void setBuffer(char *);

    string getFileLoc();

    void readFile();


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

};

#endif //PAGE_H
