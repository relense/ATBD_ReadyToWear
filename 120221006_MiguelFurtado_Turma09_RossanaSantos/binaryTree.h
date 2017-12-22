#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "element.h"

typedef struct abpnode *PtBSTnode;

struct abpnode
{
    PtBSTnode ptLeft;
    PtBSTnode ptRight;
    TElem *ptElem;
};

PtBSTnode BSTnodeCreate (TElem pelem);                  /* criar um nó da árvore */
unsigned int BSTSize (PtBSTnode proot);                 /* saber o tamanho da àrvore */
unsigned int BSTHeight (PtBSTnode proot);               /* saber a altura da àrvore */

PtBSTnode BSTSearchRec (PtBSTnode proot, TElem pelem) ; /* pesquisa recursiva */
PtBSTnode BSTMinRec (PtBSTnode proot);                  /* pesquisa de minimo recursiva */
PtBSTnode BSTMaxRec (PtBSTnode proot);                  /* pesquisa de máximo recursiva */

void BSTInsertRec (PtBSTnode *proot, TElem pelem);      /* inserção recursiva */
void BSTDeleteRecTotal (PtBSTnode *proot, TElem *pelem);/* remoção recursiva Total*/
PtBSTnode FindMin (PtBSTnode proot);                    /* encontrar o minimo */
void BSTDestroy (PtBSTnode *proot);                     /* destruir a àrvore */
void nodeRemove (PtBSTnode *proot);
void BSTDeleteRec (PtBSTnode *proot, TElem *pelem);	    /* remoção recursiva  sem apagar elemento da memória*/

void BSTPreOrderRec (PtBSTnode proot);                  /* travessia em pré-ordem recursiva */
void BSTInOrderRec (PtBSTnode proot);                   /* travessia em ordem recursiva */
void BSTPostOrderRec (PtBSTnode proot);                 /* travessia em pós-ordem recursiva */

void BSTByLevel (PtBSTnode proot);          /* mostrar em largura  - Precisa de confirmação, não tenho a certeza se imprime*/
void BSTDisplay (PtBSTnode proot, unsigned int plevel); /* mostrar em profrundidade */

void writeElem(PtBSTnode node);


#endif // BINARYTREE_H_INCLUDED
