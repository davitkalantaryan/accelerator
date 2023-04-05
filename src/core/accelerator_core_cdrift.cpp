#include "stdafx.h"
#include <accelerator/cdrift.h>


namespace DAVIT_CLASSES {


CDrift::CDrift( const double& a_lfL, const int& a_nKind  ) : LinearBase(a_nKind, a_lfL)
{
	ObtainMatrixTrans();
	ObtainMatrixTwiss();
}



ElementBase* CDrift::Clone()const
{
	return new CDrift(*this);
}



double CDrift::DfiX(const double& beta0, const double& alfa0, const double& gama0,
					double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
					const double& lfS )const
{
	double s = ( lfS < 0. ) ? m_lfL : lfS;

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllX( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFiDrift( s, beta0, alfa0 ) ;
}



double CDrift::DfiY(const double& beta0, const double& alfa0, const double& gama0,
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


}  //  namespace DAVIT_CLASSES {
