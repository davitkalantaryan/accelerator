#include "stdafx.h"
#include "elementbase.h"

#include <malloc.h>
#include "elementcreator.h"

using namespace DAVIT_CLASSES;



void ElementBase::FamNameFromFile1( FILE* a_fpFile, char* a_pcFamName )
{
	char* aFamName = NULL;
	ElementCreator::StringFromFile( a_fpFile, &aFamName );
	strncpy( a_pcFamName, aFamName,FAM_NAME_SIZE );
	free( aFamName );
}



void ElementBase::ReadFromFile1( FILE* a_File, void*, void* )
{

	//fread( &m_nKind, sizeof(m_nKind), 1, a_File );

	//char* aFamName = NULL;
	//ElementCreator::StringFromFile( a_File, &aFamName );
	//strncpy( m_FamName, aFamName,FAM_NAME_SIZE );
	//free( aFamName );

	fread( &m_lfL, sizeof(m_lfL), 1, a_File );

	fread( &m_ucFlags2, sizeof(m_ucFlags2), 1, a_File );
}



void ElementBase::WriteToFile1( FILE* a_File )const
{

	fwrite( &m_nKind, sizeof(m_nKind), 1, a_File );

	ElementCreator::StringToFile( a_File, m_FamName );

	fwrite( &m_lfL, sizeof(m_lfL), 1, a_File );

	fwrite( &m_ucFlags2, sizeof(m_ucFlags2), 1, a_File );
	
}



void ElementBase::WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const
{
}



void ElementBase::LoadFromOptimString( const char*const& a_pcBuff, int a_nRead )
{
}



/// Get members for matchings
double ElementBase::GetTwissParam2(const int& whichParam,
								   const STwiss& aTwiss0, STwiss*const& pTwisF, 
								   const int& nI1, const int& /*nI2*/ )const
{
	double lfRet;

	this->GetTwissParam(lfRet, nI1, whichParam,aTwiss0, pTwisF);

	return lfRet;
}



void ElementBase::ObtainAll()
{
	this->ObtainMatrixTrans();
	this->ObtainMatrixTwiss();
}



void ElementBase::SetFlagHard(unsigned char a_unFlag)
{
	m_ucFlags2 = a_unFlag;
}



void ElementBase::SetFlag(int a_nBit, int a_nValue)
{
	ElementBase::SetFlagStat( a_nBit, a_nValue, &m_ucFlags2 );
}



void ElementBase::SetFlagStat(int a_nBit, int a_nValue, unsigned char* a_pucFlag)
{
	unsigned char unValue(a_nValue ? 1 : 0);
	unValue <<= a_nBit;

	unsigned char unMask( ~(1<<a_nBit) );

	*a_pucFlag &= unMask;
	*a_pucFlag |= unValue;
}



int ElementBase::GetFlag(int a_nBit)
{
	return ElementBase::GetFlagStat( a_nBit, m_ucFlags2 );
}



int ElementBase::GetFlagStat(int a_nBit,unsigned char a_ucFlag)
{
	return (a_ucFlag & (1<<a_nBit)) ? 1 : 0;
}
