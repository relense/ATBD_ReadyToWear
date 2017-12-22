#include <stdio.h>
#include <stdlib.h>
#include "ficheiros.h"
#include "stackEstatico.h"

Ficheiro criaFicheiro(void){

    Ficheiro ficheiro;

    if((ficheiro = (Ficheiro) malloc (sizeof (struct ficheiro))) == NULL)
        return NULL;

    ficheiro->ano = 0;
    ficheiro->mes = 0;
    ficheiro->dia = 0;
    ficheiro->stackClientes = stackCreateEstatico();

    return ficheiro;
}
