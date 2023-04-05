//
// file:            string.h
// path:			include/accelerator/std/string.h
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef ACCELERATOR_INCLUDE_ACCELERATOR_STD_STRING_H
#define ACCELERATOR_INCLUDE_ACCELERATOR_STD_STRING_H


#include <string.h>


#ifdef _MSC_VER
#define strncpy(_dst,_src,_count)	strcpy_s(_dst,_count,_src)
#endif


#endif  //  #ifndef ACCELERATOR_INCLUDE_ACCELERATOR_STD_STRING_H
