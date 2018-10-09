#include "stdafx.h"
#include "filesystem_header.h"


int see_dirContent(const char* dir, const char ** filenameArray)
{
	path p(dir);
	int counter=0;
	int i = 0;
	if (exists(p))
	{
		if (is_regular_file(p))
		{
			filenameArray[0] = (char *)dir;
			counter = 1;
		}
		else if (is_directory(p))     // is p a directory?
		{
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{
				filenameArray[i] = (char *)(itr->path().filename());
				counter++;
				i++;
			}
		}
	}
	else
	{
		cout << p << " No existe\n";
	}
	return counter;
}
/*
La funcion copy mueve todos los elementos comprendidos entre directory_iterator() (que devuelve un ITERATOR END)
y directory_iterator(p) que devuelve la carpeta raiz a  ostream_iterator, que se ocupa de transformar a la clase
especificada en <> (TEMPLATE) en algo legible para cout.
*/