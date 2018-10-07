#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callback.h"

#define ARGUMENTOS 2

typedef struct
{
	char * path;
	int threshold;
}argument_t;


int parseCallback(char *key, char *value, void *UserData);
void how_to_use(void);