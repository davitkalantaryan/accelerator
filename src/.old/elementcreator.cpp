#include "stdafx.h"
#include "elementcreator.h"

using namespace DAVIT_CLASSES;

#include "linearbase.h"
#include "cdrift.h"
#include "cquad.h"
#include "cbend.h"
#include "cbendr.h"
#include "elemsseq.h"
#include "clinear.h"
#include "csextupole.h"
#include "caperture.h"
#include "combinefuncmagnet.h"



int ElementCreator::LoadKindFromFile(FILE* a_fpFile)
{
	int nKind;
	fread( &nKind, sizeof(nKind), 1, a_fpFile );
	return nKind;
}


/*
enum _ELEM_KIND{INIT, LINEARBASE, DRIFT, QUAD, QF, QD, 
						BEND, BENDR, SEQUENCE, LINEAR, SEXTUPOLE, APERTURE, END };*/
class ElementBase* ElementCreator::CreateNewDevice(int a_nKind)
{
	ElementBase* pDevice = NULL;

	switch(a_nKind)
	{
	case ElementBase::LINEARBASE:
		pDevice = new LinearBase;
		break;
	case ElementBase::DRIFT:
		pDevice = new CDrift;
		break;
	case ElementBase::QUAD:
		pDevice = new CQuad;
		break;
	case ElementBase::QF:
		break;
	case ElementBase::QD:
		break;
	case ElementBase::BEND:
		pDevice = new CBend;
		break;
	case ElementBase::BENDR:
		pDevice = new CBendR;
		break;
	case ElementBase::SEQUENCE:
		pDevice = new ElemsSeq;
		break;
	case ElementBase::LINEAR:
		pDevice = new CLinear;
		break;
	case ElementBase::SEXTUPOLE:
		pDevice = new CSextupole;
		break;
	case ElementBase::APERTURE:
		pDevice = new CAperture;
		break;
	case ElementBase::COMBINEFUNCMAGNET:
		pDevice = new CombineFuncMagnet;
		break;
	default:
		break;
	}

	return pDevice;
}



void ElementCreator::StringToFile( FILE* a_File, const char* a_String )
{
	int nSize = a_String ? (int)strlen( a_String ) : 0 ;

	fwrite( &nSize, sizeof(nSize), 1, a_File );

	if( nSize )
	{
		fwrite( a_String, sizeof(char), (size_t)nSize, a_File );
	}
}



void ElementCreator::StringFromFile( FILE* a_File, char** a_pString )
{
	char*& aString = *a_pString;

	int nSize;

	fread( &nSize, sizeof(nSize), 1, a_File );

	if( nSize )
	{
		aString = (char*)realloc( aString, nSize + 1 );
		fread( aString, sizeof(char), (size_t)nSize, a_File );
		aString[nSize] = 0;
	}
}
