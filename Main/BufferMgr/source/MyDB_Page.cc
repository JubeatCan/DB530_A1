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

bool MyDB_Page::getBuffered() {
    return false;
}

void MyDB_Page::setBuffered() {

}

#endif