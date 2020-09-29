#ifndef _CJB_QUEUE_
#define _CJB_QUEUE_

typedef struct queue { 
    
    int iAllocated;
    int iElementSize;
    int iIndex; // next free index
    void *pList;
}queue;

queue* queue_newQueue( int iNumElements, int iElementSize );
void   queue_freeQueue( queue *pQueue );
queue* queue_copyQueue( queue *pQueue );
bool   queue_empty( queue *pQueue );
bool   queue_push( queue *pQueue, void *pValue );
void*  queue_pop( queue *pQueue );
void*  queue_get ( queue *pQueue, int iIndex );
bool   queue_set( queue *pQueue, int iIndex, void *pValue );
queue* queue_subset( queue *pQueue, int iStart, int iEnd );
bool   queue_append( queue *pDestQueue, queue *pSrcQueue );

// Doubles the allocated memory for the queue. Called by queue_push()
int    queue_expand( queue *pQueue ); 

#endif // _CJB_QUEUE_
