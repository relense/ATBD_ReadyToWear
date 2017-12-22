#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iterator.h"
#include "list.h"

PtListIterator listIteratorCreate(PtList pList)
{
    PtListIterator pListIt = malloc(sizeof (struct listIterator));

    pListIt->ptlist = pList;
    pListIt->ptNode = pList->head;

    return pListIt;
}

TElem* nextElem(PtListIterator pListIt)
{
    TElem *elem = pListIt->ptNode->ptElem;
    pListIt->ptNode = pListIt->ptNode->ptNext;

    return elem;
}

int hasNextElem(PtListIterator pListIt)
{
    return(pListIt->ptNode != pListIt->ptlist->tail->ptNext);
}

int destroyIterator(PtListIterator *pListIt)
{
    PtListIterator tmptList = *pListIt;
    PtNodeL tmpNode;

    if (tmptList == NULL) return 1;

    while (tmptList->ptlist->head->ptNext != NULL)
    {
        tmpNode = tmptList->ptlist->head;
        tmptList->ptlist->head = tmptList->ptlist->head->ptNext;
        free (tmpNode->ptElem);
        free (tmpNode);
    }

    free (tmptList);
    *pListIt = NULL;

    return 0;
}
