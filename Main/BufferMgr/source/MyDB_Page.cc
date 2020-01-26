#ifndef PAGE_C
#define PAGE_C

#include "MyDB_Page.h"

MyDB_Page::MyDB_Page() {

}

MyDB_Page::~MyDB_Page() {

}

string MyDB_Page::getPageId() {
    return std::string();
}

void MyDB_Page::increaseCounter() {

}

void MyDB_Page::decreaseCounter() {

}

bool MyDB_Page::getDirty() {
    return false;
}

void MyDB_Page::setDirty(bool) {

}

bool MyDB_Page::getAnonymous() {
    return false;
}

int MyDB_Page::getNumberOfHandler() {
    return 0;
}

bool MyDB_Page::getPinStatus() {

}

bool MyDB_Page::getBuffered() {
    return false;
}

void MyDB_Page::setBuffered() {

}

void MyDB_Page::setPinStatus(bool) {

}

void MyDB_Page::setAnonymous(bool) {

}

char *MyDB_Page::getBuffer() {
    return nullptr;
}

void MyDB_Page::setBuffer(char *) {

}

string MyDB_Page::getFileLoc() {
    return std::string();
}

#endif