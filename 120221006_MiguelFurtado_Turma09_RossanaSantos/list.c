#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define OK 0            /* operação realizada com sucesso */
#define NO_LIST -1      /* lista inexistente */
#define NO_MEM -2       /* memória esgotada */
#define NULL_PTR -3     /* ponteiro nulo */
#define LIST_EMPTY -4   /* lista vazia */
#define OUT_OF_RANK -5  /* fora do range da lista */


void destroyNode(PtNodeL ptNode)
{
    free(ptNode->ptElem);
    free(ptNode);
}

PtList listCreate ()
{
    PtList ptList;
    if ((ptList = (PtList) malloc (sizeof (struct list))) == NULL)
        return NULL; /* alocar memória */

    ptList->head = NULL; /* inicializar a cabeça */
    ptList->tail = NULL; /* inicializar a cauda */
    ptList->nElems = 0;

    return ptList; /* devolver a referência da lista acabada de criar */
}

int listDestroy (PtList *ptList)
{
    PtList tmptList = *ptList;
    PtNodeL tmpNode;

    if (tmptList == NULL) return NO_LIST;

    while (tmptList->head != NULL)
    {
        tmpNode = tmptList->head;
        tmptList->head = tmptList->head->ptNext;
        free (tmpNode->ptElem);
        free (tmpNode);
    }

    free (tmptList);
    *ptList = NULL;
    return OK;
}


PtNodeL ptNodeAtRank(PtList ptList, unsigned int rank)
{
    int i;

    if(rank < ptList->nElems/2)
    {
        PtNodeL ptNode = ptList->head;
        for (i = 0; i <= rank; i++)
            ptNode = ptNode->ptNext;

        return ptNode;
    }
    else
    {
        PtNodeL ptNode = ptList->tail;
        for (i = ptList->nElems - 1; i > rank; i--)
            ptNode = ptNode->ptPrev;

        return ptNode;
    }
}

int listAdd (PtList ptList, unsigned int rank, TElem elem)
{
    PtNodeL tmpNode;

    if (ptList == NULL) return NO_LIST;

    if(rank < 0 || rank > ptList->nElems)
        return OUT_OF_RANK;

    if ((tmpNode = malloc (sizeof (struct ptNode))) == NULL)
        return NO_MEM;

    if ((tmpNode->ptElem = malloc (sizeof (TElem)))== NULL)
    {
        free (tmpNode);
        return NO_MEM;
    }

    *tmpNode->ptElem = elem;
    tmpNode->ptPrev = NULL;
    tmpNode->ptNext = NULL;
    ptList->nElems++;

    if(ptList->nElems == 1)
    {
        ptList->head = tmpNode;
        ptList->tail = tmpNode;
    }

    if(rank == 0)
    {
        tmpNode->ptNext = ptList->head;
        tmpNode->ptNext->ptPrev = tmpNode;
        ptList->head = tmpNode;

        return OK;
    }

    if(rank == ptList->nElems - 1)
    {
        tmpNode->ptPrev = ptList->tail;
        tmpNode->ptPrev->ptNext = tmpNode;
        ptList->tail = tmpNode;

        return OK;
    }

    PtNodeL ptNextNode = ptNodeAtRank(ptList,rank);
    PtNodeL ptNodePrev = ptNextNode->ptPrev;

    tmpNode->ptPrev = ptNodePrev;
    tmpNode->ptNext = ptNextNode;

    ptNextNode->ptPrev = tmpNode;
    ptNodePrev->ptNext = tmpNode;

    return OK;
}

int listSet (PtList ptList, unsigned int rank, TElem elemIn, TElem* pElemOut)
{
    if (ptList == NULL) return NO_LIST;

    if(listSize(ptList) == 0) return LIST_EMPTY;

    if(rank < 0|| rank >= ptList->nElems) return OUT_OF_RANK;

    if(pElemOut == NULL) return NULL_PTR;

    PtNodeL ptNode =ptNodeAtRank(ptList, rank);
    *pElemOut = *ptNode->ptElem;

    *ptNode->ptElem = elemIn;

    return OK;
}

int listRemove (PtList ptList, unsigned int rank, TElem* pElem)
{
    if (ptList == NULL) return NO_LIST;

    if(rank < 0 || rank >= ptList->nElems) return OUT_OF_RANK;

    if(pElem == NULL) return NULL_PTR;

    PtNodeL ptNode = ptNodeAtRank(ptList,rank);

    *pElem = *ptNode->ptElem;
    ptList->nElems--;

    if(ptList->nElems == 0)
    {
        ptList->head = NULL;
        ptList->tail = NULL;
        destroyNode(ptNode);
    }

    PtNodeL ptNodePrev = ptNode->ptPrev;
    PtNodeL ptNodeNext = ptNode->ptNext;

    if(rank == ptList->nElems)
    {
        ptList->tail = ptNodePrev;
        ptNodePrev->ptNext = ptNodeNext;
    }

    else if(rank == 0)
    {
        ptNodeNext->ptPrev = ptNodePrev;
        ptList->head = ptNodeNext;
    }
    else
    {
        ptNodePrev->ptNext = ptNodeNext;
        ptNodeNext->ptPrev = ptNodePrev;
    }
    destroyNode(ptNode);
    return OK;
}

int listGet (PtList ptList, unsigned int rank, TElem* pElem)
{
    if (ptList == NULL) return NO_LIST;

    if(listSize(ptList) == 0) return LIST_EMPTY;

    if(rank < 0|| rank >= ptList->nElems) return OUT_OF_RANK;

    if(pElem == NULL) return NULL_PTR;

    PtNodeL ptNode = ptNodeAtRank(ptList, rank);
    *pElem = *ptNode->ptElem;

    return OK;
}
int listSize (PtList ptList)
{
    if(ptList == NULL) return NO_LIST;

    return ptList->nElems;
}

