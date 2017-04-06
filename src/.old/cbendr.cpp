#include "stdafx.h"
#include "cbendr.h"


using namespace DAVIT_CLASSES;



CBendR::CBendR( const double& a_lfL, const double& a_H )
	:	CBend( a_lfL, a_H, BENDR )
{
	ObtainMatrixTrans();
	ObtainMatrixTwiss();
}



ElementBase* CBendR::Clone()const
{
	return new CBendR(*this);
}



double CBendR::DfiX(const double& beta0, const double& alfa0, const double& gama0,
					double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
					const double& lfS )const
{
	
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFiBendRx( s, beta0, alfa0, m_lfH, m_lfL ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllX( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFiBendRx( s, beta0, alfa0, m_lfH, m_lfL ) ;

}



double CBendR::DfiY(const double& beta0, const double& alfa0, const double& gama0,
					double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
					const double& lfS )const
{
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFiBendRy( s, beta0, alfa0, m_lfH, m_lfL, aPAR ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllY( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFiBendRy( s, beta0, alfa0, m_lfH, m_lfL, aPAR ) ;
}



SMatrix CBendR::GetMatrixTrans(	const double& a_lfS )const
{
	return CFuncs::ObtainMatrixTransBendR( a_lfS, m_lfH, m_lfL );
}
