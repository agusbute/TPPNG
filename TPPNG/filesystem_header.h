#include "stdafx.h"
#ifndef __FILESYSTEM_HEADER
#define __FILESYSTEM_HEADER

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem;

#define ARCHIVO_EXISTE "hola.txt"
#define ARCHIVO_INEXISTE "no_hola.txt"

int see_dirContent(const char* dir,const char **);



#endif