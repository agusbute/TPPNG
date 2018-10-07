#pragma once
#include "stdafx.h"
#include "Encode.h"
#include "lodepng.h"


QuadTree::QuadTree()
{
	topLeft = Point(0, 0);
	botRight = Point(0, 0);
	n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
}

QuadTree::QuadTree(Point topLeft, Point botRight)
{
	n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
	this->topLeft = topLeft;
	this->botRight = botRight;
}

void QuadTree::insertNode(Node *node)
{
	if (node == NULL)
	{
		return;
	}
	if (!inSquare(node->pos))
	{
		return;
	}
	if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1)
	{
		if (n == NULL)
		{
			n = node;
		}
		return;
	}

	if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
	{
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
		{
			if (topLeftTree == NULL)
			{
				topLeftTree = new QuadTree(Point(topLeft.x, topLeft.y), Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2));
			}
			topLeftTree->insertNode(node);
		}

		else
		{
			if (botLeftTree == NULL)
			{
				botLeftTree = new QuadTree(Point(topLeft.x, (topLeft.y + botRight.y) / 2), Point((topLeft.x + botRight.x) / 2, botRight.y));
			}
			botLeftTree->insertNode(node);
		}
	}
	else
	{
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
		{
			if (topRightTree == NULL)
			{
				topRightTree = new QuadTree(Point((topLeft.x + botRight.x) / 2, topLeft.y), Point(botRight.x, (topLeft.y + botRight.y) / 2));
			}
			topRightTree->insertNode(node);
		}

		else
		{
			if (botRightTree == NULL)
			{
				botRightTree = new QuadTree(Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2), Point(botRight.x, botRight.y));
			}
			botRightTree->insertNode(node);
		}
	}
}

bool QuadTree::inSquare(Point p)
{
	return (p.x >= topLeft.x &&
		p.x <= botRight.x &&
		p.y >= topLeft.y &&
		p.y <= botRight.y);
}

bool Encode(const char * filename, unsigned int threshold)
{
	unsigned w, h;
	unsigned char * image;												//Arreglo donde se almacenara la informacion de la imagen
	char buffer[8];
	ofstream output;													//Archivo de salida (para el comprimido)

	lodepng_decode32_file(&image, &w, &h, filename);					//Decodifico imagen																																	
	char * hexaSize = _itoa(w*h, buffer, 10);							//Tamano de la imagen en hexadecimal
	output << hexaSize;												//Escribo el tamano en el archivo
	EncodeRec(image, output, threshold, w, w);

}

void EncodeRec(unsigned char * pointer, ofstream& outFile, unsigned int threshold, unsigned SubArbol, unsigned original)
{
	
}
