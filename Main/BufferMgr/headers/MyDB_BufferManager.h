
#ifndef BUFFER_MGR_H
#define BUFFER_MGR_H

#include "MyDB_PageHandle.h"
#include "MyDB_Table.h"
#include "MyDB_Page.h"
#include "MyDB_LRUManager.h"
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
class MyDB_PageHandleBase;
class MyDB_LRUManager;
typedef shared_ptr <MyDB_PageHandleBase> MyDB_PageHandle;
typedef shared_ptr<MyDB_LRUManager> LRUManager;

class MyDB_BufferManager {

public:

	// THESE METHODS MUST APPEAR AND THE PROTOTYPES CANNOT CHANGE!

	// gets the i^th page in the table whichTable... note that if the page
	// is currently being used (that is, the page is current buffered) a handle 
	// to that already-buffered page should be returned
	MyDB_PageHandle getPage (MyDB_TablePtr whichTable, long i);

	// gets a temporary page that will no longer exist (1) after the buffer manager
	// has been destroyed, or (2) there are no more references to it anywhere in the
	// program.  Typically such a temporary page will be used as buffer memory.
	// since it is just a temp page, it is not associated with any particular 
	// table
	MyDB_PageHandle getPage ();

	// gets the i^th page in the table whichTable... the only difference 
	// between this method and getPage (whicTable, i) is that the page will be 
	// pinned in RAM; it cannot be written out to the file
	MyDB_PageHandle getPinnedPage (MyDB_TablePtr whichTable, long i);

	// gets a temporary page, like getPage (), except that this one is pinned
	MyDB_PageHandle getPinnedPage ();

	// un-pins the specified page
	void unpin (MyDB_PageHandle unpinMe);

	// find next available position
	char * nextAvailablePosition() ;

	// creates an LRU buffer manager... params are as follows:
	// 1) the size of each page is pageSize 
	// 2) the number of pages managed by the buffer manager is numPages;
	// 3) temporary pages are written to the file tempFile
	MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile);
	
	// when the buffer manager is destroyed, all of the dirty pages need to be
	// written back to disk, any necessary data needs to be written to the catalog,
	// and any temporary files need to be deleted
	~MyDB_BufferManager ();

	// FEEL FREE TO ADD ADDITIONAL PUBLIC METHODS
//	// allocate buffer to single page, poll() from buffer queue
//	char * bufferLocForSinglePage();

	// update LRU cache when you call get(), return the pagePtr should be evicted
    void updateLRUCache(string, pagePtr);

    // update the available buffer queue, if free -> push available loc to queue
    void updateAvailableBufferLoc();

    // Write dirty page back when buffer manager is destroyed.
    void safeExit();

    size_t getPageSize();

    LRUManager getLruManager();

    void addAvailableBufferLoc(char *);

    void addAvailableAnonyId(long);

private:

	// YOUR STUFF HERE

	// Initialize stuffs
	size_t pageSize;
	size_t numPages;
	string tempFile;

	//vector<char *> pageSpace;
	char * bufferPool;

	//unordered_map<char *, bool> isAvailable;
    //available bufferAddress, push all available buffer at the beginning
    queue<char *> availableBufferLoc;

    //map from pageId to page pointer
    unordered_map<string, pagePtr> idToPage;

    long anonyTotalCount;

    vector<long> availableAnonyId;

    LRUManager lruManager;


};

#endif


