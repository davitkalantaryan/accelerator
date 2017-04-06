#include "stdafx.h"
#include "linearbase.h"

#include "elementcreator.h"



LinearBase::LinearBase( const int& Kind, const double& Length )
	:	ElementBase(Kind,Length),
		m_MatrixTrans( g_cmUnitMartix ),
		m_MatrixTwiss( g_cmUnitMartix )
{
}



ElementBase* LinearBase::Clone()const
{
	return new LinearBase(*this);
}



void LinearBase::EQUATING( ElementBase* pSource )
{

	//ElementBase::EQUATING(pSource);
	
	LinearBase*& pLinear = (LinearBase*&)pSource;

	m_lfL			= pLinear->m_lfL ;
	m_MatrixTrans	= pLinear->m_MatrixTrans;
	m_MatrixTwiss	= pLinear->m_MatrixTwiss;
}



void LinearBase::SetFieldsPassive( const int&, const double& Param, const int& )
{
	m_lfL = Param;
}



void LinearBase::SetFields( const int&, const double& Param, const int& )
{
	m_lfL = Param;
	ObtainMatrixTrans();
	ObtainMatrixTwiss();
}



int LinearBase::GetIndex(const char*)const
{
	return END_OF_LATTICE;
}



SMatrix LinearBase::GetMatrixTrans(	const double& a_lfS )const
{
	return ElementBase::CFuncs::ObtainMatrixTransDrift( a_lfS );
}



SMatrix LinearBase::GetMatrixTwiss(	const double& a_lfS )const
{
	SMatrix Matrix = ElementBase::CFuncs::ObtainMatrixTransDrift( a_lfS );

	return ElementBase::CFuncs::ObtainMatrixTwiss( Matrix );
}



void LinearBase::GetTwissAllX(const double& beta0, const double& alfa0, const double& gama,
							  double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF )const
{
	if( pBetaF )
		*pBetaF = m_MatrixTwiss.m11 * beta0 + m_MatrixTwiss.m12 * alfa0 + m_MatrixTwiss.m13 * gama;
	
	if( pAlfaF )
		*pAlfaF = m_MatrixTwiss.m21 * beta0 + m_MatrixTwiss.m22 * alfa0 + m_MatrixTwiss.m23 * gama;
	
	if( pGamaF )
		*pGamaF = m_MatrixTwiss.m31 * beta0 + m_MatrixTwiss.m32 * alfa0 + m_MatrixTwiss.m33 * gama;
}



void LinearBase::GetTwissAllY(	const double& beta0, const double& alfa0, const double& gama,
									double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF )const
{
	if( pBetaF )
		*pBetaF = m_MatrixTwiss.m44 * beta0 + m_MatrixTwiss.m45 * alfa0 + m_MatrixTwiss.m46 * gama;
	
	if( pAlfaF )
		*pAlfaF = m_MatrixTwiss.m54 * beta0 + m_MatrixTwiss.m55 * alfa0 + m_MatrixTwiss.m56 * gama;
	
	if( pGamaF )
		*pGamaF = m_MatrixTwiss.m64 * beta0 + m_MatrixTwiss.m65 * alfa0 + m_MatrixTwiss.m66 * gama;
}



double LinearBase::DfiX(const double& beta0, const double& alfa0, const double& gama0,
						double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
						const double& lfS)const
{
	double gama = ( gama0 < 0. ) ? ( ( 1 + alfa0 * alfa0 ) / beta0 ) : gama0;
	double
	betaF( m_MatrixTwiss.m11 * beta0 + m_MatrixTwiss.m12 * alfa0 + m_MatrixTwiss.m13 * gama ),
	alfaF( m_MatrixTwiss.m21 * beta0 + m_MatrixTwiss.m22 * alfa0 + m_MatrixTwiss.m23 * gama ),
	gamaF( m_MatrixTwiss.m31 * beta0 + m_MatrixTwiss.m32 * alfa0 + m_MatrixTwiss.m33 * gama );

	if( pBetaF )
		*pBetaF = betaF;
	if( pAlfaF )
		*pAlfaF = alfaF;
	if( pGamaF )
		*pGamaF = gamaF;

	return asin( m_MatrixTrans.m12 / sqrt( beta0 * betaF ) );
}



double LinearBase::DfiY(const double& beta0, const double& alfa0, const double& gama0,
						double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
						const double& lfS )const
{
	double gama = ( gama0 < 0. ) ? ( ( 1 + alfa0 * alfa0 ) / beta0 ) : gama0;
	double
	betaF( m_MatrixTwiss.m44 * beta0 + m_MatrixTwiss.m45 * alfa0 + m_MatrixTwiss.m46 * gama ),
	alfaF( m_MatrixTwiss.m54 * beta0 + m_MatrixTwiss.m55 * alfa0 + m_MatrixTwiss.m56 * gama ),
	gamaF( m_MatrixTwiss.m64 * beta0 + m_MatrixTwiss.m65 * alfa0 + m_MatrixTwiss.m66 * gama );

	if( pBetaF )
		*pBetaF = betaF;
	if( pAlfaF )
		*pAlfaF = alfaF;
	if( pGamaF )
		*pGamaF = gamaF;

	return asin( m_MatrixTrans.m34 / sqrt( beta0 * betaF ) );
}


