#ifndef GESTORFICHEIROS_H_INCLUDED
#define GESTORFICHEIROS_H_INCLUDED
#include "stackDinamico.h"
#include "stackEstatico.h"
#include "ficheiros.h"
#include "dataLoja.h"

int carregarFicheiro(FILE *file, Ficheiro ficheiro, DataLoja data);
void guardarFicheiro(PtStackD stack, Ficheiro ficheiro);
void imprimePilha(PtStackE stack);
PtStackE ordenaPilha(PtStackE stack);
int verificarSeExisteFicheiro(Ficheiro ficheiro, PtStackD stack);

#endif // GESTORFICHEIROS_H_INCLUDED
