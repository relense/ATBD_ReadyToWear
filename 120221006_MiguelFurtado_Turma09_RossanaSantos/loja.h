#ifndef LOJA_H_INCLUDED
#define LOJA_H_INCLUDED
#include "cliente.h"
#include "stackDinamico.h"
#include "list.h"
#include "dataLoja.h"
#include "binaryTree.h"

struct loja
{
    int nrClienteVistaramCompras, nrClientesSemCompras, nrClienteVisitaram;
    int nrClientes;
    char generoMaisVisitou[20];
    Cliente *clienteGastouMais;
    PtStackD stack;                                                         /* stack de ficheiros*/
    PtList lista;
    DataLoja dataLoja;
    PtBSTnode clienteNo;

};
typedef struct loja *Loja;

Loja criarLoja(void);                                                       /* Criar uma loja*/
#endif // LOJA_H_INCLUDED
