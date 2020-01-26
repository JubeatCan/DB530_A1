#ifndef PAGE_C
#define PAGE_C

#include "MyDB_Page.h"

MyDB_Page::~MyDB_Page() {

}

string MyDB_Page::getPageId() {
    return this -> pageId;
}

void MyDB_Page::increaseCounter() {
    this -> handlerCounter += 1;
}

void MyDB_Page::decreaseCounter() {
    this -> handlerCounter -= 1;
}

bool MyDB_Page::getDirty() {
    return this -> dirty;
}

void MyDB_Page::setDirty(bool newDirty) {
    this -> dirty = newDirty;
}

bool MyDB_Page::getAnonymous() {
    return this -> anonymous;
}

int MyDB_Page::getNumberOfHandler() {
    return this -> handlerCounter;
}

bool MyDB_Page::getPinStatus() {
    return this -> pin;
}

void MyDB_Page::setPinStatus(bool newPin) {
    this -> pin = newPin;
}

char *MyDB_Page::getBuffer() {
    return bufferLoc;
}

void MyDB_Page::setBuffer(char * newBuffer) {
    bufferLoc = newBuffer;
}

string MyDB_Page::getFileLoc() {
    return this -> fileLoc;
}

MyDB_Page::MyDB_Page(const MyDB_BufferManager* bm, string& fileLoc, char * ramLoc, string& pageId, bool pin, bool anonymous) {
    this->fileLoc = fileLoc;
    this->bufferLoc = ramLoc;
    this->pageId = pageId;
    this->pin = pin;
    this->anonymous = anonymous;

    handlerCounter = 0;
    dirty = false;
}

void MyDB_Page::readFile() {
//    int fileDescriptor;
//    if (!anonymous) {
//        fileDescriptor = open();
//    }
}

#endif