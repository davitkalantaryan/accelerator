#include "stdafx.h"
#include "cquad.h"


using namespace DAVIT_CLASSES;



// Class Quadrupol
CQuad::CQuad( const double& a_lfL, const double& a_g, const int& a_nKind )
	:	LinearBase(a_nKind, a_lfL), m_g(a_g), m_nMirrorIndex( _NO_MIRROR )
{
	m_lfK = sqrt( fabs( m_g ) );

	if( a_nKind == QUAD )
	{
		ObtainMatrixTrans();
		ObtainMatrixTwiss();
	}
}



ElementBase* CQuad::Clone()const
{
	return new CQuad(*this);
}



void CQuad::EQUATING( ElementBase* pSource )
{
	CQuad* pQuad = (CQuad*)pSource;

	m_lfL			= pQuad->m_lfL;
	m_g				= pQuad->m_g;
	m_lfK			= pQuad->m_lfK;
	m_nMirrorIndex	= pQuad->m_nMirrorIndex;
}



double CQuad::DfiX(const double& beta0, const double& alfa0, const double& gama0,
				   double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
				   const double& lfS )const
{
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	double lfRet, gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;

	if( m_g < 0. )
		lfRet = CFuncs::ObtainDFiQD( s, beta0, alfa0, m_lfK ) ;
	else if( m_g > 0. )
		lfRet = CFuncs::ObtainDFiQF( s, beta0, alfa0, m_lfK ) ;
	else
		lfRet = CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
	

	GetTwissAllX( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return lfRet ;
}



double CQuad::DfiY(const double& beta0, const double& alfa0, const double& gama0,
				   double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
				   const double& lfS )const
{
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	double lfRet, gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;

	if( m_g < 0. )
		lfRet = CFuncs::ObtainDFiQF( s, beta0, alfa0, m_lfK ) ;
	else if( m_g > 0. )
		lfRet = CFuncs::ObtainDFiQD( s, beta0, alfa0, m_lfK ) ;
	else
		lfRet = CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
	

	GetTwissAllY( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return lfRet ;
}



void CQuad::SetMirrorIndex( const int& a_nMirrorIndex )
{
	m_nMirrorIndex = a_nMirrorIndex;
}



const int& CQuad::GetMirrorIndex()const
{
	return m_nMirrorIndex;
}



void CQuad::WriteToFile1( FILE* a_File )const
{
	ElementBase::WriteToFile1( a_File );
	fwrite( &m_g, sizeof(m_g), 1, a_File );	
}



void CQuad::ReadFromFile1( FILE* a_File, void*, void* )
{
	ElementBase::ReadFromFile1( a_File, NULL, NULL );
	fread( &m_g, sizeof(m_g), 1, a_File );
	m_lfK = sqrt( fabs( m_g ) );
}



SMatrix CQuad::GetMatrixTrans(	const double& a_lfS )const
{
	//CFuncs::ObtainMatrixTransQuad( m_lfL, m_g, m_lfK );
	return CFuncs::ObtainMatrixTransQuad( a_lfS, m_g, m_lfK );
}



#if 0
void CQuad::WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const
{
	CAccElements::WriteOptiM( a_File, a_lfReserve );

	/// ret = Bro * value / 10000;
	fprintf( a_File, "\tG[kG/cm]=%lf\tTilt[deg]=0", CGlobals::GetBro() * m_g / 10000. );
}



void CQuad::LoadFromString( const char*const& a_pcBuff, int a_nRead )
{
	CAccElements::LoadFromString( a_pcBuff, a_nRead );

	int nOffSet1, nOffSet2;

	int nLen = CGlobals::FindString( a_pcBuff, a_nRead, "G[", "]", nOffSet1 );

	if( nLen > 0 )
	{/// if1

		/// G[kG/cm]
		if( nLen > 4 &&                        a_pcBuff[ nOffSet1     ] == 'k' && 
			a_pcBuff[ nOffSet1 + 1 ] == 'G' && a_pcBuff[ nOffSet1 + 2 ] == '/' && 
			a_pcBuff[ nOffSet1 + 3 ] == 'c' && a_pcBuff[ nOffSet1 + 4 ] == 'm'		)
		{/// if2
			nLen = CGlobals::FindString( a_pcBuff + nOffSet1, a_nRead - nOffSet1, "=", nOffSet2 );
			
			if( nLen > 0 )
			{
				/// ret = 10000 * value / Bro;
				m_g = 10000. * atof( a_pcBuff + nOffSet1 + nOffSet2 ) / CGlobals::GetBro();
			}
			else
			{
				/// Error Report
			}
		}/// End if2
		/// G[T/m]
		else if(nLen > 2 &&                        a_pcBuff[ nOffSet1     ] == 'T' && 
				a_pcBuff[ nOffSet1 + 1 ] == '/' && a_pcBuff[ nOffSet1 + 2 ] == 'm'		)
		{/// else if2

			nLen = CGlobals::FindString( a_pcBuff + nOffSet1, a_nRead - nOffSet1, "=", nOffSet2 );
			
			if( nLen > 0 )
			{
				/// Piti Grvi
				/// m_g = atof( a_pcBuff + nOffSet1 + nOffSet2 ) / KOEF_g;
				/// End Piti Grvi
			}
			else
			{
				/// Error Report
			}

		}/// End else if2
		/// G[cm^-2]
		else if(nLen > 4 &&                        a_pcBuff[ nOffSet1     ] == 'c' && 
				a_pcBuff[ nOffSet1 + 1 ] == 'm' && a_pcBuff[ nOffSet1 + 2 ] == '^' &&
				a_pcBuff[ nOffSet1 + 3 ] == '-' && a_pcBuff[ nOffSet1 + 4 ] == '2'		)
		{/// else if2

			nLen = CGlobals::FindString( a_pcBuff + nOffSet1, a_nRead - nOffSet1, "=", nOffSet2 );
			
			if( nLen > 0 )
			{
				m_g = 10000. * atof( a_pcBuff + nOffSet1 + nOffSet2 );
			}
			else
			{
				/// Error Report
			}

		}/// End else if2
		/// G[m^-2]
		else if(nLen > 3 &&                        a_pcBuff[ nOffSet1     ] == 'm' && 
				a_pcBuff[ nOffSet1 + 1 ] == '^' && a_pcBuff[ nOffSet1 + 2 ] == '-' &&
				a_pcBuff[ nOffSet1 + 3 ] == '2'		)
		{/// else if2

			nLen = CGlobals::FindString( a_pcBuff + nOffSet1, a_nRead - nOffSet1, "=", nOffSet2 );
			
			if( nLen > 0 )
			{
				m_g = atof( a_pcBuff + nOffSet1 + nOffSet2 );
			}
			else
			{
				/// Error Report
			}

		}/// End else if2

	}/// End if1
	else /// else for if1
	{
		/// Error Report
	}/// End else for if1

}

#endif
