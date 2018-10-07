#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parselib.h"

#define ARGUMENTOS 8

typedef struct 
{
	char *path;
}argument_t;

	
int parseCallback(char *key, char *value, void *UserData);
void how_to_use(void);


int main (int argc, char *argv[])
{
	argument_t a = {NULL};
	argument_t *pUserData = &a;
	if(argc >= ARGUMENTOS)
	{
		if (parseCmdLine (argc, argv, parseCallback, pUserData) == 1)
		{
				printf("La materia %s es %s, la da el profesor %s que tiene %s años\n", pUserData->materia, pUserData->opinion, pUserData->nombre, pUserData->edad);
		}
		
		else 
		{
			printf("Error de parametros\n");
			how_to_use();
		}
	}
	else 
	{
		printf("Error de parametros\n");
		how_to_use();
	}
	return 0;
}



//**************************************  parseCallback  ****************************************************************	

int parseCallback(char *key, char *value, void *UserData)
{
	argument_t *pUserData = (argument_t*) UserData; //Puntero a la estructura
	int result = 0; //Variable para detectar error

	//Evaluo la clave
	if(key!=NULL)
	{
		if((strcasecmp(key,"materia")) == 0)
		{
			pUserData->materia = value;	//le asigna su valor
			result = 1;
		}
		
		else if((strcasecmp(key,"opinion")) == 0)
		{
			pUserData->opinion = value;
			result = 1;
			
		}	
		else if((strcasecmp(key,"nombre")) == 0)
		{
			pUserData->nombre = value;
			result = 1;
			
		}
        }
	else if (key == NULL) // si es parámetro
	{
		pUserData->edad = value;
		result = 1;
	}	
	return result;
}


void how_to_use(void) 
{
	printf("Se deben ingresar los valores para las siguientes opciones: \n");
	printf("-materia ...\n-opinion ... \n-nombre  ... \nedad (como argumento sin clave) \n");
    printf("Estas pueden estar en cualquier orden. De no completar un minimo de 7 argumentos, el programa indicara un error de parametros.\n");
}


