#ifndef PAGE_C
#define PAGE_C

#include "MyDB_Page.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

using namespace std;

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

MyDB_Page::MyDB_Page(MyDB_BufferManager* bm, string& fileLoc, char * ramLoc, string& pageId, bool pin, bool anonymous, long pageNum) {
    this->fileLoc = fileLoc;
    this->bufferLoc = ramLoc;
    this->pageId = pageId;
    this->pin = pin;
    this->anonymous = anonymous;
    this->bufferManager = bm;
    this->pageNum = pageNum;
    handlerCounter = 0;
    dirty = false;
}

void MyDB_Page::readFile() {
    int fileDescriptor;
    fileDescriptor = open(fileLoc.c_str(), O_FSYNC | O_RDONLY, 0666);
    if (fileDescriptor < 0) {
        perror("Cannot open file to read");
    }

    lseek(fileDescriptor, this -> bufferManager->getPageSize() * this -> pageNum, SEEK_SET);
    read(fileDescriptor, bufferLoc, this->bufferManager->getPageSize());

    close(fileDescriptor);
}

void MyDB_Page::writeFile() {
    int fileDescriptor;
    fileDescriptor = open(fileLoc.c_str(), O_FSYNC | O_CREAT | O_RDWR, 0666);
    if (fileDescriptor < 0) {
        perror("Cannot open file to write");
    }

    lseek(fileDescriptor, this -> bufferManager->getPageSize() * this -> pageNum, SEEK_SET);
    write(fileDescriptor, bufferLoc, this->bufferManager->getPageSize());

    close(fileDescriptor);
}

void MyDB_Page::evictMe() {
    bufferManager->getLruManager()->evictSinglePage(pageId);
    writeFile();
    if (bufferLoc != nullptr)
        bufferManager->addAvailableBufferLoc(bufferLoc);
    if (anonymous) {
        bufferManager->addAvailableAnonyId(pageNum);
    }
}

void MyDB_Page::bufferMe() {
    this->bufferLoc = bufferManager->nextAvailablePosition();
    this->readFile();
    this->bufferManager->getLruManager()->update(pageId, shared_from_this());
    this->setDirty(false);
}

void MyDB_Page::lruUpdateToHead() {
    this->bufferManager->getLruManager()->update(pageId, shared_from_this());
}


#endif