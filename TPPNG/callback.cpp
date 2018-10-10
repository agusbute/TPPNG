#include "stdafx.h"
#include "parselib.h"
#include "callback.h"

//**************************************  parseCallback  ****************************************************************	

int parseCallback(char *key, char *value, void *UserData)
{
	argument_t *pUserData = (argument_t*) UserData; //Puntero a la estructura
	int result = 0; //Variable para detectar error

	//Evaluo la clave
	if(key!=NULL)
	{
		if((strcasecmp(key,"path")) == 0)
		{
			pUserData->path = value;	//le asigna su valor
			result = 1;
		}
		
		else if((strcasecmp(key,"threshold")) == 0)
		{
			if (atoi(value) <= 100 && atoi(value) >= 0)
			{
				pUserData->threshold = atoi(value);
				result = 1;
			}
			else
			{
				result = 0;
			}
		}	

    }
	else if (key == NULL) // si es parámetro
	{
		pUserData->threshold = atoi(value);
		result = 1;
	}	
	return result;
}


void how_to_use(void) 
{
	printf("Se deben ingresar los valores para las siguientes opciones: \n");
	printf("-path ... \n-threshold ...(con un valor entre 0 y 100). Tambien puede ingresar el threshold como parametro (como argumento sin clave) \n");
    printf("Estas pueden estar en cualquier orden. De no completar un minimo de 4 argumentos, el programa indicara un error de parametros.\n");
}

int strcasecmp(const char * str1, const char * str2)
{
	char auxStr1[100];
	char auxStr2[100];
	strcpy_s(auxStr1, 100, str1);
	str_to_lwr(auxStr1);
	strcpy_s(auxStr2, 100, str2);
	str_to_lwr(auxStr2);

	return strcmp(auxStr1, auxStr2);
}

void str_to_lwr(char * str)
{
	int i = 0;
	while (*(str + i) != '\0')
	{
		if (isupper(*(str + i)))
		{
			*(str + i) = tolower(*(str + i));
		}
		i++;
	}
}
