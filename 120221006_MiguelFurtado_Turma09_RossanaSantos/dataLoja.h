#ifndef DATALOJA_H_INCLUDED
#define DATALOJA_H_INCLUDED

struct dataLoja
{
    int ano;
    int mes;
    int dia;
};

typedef struct dataLoja *DataLoja;

DataLoja criaDataLoja(void);
#endif // DATALOJA_H_INCLUDED
