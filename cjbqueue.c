// Author: Christian Bargraser

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cjbqueue.h"

queue* queue_newQueue( iNumElements, iElementSize ) {

    queue *pQueue = (queue*)malloc(sizeof(queue));

    if( NULL == pQueue ) {
        fprintf(stderr, "Error: cjbqueue.h: queue_newQueue(): malloc() for queue *pQueue failed\n");
        exit(-1);
    }

    pQueue->iAllocated = iNumElements;
    pQueue->iElementSize = iElementSize;
    pQueue->pList = calloc( iNumElements, iElementSize );

    if( NULL == pQueue->pList ) {
        fprintf(stderr, "Error: cjbqueue.h: queue_newQueue(): malloc() for queue *pQueue->pList failed\n");
        exit(-1);
    }
    
    pQueue->iIndex = 0;

    return pQueue;
}

void queue_freeQueue( queue *pQueue ) {

    free( pQueue->pList );
    free( pQueue );
}

queue* queue_copyQueue( queue *pQueue ) {

    if( NULL == pQueue ) {
        return NULL;
    }

    queue *pCopy = queue_newQueue( pQueue->iAllocated, pQueue->iElementSize );
    memcpy( pCopy->pList, pQueue->pList, pQueue->iElementSize * pQueue->iAllocated );
    pCopy->iIndex = pQueue->iIndex;
    return pCopy;
}

bool queue_empty( queue *pQueue ) {

    if( NULL == pQueue ) {
        fprintf(stderr, "Warning: cjbqueue.h: queue_empty(): pQueue is NULL\n");
        return true;
    }

    if( NULL == pQueue->pList ) {
        fprintf(stderr, "Warning: cjbqueue.h: queue_empty(): pQueue->pList is NULL\n");
        return true;
    }

    if( 0 == pQueue->iIndex ) {
        return true;
    }

    return false;
}

bool queue_push( queue *pQueue, void *pValue ) {

    if( NULL == pQueue ) {
        return false;
    }

    // if the queue is full, allocate more memory
    if( pQueue->iIndex == pQueue->iAllocated ) {
        queue_expand( pQueue );
    }

    // insert the new value
    memcpy( ((char*)pQueue->pList) + (pQueue->iIndex * pQueue->iElementSize), pValue, pQueue->iElementSize);
    pQueue->iIndex++;
    
    return true;
}

void* queue_pop( queue *pQueue ) {

    if( NULL == pQueue || pQueue->iIndex <= 0 ) {
        return NULL;
    }

    // iIndex is the next free index
    pQueue->iIndex--;
    return ((char*)pQueue->pList) + (pQueue->iIndex * pQueue->iElementSize);
}

void* queue_get ( queue *pQueue, int iIndex ) {

    if( NULL == pQueue || NULL == pQueue->pList || iIndex >= pQueue->iIndex ) {
        return NULL;
    }

    return ((char*)pQueue->pList) + (iIndex * pQueue->iElementSize);
}

bool queue_set( queue *pQueue, int iIndex, void *pValue ) {

    if( NULL == pQueue || NULL == pQueue->pList || iIndex >= pQueue->iIndex ) {
        return false;
    }

    memcpy( ((char*)pQueue->pList) + (iIndex * pQueue->iElementSize), pValue, pQueue->iElementSize);
    return true;
}

queue* queue_subset( queue *pQueue, int iStart, int iEnd ) {

    if( NULL == pQueue ) {
        return NULL;
    }

    if( iStart > pQueue->iAllocated ) {

        fprintf(stderr, "Warning: cjbqueue.h: queue_subset(): iStart (%d) is greater than pQueue->iAllocated (%d)\n", iStart, pQueue->iAllocated );
        return NULL;
    }

    if( iEnd < iStart ) {
        
        fprintf(stderr, "Warning: cjbqueue.h: queue_subset(): iEnd (%d) is greater than iStart (%d)\n", iEnd, iStart );
        return NULL;
    }

    // adjust iEnd if necessary
    if( iEnd > pQueue->iAllocated ) {
        iEnd = pQueue->iAllocated;
    }

    // length of requested subset is 0
    if( iStart == iEnd ) {
        fprintf(stderr, "Warning: cjbqueue.h: queue_subset(): iStart (%d) == iEnd (%d)\n", iStart, iEnd );
        return NULL;
    }

    int iNewAllocate = iEnd-iStart;
    queue *pSubset = queue_newQueue( iNewAllocate, pQueue->iElementSize );
    pSubset->iAllocated = iNewAllocate;

    int iQueue = iStart;
    int iSub;

    for( iSub = 0 ; iSub < iNewAllocate ; ++iSub, ++iQueue ) {

        // pSubset->pList[iSub] = pQueue->pList[iQueue];
        memcpy( ((char*)pSubset->pList) + (iSub * pQueue->iElementSize), ((char*)pQueue->pList) + (iQueue * pQueue->iElementSize), pQueue->iElementSize);
    }
    pSubset->iIndex = iSub;

    return pSubset;
}

bool queue_append( queue *pDestQueue, queue *pSrcQueue ) {

    if( NULL == pDestQueue || NULL == pSrcQueue ) {
        return false;
    }

    // if the resulting queue would exceed the allocated memory
    int iNeeded = pDestQueue->iIndex + pSrcQueue->iIndex;
    while ( iNeeded > pDestQueue->iAllocated ) { // was < 
        queue_expand( pDestQueue );
    }

    memcpy( ((char*)pDestQueue->pList) + (pDestQueue->iIndex * pDestQueue->iElementSize), pSrcQueue->pList, pDestQueue->iElementSize * pSrcQueue->iIndex);
    pDestQueue->iIndex += pSrcQueue->iIndex;

    return true;
}

int queue_expand( queue *pQueue ) {
    
    if( NULL == pQueue ) {
        return -1;
    }

    if( 0 == pQueue->iAllocated ) {
        
        pQueue->pList = malloc( pQueue->iElementSize );
        pQueue->iAllocated = 1;
        return 1;
    }

    int iNewAllocated = pQueue->iAllocated * 2;
    void *pRealloc = realloc( pQueue->pList, iNewAllocated * pQueue->iElementSize );

    if( NULL == pRealloc ) {
        queue_freeQueue(pQueue);
        fprintf(stderr, "Error: cjbqueue.h: queue_expand: malloc failed\n"); 
        exit(-1);
    }

    pQueue->pList = pRealloc;
    pQueue->iAllocated = iNewAllocated; 
    return iNewAllocated; 
}
