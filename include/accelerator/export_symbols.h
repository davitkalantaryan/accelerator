//
// file:			export_symbols.h
// path:			include/accelerator/export_symbols.h
// created on:		2023 Apr 03
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef ACCELERATOR_INCLUDE_ACCELERATOR_EXPORT_SYMBOLS_H
#define ACCELERATOR_INCLUDE_ACCELERATOR_EXPORT_SYMBOLS_H

#include <cinternal/internal_header.h>


#ifndef ACCELERATOR_EXPORT
#if defined(ACCELERATOR_COMPILING_SHARED_LIB)
#define ACCELERATOR_EXPORT CPPUTILS_DLL_PUBLIC
#elif defined(ACCELERATOR_USING_STATIC_LIB_OR_OBJECTS)
#define ACCELERATOR_EXPORT
#elif defined(ACCELERATOR_LOAD_FROM_DLL)
#define ACCELERATOR_EXPORT CPPUTILS_IMPORT_FROM_DLL
#else
#define ACCELERATOR_EXPORT CPPUTILS_DLL_PRIVATE
#endif
#endif


#endif  // #ifndef ACCELERATOR_INCLUDE_ACCELERATOR_EXPORT_SYMBOLS_H
