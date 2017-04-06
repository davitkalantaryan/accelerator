#include "stdafx.h"
#include "cbend.h"

using namespace DAVIT_CLASSES;



CBend::CBend( const double& a_lfL, const double& a_H, const int& a_nKind )
	:	LinearBase(a_nKind, a_lfL),
		m_lfH(a_H)
{
	if( m_nKind == BEND )
	{
		ObtainMatrixTrans();
		ObtainMatrixTwiss();
	}
}



ElementBase* CBend::Clone()const
{
	return new CBend(*this);
}



void CBend::EQUATING( ElementBase* pSource )
{
	CBend* pBend = (CBend*)pSource;

	m_lfL	= pBend->m_lfL;
	m_lfH	= pBend->m_lfH;
}



void CBend::ReadFromFile1( FILE* a_File, void*, void* )
{
	ElementBase::ReadFromFile1( a_File, NULL, NULL );
	fread( &m_lfH, sizeof(m_lfH), 1, a_File );
}



void CBend::WriteToFile1( FILE* a_File )const
{
	ElementBase::WriteToFile1( a_File );
	fwrite( &m_lfH, sizeof(m_lfH), 1, a_File );	
}



#if 0

void CBend::WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const
{
	CAccElements::WriteOptiM( a_File, a_lfReserve );

	// bH 	L[cm]=$Ldip        	B[kG]=$Bdip    	G[kG/cm]=0        	Tilt[deg]=0

	fprintf( a_File, "\tB[kG]=%lfG[kG/cm]=0\tTilt[deg]=0", m_lfH * CGlobals::GetBro() );
}

void CBend::LoadFromString( const char*const& a_pcBuff, int a_nRead )
{

	CAccElements::LoadFromString( a_pcBuff, a_nRead );

	int nOffSet1, nOffSet2;

	int nLen = CGlobals::FindString( a_pcBuff, a_nRead, "B[", "]", nOffSet1 );

	/// B[kG]=$Bdip
	if( nLen > 0 )
	{/// if1

		nLen = CGlobals::FindString( a_pcBuff + nOffSet1, a_nRead - nOffSet1, "=", nOffSet2 );

		if( nLen > 2 && a_pcBuff[ nOffSet1 ] == 'k' && a_pcBuff[ nOffSet1 ] == 'G' )
		{
			if( nLen > 0 )
			{
				/// Piti Grvi
				m_lfH = 100. * atof( a_pcBuff + nOffSet1 + nOffSet2 ) / CGlobals::GetBro();
				/// End Piti Grvi
			}
			else
			{
				/// Error Report
			}
		}
		/// B[T]=$Bdip
		else if( nLen > 1 && a_pcBuff[ nOffSet1 ] == 'T'  )
		{
			if( nLen > 0 )
			{
				/// Piti Grvi
				m_lfH = atof( a_pcBuff + nOffSet1 + nOffSet2 ) / CGlobals::GetBro();
				/// End Piti Grvi
			}
			else
			{
				/// Error Report
			}
		}
		/// B[1/m]=$Bdip
		else if(nLen > 1                        && a_pcBuff[ nOffSet1     ] == '1' &&
				a_pcBuff[ nOffSet1 + 1 ] == '/' && a_pcBuff[ nOffSet1 + 2 ] == 'm' )
		{
			if( nLen > 0 )
			{
				/// Piti Grvi
				m_lfH = atof( a_pcBuff + nOffSet1 + nOffSet2 );
				/// End Piti Grvi
			}
			else
			{
				/// Error Report
			}
		}

	}/// End if1
	else 
	{/// else For if1
		/// Error Report
	}/// End else For if1

}

#endif



double CBend::DfiX(const double& beta0, const double& alfa0, const double& gama0,
				   double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
				   const double& lfS )const
{

	double s = ( lfS < 0. ) ? m_lfL : lfS;

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFiQF( s, beta0, alfa0, m_lfH ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	
	GetTwissAllX( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFiQF( s, beta0, alfa0, m_lfH ) ;

}



double CBend::DfiY(const double& beta0, const double& alfa0, const double& gama0,
				   double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
				   const double& lfS )const
{
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllY( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
}



SMatrix CBend::GetMatrixTrans(	const double& a_lfS )const
{
	return CFuncs::ObtainMatrixTransBend( a_lfS, m_lfH );
}
