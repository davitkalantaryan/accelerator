#include "stdafx.h"
#include <accelerator/clinear.h>


namespace DAVIT_CLASSES {


CLinear::CLinear(const SMatrix& a_MatrTrans, const double& a_lfL, const int& a_nKind)
	:	LinearBase( a_nKind, a_lfL )
{
	
	m_MatrixTrans = a_MatrTrans ;
	ObtainMatrixTwiss();
}



ElementBase* CLinear::Clone()const
{
	return new CLinear(*this);
}



void CLinear::SetFieldsPassive( const int&, const double&, const int&)
{
}


	
void CLinear::SetFields( const int&, const double&, const int& )
{
}



double CLinear::DfiX(const double& beta0, const double& alfa0, const double& gama0,
					 double*const pBetaF, double*const pAlfaF, double*const pGamaF,
					 const double& lfS )const
{

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFi( m_MatrixTrans.m11, m_MatrixTrans.m12, beta0, alfa0 ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllX( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFi( m_MatrixTrans.m11, m_MatrixTrans.m12, beta0, alfa0 ) ;
}



double CLinear::DfiY(const double& beta0, const double& alfa0, const double& gama0,
					 double*const pBetaF, double*const pAlfaF, double*const pGamaF,
					 const double& lfS )const
{

	if( !pBetaF && !pAlfaF && !pGamaF )
	{
		return CFuncs::ObtainDFi( m_MatrixTrans.m33, m_MatrixTrans.m34, beta0, alfa0 ) ;
	}

	double gama = ( gama0 < 0. ) ? ( 1 + alfa0*alfa0 ) / beta0 : gama0 ;
	

	GetTwissAllY( beta0, alfa0, gama, pBetaF, pAlfaF, pGamaF );
	
	return CFuncs::ObtainDFi( m_MatrixTrans.m11, m_MatrixTrans.m12, beta0, alfa0 ) ;
}



double ElementBase::GetTwissParamStat(const SMatrix& a_MatrixTrans,
									  const int& whichParam, const STwiss& aTwis0, STwiss*const& pTwisF)
{
	CLinear aLinear;

	aLinear.SetMatrixes( a_MatrixTrans );

	double lfRet(0.);

	aLinear.GetTwissParam( lfRet, END_OF_LATTICE, whichParam,aTwis0, pTwisF );

	return lfRet;
}


}  //  namespace DAVIT_CLASSES {
