#include "StdAfx.h"
#include <accelerator/comandsfl.h>
#include <stdlib.h>
#include <ctype.h>


namespace DAVIT_CLASSES {


CComands::~CComands()
{
	free( m_pcComand );
}


CComands::CComands()
{
	m_pcComand = (char*)malloc((1 + MAX_CHARACT_COMAND_LINE) * sizeof(char));
	m_pcComand[0] = 'G'; m_pcComand[1] = 'O'; m_pcComand[2] = 0;
}


void CComands::StartMatch()
{
}

const char* CComands::ReadComand( const char*const& a_pcComandStr )const
{

	const char* pcComandStrTemp = a_pcComandStr;
	char* pcComandTemp = m_pcComand;

	while( *pcComandStrTemp == ' ' )
		++pcComandStrTemp;

	while( *pcComandStrTemp != ' '  && *pcComandStrTemp != 0 )
		*(pcComandTemp++) = toupper( *(pcComandStrTemp++) ) ;

	*pcComandTemp = 0;

	return pcComandStrTemp;

}

void CComands::GetPath(const char*& a_pcArgs, char*const& a_pcFileName )const
{

	while( *a_pcArgs++ == ' ' );
	--a_pcArgs;


	char* pcFileNameTemp = a_pcFileName;

	while( *a_pcArgs != ' '  && *a_pcArgs != 0 )
		*pcFileNameTemp++ = *a_pcArgs++ ;

	*pcFileNameTemp = 0;

}

void CComands::Get_N_Args( const char*& a_pcArgs, unsigned long& a_ulnN )const
{
	while( *a_pcArgs++ == ' ' );
	--a_pcArgs;

	a_ulnN = (unsigned long)atol( a_pcArgs );
}

void CComands::Get_Derivative( const char*& a_pcArgs, double& a_lfDerivativeMax )const
{
	while( *a_pcArgs++ == ' ' );
	--a_pcArgs;

	a_lfDerivativeMax = atof( a_pcArgs );
}

void CComands::Get_N_Threads( const char*& a_pcArgs, size_t& a_unThreads )const
{
	while( *a_pcArgs++ == ' ' );
	--a_pcArgs;

	a_unThreads = (size_t)atoi( a_pcArgs );
}


}  //  namespace DAVIT_CLASSES {
