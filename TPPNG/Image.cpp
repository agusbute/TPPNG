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
	int i = lodepng_decode32_file(&img,&width,&height,filename.c_str());
	selected = false;
}

Image& Image::operator=(const char* name)
{
	this->filename = name;
	int i = lodepng_decode32_file(&(this->img), &(this->width), &(this->height), (this->filename.c_str()));
	this->selected = false;
	return *this;
}

Image& Image::operator=(string& name)
{
	this->filename = name;
	lodepng_decode32_file(&(this->img), &(this->width), &(this->height), (this->filename.c_str()));
	this->selected = false;
	return *this;
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
	return this->selected;
}

void Image::toggleSelect()
{
	this->selected = !this->selected;
}

string Image::getFilename()
{
	return this->filename;
}