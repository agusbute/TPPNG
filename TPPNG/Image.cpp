#pragma once
#include "stdafx.h"
#include "Image.h"
#include "lodepng.h"


Image::Image(string filename)
{
	this->filename = filename;
	lodepng_decode24_file(&img,&width,&height,filename.c_str());
}


bool Image::isSelected()
{
	return selected;
}

void Image::toggleSelect()
{
	selected = !selected;
}

string Image::getFilename()
{
	return filename;
}