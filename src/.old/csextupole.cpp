#include "stdafx.h"
#include "csextupole.h"


using namespace DAVIT_CLASSES;



CSextupole::CSextupole( const double& a_lfL, const double& a_lfSG )
:	CDrift( a_lfL, SEXTUPOLE ), m_lfSG( a_lfSG )
{
}



ElementBase* CSextupole::Clone()const
{
	return new CSextupole(*this);
}



void CSextupole::SetFields( const int& Which, const double& Param, const int& /*Index*/ )
{
	switch(Which)
	{
	case CSextupole::GRADIENT:
		m_lfSG = Param;
		break;

	default:
		CDrift::SetFields(Which,Param,END_OF_LATTICE);
		break;
	}
}



const double& CSextupole::GetFields( const int& Which, const int& /*Index*/ )const
{
	switch(Which)
	{
	case CSextupole::GRADIENT:
		return m_lfSG;
		break;

	default:
		break;
	}


	return CDrift::GetFields(Which,END_OF_LATTICE);
}



void CSextupole::WriteToFile1( FILE* a_File )const
{
	ElementBase::WriteToFile1( a_File );
	fwrite( &m_lfSG, sizeof(m_lfSG), 1, a_File );	
}



void CSextupole::ReadFromFile1( FILE* a_File, void*, void* )
{
	ElementBase::ReadFromFile1( a_File, NULL, NULL );
	fread( &m_lfSG, sizeof(m_lfSG), 1, a_File );
}
