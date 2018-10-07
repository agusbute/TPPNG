#include "stdafx.h"
#include "Decoder.h"

bool image_encoder(string filename)
{
	string filename_BOI = filename + ".BOI";	//mi archivo
	string filename_png = filename + ".png";
	bool error;
	unsigned char * encoded_image;
	FILE* imagen;
	imagen = fopen(filename_BOI.c_str(), "r");	//si no es con la terminación le agrego + ".txt"

// tomo los primeros cuatro bytes para obtener el tamaño de la imagen
	char c = fgetc(imagen);
	unsigned int size = c * 1000;
	c = fgetc(imagen);
	size += c * 100;
	c = fgetc(imagen);
	size += c * 10;
	c = fgetc(imagen);
	size += c; // tamaño total de pixeles
	int width = (int)sqrt(size);	//ancho y altura es lo mismo
	unsigned int cant_N = 0; // cantidad de nodos
	encoded_image = (unsigned char*)new char[size * 4];	//reservo la memoria
	unsigned int x1, x2, y1, y2;
	x1 = x2 = y1 = y2 = 0;
	myTypeToPNG(encoded_image, imagen, size, cant_N, x1, x2, y1, y2);

	if (lodepng_encode32_file(filename_png.c_str(), encoded_image, width, width))	// a filename agregarle .png ?? // image es const unsigned char*
	{
		error = false;
	}
	else
	{
		error = true;
	}
	
	delete[] encoded_image;
	fclose(imagen);
	return !error;
}

void myTypeToPNG(unsigned char* encoded_image, FILE* imagen, int size, unsigned int cant_N, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2)
{
	char c = fgetc(imagen);
	if (c = 'N')	//si es un nodo
	{
		cant_N++;
		unsigned int desplazado = size / pow(2,cant_N);
		myTypeToPNG(encoded_image, imagen, size, cant_N, x1, x2 + desplazado, y1, y2 + desplazado);	//para cada hijo
		myTypeToPNG(encoded_image, imagen, size, cant_N, x1 + desplazado, x2 + (desplazado*2), y1+ desplazado, y2 + desplazado);
		myTypeToPNG(encoded_image, imagen, size, cant_N, x1, x2 + desplazado, y1 + desplazado, y2 + (desplazado*2));
		myTypeToPNG(encoded_image, imagen, size, cant_N, x1 + desplazado, x2 + (desplazado * 2), y1 + desplazado, y2 + (desplazado * 2));
	}
	else if ( c = 'H')	//si es una hoja
	{
		char red, green, blue;
		char alpha = 0xFF;
		red = fgetc(imagen);
		green = fgetc(imagen);
		blue = fgetc(imagen);

		for (int j = y1; j < y2; j++)
		{
			for (int i = x1; i < x2; i += 4)
			{
				encoded_image[i] = red;	//red
				encoded_image[i + 1] = green;	//green
				encoded_image[i + 2] = blue;	//blue
				encoded_image[i + 3] = 0xFF;	//alpha
			}
		}
	}
}