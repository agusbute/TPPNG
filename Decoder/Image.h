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

	Image();
	Image(string filename);
	bool isSelected();
	void toggleSelect();
	string getFilename();
	unsigned int width;

	Image& operator=(Image& img);
	Image& operator=(const char* name);
	Image& operator=(string& name);

private:
	string filename;
	bool selected;
};