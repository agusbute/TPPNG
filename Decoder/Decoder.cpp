// Decoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool image_encoder(const char* filename)
{
	bool error;
	const unsigned char * encoded_image;
	FILE* imagen;
	imagen = fopen(filename, "r"); //si no es con la terminación le agrego + ".txt"

// tomo los primeros cuatro bytes para obtener el tamaño de la imagen
	char c = fgetc(imagen);
	unsigned int size = c * 1000;
	c = fgetc(imagen);
	size += c * 100;
	c = fgetc(imagen);
	size += c * 10;
	c = fgetc(imagen);
	size += c; // tamaño total de pixeles

	encoded_image = new char[(unsigned int)size];	//reservo la memoria

	c = fgetc(imagen); 
	if (c != 'N')	//toda la imagen es del mismo color ¿caso base?
	{
		for (int i = 0; i < (size); i++)	//por pixel
		{
			encoded_image[i] = fgetc(imagen);	//red
			encoded_image[i+1] = fgetc(imagen);	//green
			encoded_image[i+2] = fgetc(imagen);	//blue
			encoded_image[i+4] = 0xFF;	//alpha
		}
	}
	else
	{
		myTypeToPNG(); //como es un nodo, voy a tener hojas // entra a la recursiva
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
	
	delete[] encoded_image;
	return error;
}

void myTypeToPNG(const unsigned char* encoded_image, FILE* imagen, int size)
{
	char c = fgetc(imagen);
	if (c != 'N')	//toda la imagen es del mismo color
	{
		if (c != 'L')
		{
			for (int i = 0; i < size; i++)	//por pixel
			{
				encoded_image[i] = fgetc(imagen);	//red
				encoded_image[i + 1] = fgetc(imagen);	//green
				encoded_image[i + 2] = fgetc(imagen);	//blue
				encoded_image[i + 4] = 0xFF;	//alpha
			}
		}
		else
		{

		}
	}
	else
	{
		myTypeToPNG(); //como es un nodo, voy a tener hojas // entra a la recursiva
	}
	if (fgetc(image) == 'N') 	//es un nodo
	{
		size /= 4;
		if (fgetc(image) == 'L')
		{

		}
		
	}
	
	
	fclose(imagen);
}