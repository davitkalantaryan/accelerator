//
// file:            elementcreator.hpp
// path:			include/accelerator/elementcreator.hpp
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <accelerator/export_symbols.h>
#include <stdio.h>

namespace DAVIT_CLASSES{

class ACCELERATOR_EXPORT ElementCreator
{
public:
	static int					LoadKindFromFile(FILE* flFile);	
	static class ElementBase*	CreateNewDevice(int Kind);
	static void					StringToFile( FILE* a_File, const char* a_String );
	static void					StringFromFile( FILE* a_File, char** a_pString );
};


}  //  namespace DAVIT_CLASSES{
