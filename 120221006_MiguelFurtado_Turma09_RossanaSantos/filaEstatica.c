#include <stdlib.h>
#include <stdio.h>
#include "filaEstatica.h"

#define OK          0
#define NO_QUEUE    1
#define NO_MEM      2
#define NULL_PTR    3
#define QUEUE_EMPTY 4
#define QUEUE_FULL  5

PtQueue queueCreate (int max)
{
    PtQueue queue;
    if(max < 1)
        max = MAX;

    if ((queue = (PtQueue) malloc (sizeof (struct queue))) == NULL)
        return NULL;	/* alocar memória para a fila */

    queue->table = calloc(max,sizeof(TElemN));
    queue->N = max;
    queue->begin = 0;	/* inicializar a cabeça da fila */
    queue->end = 0;	/* inicializar a cauda da fila */
    queue->nElem = 0;

    return queue;	/* devolver a referência da fila acabada de criar */
}

int queueDestroy (PtQueue *pqueue)
{
    PtQueue Tmpqueue = *pqueue;

    if (Tmpqueue == NULL) return NO_QUEUE;
    free (Tmpqueue);	/* libertar toda a memória ocupada pela fila */
    *pqueue = NULL;	/* colocar a referência da fila a NULL */
    return OK;
}

int queueEnqueue (PtQueue pqueue, TElemN elem)
{
    if (pqueue == NULL)
    {
        return NO_QUEUE;
    }

    if(queueIsFull(pqueue))
        return QUEUE_FULL;

    pqueue ->table[pqueue->end] = elem;
    pqueue -> end = (pqueue -> end+1) % pqueue->N;
    pqueue ->nElem++;
    return OK;

}

int queueDequeue (PtQueue pqueue, TElemN *pElem)
{
    if (pqueue == NULL)
    {
        return NO_QUEUE;
    }

    if(queueIsEmpty(pqueue))
        return QUEUE_EMPTY;
    if (pElem == NULL)
        return NULL_PTR;

    *pElem = pqueue ->table[pqueue->begin];
    pqueue -> begin = (pqueue -> begin+1) % pqueue->N;
    pqueue ->nElem--;
    return OK;
}

int queuePeek (PtQueue pqueue, TElemN *pElem)
{
    if (pqueue == NULL)
        return NO_QUEUE;

    if(queueIsEmpty(pqueue))
        return QUEUE_EMPTY;

    if (pElem==NULL)
        return NULL_PTR;

    *pElem = pqueue ->table[pqueue->begin];
    return OK;
}

int queueIsEmpty (PtQueue pqueue)
{
    if (pqueue == NULL)
        return NO_QUEUE;
    if (pqueue->nElem == 0)
        return 1;
    return 0;
}

int queueIsFull (PtQueue pqueue)
{
    if (pqueue == NULL)
        return NO_QUEUE;
    if (pqueue->nElem == pqueue->N)
        return 1;
    return 0;
}



int queueSize (PtQueue pqueue, unsigned int *pNElem)
{
    if (pqueue == NULL)
        return NO_QUEUE;

    if (pNElem == NULL)
        return NULL_PTR;

    *pNElem = pqueue->nElem;

    return 0;
}
