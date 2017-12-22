#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "element.h"

typedef struct ptNode *PtNodeL;

struct ptNode /* definição de um nó da lista */
{
    TElem *ptElem; /* ponteiro para o elemento */
    PtNodeL ptPrev; /* ponteiro para o nó seguinte */
    PtNodeL ptNext; /* ponteiro para o nó seguinte */
};

struct list
{
    PtNodeL head;
    PtNodeL tail;
    unsigned int nElems;
};

typedef struct list *PtList;

PtList listCreate ();                                                         /*Criar a lista*/
int listDestroy (PtList *ptList);                                             /*Destruir a lista*/
int listAdd (PtList ptList, unsigned int rank, TElem elem);                   /*Adicionar um element à lista*/
int listSet (PtList ptList, unsigned int rank, TElem elemIn, TElem* pElemOut);/*Retirar um elemento da lista e substituir por outro*/
int listRemove (PtList ptList, unsigned int rank, TElem* pElem);              /*Remover um elemento da lista*/
int listGet (PtList ptList, unsigned int rank, TElem* pElem);                 /*Obter um elemento da lista*/
int listSize (PtList ptList);                                                 /*Tamanho da lista*/


#endif // LIST_H_INCLUDED
