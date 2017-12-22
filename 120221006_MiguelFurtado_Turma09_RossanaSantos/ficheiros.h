#ifndef FICHEIROS_H_INCLUDED
#define FICHEIROS_H_INCLUDED
#include "stackEstatico.h"

struct ficheiro
{
    int dia;
    int mes;
    int ano;
    PtStackE stackClientes;
};

typedef struct ficheiro *Ficheiro;

/*Método para criar um ficheiro*/
Ficheiro criaFicheiro(void);

#endif // FICHEIROS_H_INCLUDED
