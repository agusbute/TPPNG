#pragma once
#include "stdafx.h"
#include "Image.h"
#include "lodepng.h"


Image::Image()
{

}

Image::Image(string filename)
{
	this->filename = filename;
	lodepng_decode24_file(&img,&width,&height,filename.c_str());
}

Image& Image::operator=(Image& img)
{
	this->filename = img.filename;
	this->selected = img.selected;
	this->height = img.height;
	this->width = img.width;
	this->img = img.img;
	return *this;
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