#ifndef FILAESTATICA_H_INCLUDED
#define FILAESTATICA_H_INCLUDED
#define MAX 100
#include "elementNo.h"

struct queue	/* definição da fila */
{
    TElemN *table;	/* área de armazenamento */
    unsigned int begin,end;	/* cabeça e cauda da fila */
    unsigned int nElem;
    unsigned int N;
};

typedef struct queue *PtQueue;

PtQueue queueCreate(int max);
int queueDestroy(PtQueue *pQueue);
int queueEnqueue(PtQueue pQueue, TElemN pelem);
int queueDequeue(PtQueue pQueue, TElemN *pelem);
int queuePeek(PtQueue pQueue, TElemN *pelem);
int queueIsEmpty(PtQueue pQueue);
int queueIsFull(PtQueue pQueue);
int queueSize(PtQueue pQueue, unsigned int *pNElem);

#endif // FILAESTATICA_H_INCLUDED
