// Decoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool image_encoder(const char* filename)
{
	bool error;
	
	FILE* imagen;
	imagen = fopen(filename, "r"); //si no es con la terminación le agrego + ".blah"

// tomo los primeros cuatro bytes para obtener el tamaño de la imagen
	char c = fgetc(imagen);
	unsigned int size = c * 1000;
	c = fgetc(imagen);
	size += c * 100;
	c = fgetc(imagen);
	size += c * 10;
	c = fgetc(imagen);
	size += c; // tamaño total de pixeles
	char red, green, blue, alpha;
	c = fgetc(imagen); 
	if (c != 'N')	//toda la imagen es del mismo color
	{
		for (int i = 0; i < (size*4); i++)
		{
			red = c;
			green = fgetc(imagen);
			blue = fgetc(imagen);
		}
	}
	else
	{
		//entra a la recursiva
	}


	

	/************************************************************************************************************/
	if (lodepng_encode32_file(filename, image, w, h))	// a filename agregarle .png ?? // image es const unsigned char*
	{
		error = false;
	}
	else
	{
		error = true;
	}
	free(image);
	return error;
}

void myTypeToPNG(const unsigned char* image_return, /*const char* filename*/)
{

	if ( == 'L' || ) 	//si es leaf
	{
		for (i = 0; i < 9; i++, a++)	//
		{
			// cargo rgb
		}
	}
	else if (a == 'N')
	{
		decode();
	}
	
	fclose(imagen);
}