cmake_minimum_required(VERSION 3.15)
project(A1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -g -O0")

include_directories(Main/BufferMgr/headers)
include_directories(Main/Catalog/headers)
include_directories(Main/Qunit)
include_directories(Main/Qunit/headers)

add_executable(A1
        Main/BufferMgr/headers/MyDB_BufferManager.h
        Main/BufferMgr/headers/MyDB_PageHandle.h
        Main/BufferMgr/source/MyDB_BufferManager.cc
        Main/BufferTest/source/BufferQUnit.cc
        Main/BufferMgr/source/MyDB_PageHandle.cc
        Main/Catalog/headers/MyDB_Table.h
        Main/Catalog/source/MyDB_Table.cc
        Main/Qunit/headers/QUnit.h Main/BufferMgr/headers/MyDB_Page.h Main/BufferMgr/source/MyDB_Page.cc Main/BufferMgr/headers/MyDB_LRUManager.h Main/BufferMgr/source/MyDB_LRUManager.cc)
