#pragma once
#include "stdafx.h"

using namespace std;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGB;

class Image
{
public:
	
	Image(string filename); 
	bool isSelected();
	void toggleSelect();
	string getFilename();
	unsigned int width;

private:
	string filename;
	bool selected;
};