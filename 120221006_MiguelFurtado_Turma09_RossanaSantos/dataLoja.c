#include <stdio.h>
#include <stdlib.h>
#include "dataLoja.h"

DataLoja criaDataLoja(void)
{
    DataLoja data;

    if((data = (DataLoja) malloc(sizeof (struct dataLoja))) == NULL)
        return NULL;

    data->dia = 0;
    data->mes = 0;
    data->ano = 0;

    return data;


}
