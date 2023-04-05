#ifndef __elementcreator_h__
#define __elementcreator_h__


#include <stdio.h>
#include "elementbase.h"

#ifdef ACCELERATOR_IGNORE_OLD_INCLUDES
#error "Old include is used"
#endif

namespace DAVIT_CLASSES
{

class ElementCreator
{
public:
	static int					LoadKindFromFile(FILE* flFile);
	
	static class ElementBase*	CreateNewDevice(int Kind);

	static void					StringToFile( FILE* a_File, const char* a_String );

	static void					StringFromFile( FILE* a_File, char** a_pString );
};


};


#endif/* #ifndef __elementcreator_h__ */
