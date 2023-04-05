//
// file:            stdio.h
// path:			include/accelerator/std/stdio.h
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef ACCELERATOR_INCLUDE_ACCELERATOR_STD_STDIO_H
#define ACCELERATOR_INCLUDE_ACCELERATOR_STD_STDIO_H


#include <stdio.h>


#ifdef _MSC_VER
#define snprintf(_buf,_count,...)	_snprintf_s(_buf,_count,_count,__VA_ARGS__)
#endif


#endif  //  #ifndef ACCELERATOR_INCLUDE_ACCELERATOR_STD_STDIO_H
