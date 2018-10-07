#pragma once
#include "stdafx.h"
#include <cmath>
#include "lodepng.h"

using namespace std;
bool image_encoder(string filename);
void myTypeToPNG(unsigned char * encoded_image, FILE* imagen, int size, unsigned int cant_N, unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2);
