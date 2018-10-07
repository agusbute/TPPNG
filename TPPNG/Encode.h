#pragma once
#include "stdafx.h"
#include <cmath> 
using namespace std;

bool Encode(Image& image, unsigned int treshold);
void EncodeRec(unsigned char * img, ofstream& output, int threshold, unsigned length, unsigned BMPsize);
int puntaje(unsigned char * image, unsigned length, unsigned BMPsize);
unsigned char promedioR(unsigned char * img, unsigned length, unsigned BMPsize);
unsigned char promedioG(unsigned char * img, unsigned length, unsigned BMPsize);
unsigned char promedioB(unsigned char * img, unsigned length, unsigned BMPsize);




