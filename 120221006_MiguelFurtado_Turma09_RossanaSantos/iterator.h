#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED
#include "list.h"
#include "element.h"

typedef struct ptNode *PtNodeI;

struct ptNodeI /* definição de um nó da lista */
{
    TElem *ptElem; /* ponteiro para o elemento */
    PtNodeI ptPrev; /* ponteiro para o nó seguinte */
    PtNodeI ptNext; /* ponteiro para o nó seguinte */
};

struct listIterator
{
    PtNodeI ptNode;
    PtList ptlist;
};

typedef struct listIterator *PtListIterator;

PtListIterator listIteratorCreate(PtList pList);
TElem* nextElem(PtListIterator pListIt);
int hasNextElem(PtListIterator pListIt);


#endif // ITERATOR_H_INCLUDED
