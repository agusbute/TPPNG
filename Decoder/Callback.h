#pragma once
#include "stdafx.h"
#include "parselib.h"

#define ARGUMENTOS 2

typedef struct
{
	char *path;
}argument_t;


int parseCallback(char *key, char *value, void *UserData);
void how_to_use(void);

int strcasecmp(const char * str1, const char * str2);
void str_to_lwr(char * str);