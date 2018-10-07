#pragma once
#include "stdafx.h"
#include "Image.h"
#include "Encode.h"
#include "lodepng.h"

bool Encode(Image& image, unsigned int threshold)
{
	unsigned  w = image.width, h = image.height;		//recupero datos de la imagen
	char buffer[8];										//necesito un bufffer para el itoa
	ofstream output;													
	string Infile(image.getFilename().c_str());
	for (int i = 3; i != 0; i--)
	{
		Infile.pop_back();								//borro el .png
	}
	string outfile = Infile + "BOI";					//pongo terminacion nueva
	output.open(outfile);								//creo el archivo
	char * size = _itoa(w*h, buffer, 10);
	output << size;														
	EncodeRec(image.img, output, threshold, w, w);

}

void EncodeRec(unsigned char * img, ofstream& output, unsigned int threshold, unsigned length, unsigned BMPsize)
{
	unsigned char Rprom, Gprom, Bprom;
	int puntos = puntaje(img, length, BMPsize);
	
	if (puntos > threshold)
	{
		output << 'N';
		int corrimiento1 = (length / 2) * 4;					
		int corrimiento2 = (length / 2) * 4 * length;
		int corrimiento3 = (length / 2) * 4 + (length / 2);

		EncodeRec(img, output, threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento1, output, threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento2, output , threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento3, output, threshold, length / 2, BMPsize);
	}
	else
	{
		output << 'H';
		Rprom = promedioR(unsigned char * img, unsigned length, unsigned BMPsize);
		Gprom = promedioG(unsigned char * img, unsigned length, unsigned BMPsize);
		Bprom = promedioB(unsigned char * img, unsigned length, unsigned BMPsize);

		
	}
}

unsigned char promedioR(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned char Rvalue = 0;
	for (unsigned int fila = 0; fila < length; fila++)
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			Rvalue += img[4 * (fila*BMPsize + columna)]
		}

	}

	return ((unsigned char)Rvalue / pow(2,BMPsize))

}

unsigned char promedioG(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned char Gvalue = 0;
	for (unsigned int fila = 0; fila < length; fila++)
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			Gvalue += img[4 * (fila*BMPsize + columna)+1]
		}

	}

	return ((unsigned char)Gvalue / pow(2, BMPsize))

}

unsigned char promedioB(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned char Bvalue = 0;
	for (unsigned int fila = 0; fila < length; fila++)
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			Bvalue += img[4 * (fila*BMPsize + columna) + 2]
		}

	}

	return ((unsigned char)Bvalue / pow(2, BMPsize))

}















int puntaje(unsigned char * image, unsigned length, unsigned BMPsize)		//esto establece un puntaje en genral comparando los minimos y maximos
{
	unsigned char Rmax, Gmax, Bmax, Rmin, Gmin, Bmin;
	Rmax = Gmax = Bmax = 255;
	Rmin = Gmin = Bmin = 0;

	for (int fila = 0; fila < length; fila++)
	{
		for (int columna = 0; columna < length; columna++)		//paso a buscar los valores minimos y maximos de los colores
		{
			
			if (image[4 * (fila * BMPsize + columna) + 1] < Gmin)		//analizo los minimos
			{
				Gmin = image[4 * (fila * BMPsize + columna) + 1];		//analizo el verde
			}
			if (image[4 * (BMPsize * fila + columna)] < Rmin)
			{
				Rmin = image[4 * (fila * BMPsize + columna)];			//analizo el rojo
			}
			if (image[4 * (fila * BMPsize + columna) + 2] < Bmin)
			{
				Bmin = image[4 * (fila * BMPsize + columna) + 2];		//analizo el azul
			}
						
			if (image[4 * (fila * BMPsize + columna) + 1] > Gmax)		//idem pero con maximos
			{
				Gmax = image[4 * (fila * BMPsize + columna) + 1];
			}
			if (image[4 * (fila * BMPsize + columna)] > Rmax)			
			{
				Rmax = image[4 * (fila * BMPsize + columna)];
			}
			if (image[4 * (fila * BMPsize + columna) + 2] > Bmax)
			{	
				Bmax = image[4 * (fila * BMPsize + columna) + 2];
			}
	}
		return (Rmax - Rmin + Gmax - Gmin + Bmax - Bmin);
}

