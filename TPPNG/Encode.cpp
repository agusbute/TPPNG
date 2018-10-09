#include "stdafx.h"
#include "Image.h"
#include "Encode.h"
#include "lodepng.h"

bool Encode(Image& image, unsigned int threshold)		
{
	unsigned  w = image.width, h = image.height;		//recupero datos de la imagen
	ofstream output;													
	string Infile(image.getFilename().c_str());
	for (int i = 3; i != 0; i--)
	{
		Infile.pop_back();								//borro el ".png"
	}
	string outfile = Infile + "BOI";					//pongo terminacion nueva
	output.open(outfile,ios::binary);								//creo el archivo
	if (h >= 4096)										//4096 = 0x1000
	{
		output << std::hex << h;

	}
	else if (h < 4096 && h >= 256)
	{
		output << 0x00 << std::hex << h;
	}
	else if (h<256 && h>= 16)
	{
		output << 0x00 << 0x00 << std::hex << h;
	}
	else
	{
		output << 0x00 << 0x00 << 0x00 << std::hex << h;
	}
	EncodeRec(image.img, output, (unsigned char) ceil(threshold * 2.55), w, w);
	return true;
}

void EncodeRec(unsigned char * img, ofstream& output, int threshold, unsigned length, unsigned BMPsize)
{
	unsigned char Rprom, Gprom, Bprom;
		
	if ((puntaje(img, length, BMPsize)) > threshold && length != 1)
	{
		output << 'N';
		int corrimiento1 = (length / 2) * 4;					
		int corrimiento2 = (length / 2) * 4 * length;
		//int corrimiento3 = (length / 2) * 4 + (length / 2);
		int corrimiento3 = corrimiento1 + corrimiento2;
		EncodeRec(img, output, threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento1, output, threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento2, output , threshold, length / 2, BMPsize);
		EncodeRec(img + corrimiento3, output, threshold, length / 2, BMPsize);
	}
	else
	{
		output << 'H';
		Rprom = promedioR(img, length,  BMPsize);
		Gprom = promedioG(img, length,  BMPsize);
		Bprom = promedioB(img, length,  BMPsize);
		output << Rprom << Gprom << Bprom << (unsigned char) 0xFF;
		
	}
}

unsigned char promedioR(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned int Rvalue = 0;
	unsigned int cont = 0;
	
	for (unsigned int fila = 0; fila < length; fila++)		//recorro todo el quadtree calculando el promedio
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			
			Rvalue += abs(img[4 * (fila*BMPsize + columna)]);
			cont++;
		}

	}

	return ((unsigned char)floor(Rvalue / (cont)));

}

unsigned char promedioG(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned int Gvalue = 0,cont = 0 ;
	
	for (unsigned int fila = 0; fila < length; fila++)					//recorro todo el quadtree calculando el promedio
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			Gvalue += abs(img[4 * (fila*BMPsize + columna) + 1]);
			cont++;
		}

	}

	return ((unsigned char)floor(Gvalue / (cont)));

}

unsigned char promedioB(unsigned char * img, unsigned length, unsigned BMPsize)
{
	unsigned int Bvalue = 0,cont = 0 ;
	for (unsigned int fila = 0; fila < length; fila++)						//recorro todo el quadtree calculando el promedio
	{
		for (unsigned int columna = 0; columna < length; columna++)
		{
			Bvalue += abs(img[4 * (fila*BMPsize + columna) + 2]);
			cont++;
		}

	}

	return ((unsigned char)floor(Bvalue / (cont)));

}


int puntaje(unsigned char * image, unsigned length, unsigned BMPsize)		//esto establece un puntaje en genral comparando los minimos y maximos
{
	unsigned char Rmax, Gmax, Bmax, Rmin, Gmin, Bmin;
	Rmax = Gmax = Bmax = 0;
	Rmin = Gmin = Bmin = 0xFF;
	unsigned int fila = 0, columna = 0 ;
	

	for (; fila < length; fila++)					//recorro todo el raw pixel data
	{
		for (columna = 0; columna < length; columna++)		//paso a buscar los valores minimos y maximos de los colores
		{

			if (image[4 * (fila * BMPsize + columna) + 1] < Gmin)		//busco el minimo verde
			{
				Gmin = image[4 * (fila * BMPsize + columna) + 1];
			}
			if (image[4 * (BMPsize * fila + columna)] < Rmin)
			{
				Rmin = image[4 * (fila * BMPsize + columna)];			////busco el minimo rojo
			}
			if (image[4 * (fila * BMPsize + columna) + 2] < Bmin)
			{
				Bmin = image[4 * (fila * BMPsize + columna) + 2];		////busco el minimo azul
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
	}
	return (Rmax - Rmin + Gmax - Gmin + Bmax - Bmin);
}

