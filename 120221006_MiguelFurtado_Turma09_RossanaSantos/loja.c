#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackDinamico.h"
#include "loja.h"
#include "list.h"
#include "dataLoja.h"

Loja criarLoja(void)
{
    Loja loja;

    if((loja = (Loja) malloc(sizeof(struct loja))) == NULL)
        return NULL;

    loja->dataLoja = criaDataLoja();
    loja->stack = stackCreateDinamico();
    loja->lista = listCreate();
    loja->nrClientes = 0;
    loja->nrClientesSemCompras = 0;
    loja->nrClienteVisitaram = 0;
    loja->nrClienteVistaramCompras = 0;

    return loja;
}
