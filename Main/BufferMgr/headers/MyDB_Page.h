#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <memory>

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
    bool getDirty();
    void setDirty(bool);
    bool getAnonymous();
    bool getBuffered();
    void setBuffered();

private:
    string pageId;
    int handlerCounter;
    bool dirty;
    bool pin;
    bool anonymous;
    bool buffered;
    string fileLoc;
};

#endif //PAGE_H
