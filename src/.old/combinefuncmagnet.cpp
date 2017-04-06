#include "stdafx.h"
#include "combinefuncmagnet.h"




CombineFuncMagnet::CombineFuncMagnet(const double& lfL, const double& lfH, 
									 const double& lfg, const int& nKind)
	:	LinearBase(nKind,lfL),
		m_lfh(lfH),
		m_lfg(lfg)
{
	m_MatrixTrans.m51 = 0.;
	m_MatrixTrans.m52 = 0.;
	m_MatrixTrans.m53 = 0.;
	m_MatrixTrans.m54 = 0.;
	m_MatrixTrans.m55 = 1.;
	m_MatrixTrans.m56 = 0.;

	m_MatrixTrans.m51 = 0.;
	m_MatrixTrans.m52 = 0.;
	m_MatrixTrans.m53 = 0.;
	m_MatrixTrans.m54 = 0.;
	m_MatrixTrans.m55 = 0.;
	m_MatrixTrans.m56 = 1.;
}



ElementBase* CombineFuncMagnet::Clone()const
{
	return new CombineFuncMagnet(*this);
}



void CombineFuncMagnet::EQUATING( ElementBase* a_pSource )
{
	CombineFuncMagnet* pMagnet = (CombineFuncMagnet*)a_pSource;

	LinearBase::EQUATING(a_pSource);

	m_lfh = pMagnet->m_lfh;
	m_lfg = pMagnet->m_lfg;
}



const double& CombineFuncMagnet::GetFields( const int& nWhichParam, const int& nIndex )const
{
	switch( nWhichParam )
	{
	case CombineFuncMagnet::CURV:
		return m_lfh;
	case CombineFuncMagnet::GRADIENT:
		return m_lfg;
	default:
		break;
	}

	return LinearBase::GetFields( nWhichParam, nIndex );
}



void CombineFuncMagnet::SetFieldsPassive( const int& nWhichParam, const double& lfParam, const int& nIndex )
{
	//enum _PARAMS{CURV = _PARAMS_ACCELEM_LAST, GRADIENT, _PARAMS_COMBINE_LAST};
	switch( nWhichParam )
	{
	case CombineFuncMagnet::CURV:
		m_lfh = lfParam;
		break;
	case CombineFuncMagnet::GRADIENT:
		m_lfg = lfParam;
		break;
	default:
		LinearBase::SetFieldsVeryPassive( nWhichParam, lfParam, nIndex );
		break;
	}
}



void CombineFuncMagnet::SetFields(  const int& nWhichParam, const double& lfParam, const int& nIndex )
{
	CombineFuncMagnet::SetFieldsPassive( nWhichParam, lfParam, nIndex );
	CombineFuncMagnet::ObtainMatrixTrans();
	CombineFuncMagnet::ObtainMatrixTwiss();
}



SMatrix	CombineFuncMagnet::GetMatrixTrans(	const double& a_lfS )const
{
	CombineFuncMagnet aMagnet(*this);

	aMagnet.SetFieldsPassive(ElementBase::LENGTH, a_lfS, END_OF_LATTICE);

	aMagnet.ObtainMatrixTrans();

	LinearBase* pMagnet = &aMagnet;

	return pMagnet->GetMatrixTrans();
}



double CombineFuncMagnet::DfiX(
								const double& beta0, const double& alfa0, const double& gama0,
								double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
								const double& lfS)const
{
	return 0.;
}



double CombineFuncMagnet::DfiY(
								const double& beta0, const double& alfa0, const double& gama0,
								double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF,
								const double& lfS	)const
{
	return 0.;
}



void CombineFuncMagnet::ObtainMatrixTrans( )
{

	if( m_lfg > 0. )
	{
		double lfKxPow2(m_lfg+m_lfh*m_lfh), lfKx(sqrt(lfKxPow2)), lfFix(lfKx*m_lfL);
		double                              lfKy(sqrt(m_lfg)),   lfFiy(lfKy*m_lfL);

		m_MatrixTrans.m11 = cos(lfFix);
		m_MatrixTrans.m12 = sin(lfFix)/lfKx;
		m_MatrixTrans.m16 = m_lfh*(1-cos(lfFix))/lfKxPow2;

		m_MatrixTrans.m21 = -lfKx*sin(lfFix);
		m_MatrixTrans.m22 = cos(lfFix);
		m_MatrixTrans.m26 = m_lfh*sin(lfFix)/lfKx;

		m_MatrixTrans.m33 = cosh(lfFiy);
		m_MatrixTrans.m34 = sinh(lfFiy)/lfKy;

		m_MatrixTrans.m43 = lfKy*sinh(lfFiy);
		m_MatrixTrans.m44 = cosh(lfFiy);
	}
	else if( m_lfg < 0. )
	{
		double lfKxPow2(-m_lfg-m_lfh*m_lfh),	lfKy(sqrt(-m_lfg)),   lfFiy(lfKy*m_lfL);

		if(lfKxPow2 > 0.)
		{
			double lfKx(sqrt(lfKxPow2)), lfFix(lfKx*m_lfL);

			m_MatrixTrans.m11 = cosh(lfFix);
			m_MatrixTrans.m12 = sinh(lfFix)/lfKx;
			m_MatrixTrans.m16 = m_lfh*(cosh(lfFix)-1)/lfKxPow2;

			m_MatrixTrans.m21 = lfKx*sinh(lfFix);
			m_MatrixTrans.m22 = cosh(lfFix);
			m_MatrixTrans.m26 = m_lfh*sinh(lfFix)/lfKx;
		}
		else if(lfKxPow2 < 0.)
		{
			lfKxPow2 = -lfKxPow2;
			double lfKx(sqrt(lfKxPow2)), lfFix(lfKx*m_lfL);

			m_MatrixTrans.m11 = cos(lfFix);
			m_MatrixTrans.m12 = sin(lfFix)/lfKx;
			m_MatrixTrans.m16 = m_lfh*(1-cos(lfFix))/lfKxPow2;

			m_MatrixTrans.m21 = -lfKx*sin(lfFix);
			m_MatrixTrans.m22 = cos(lfFix);
			m_MatrixTrans.m26 = m_lfh*sin(lfFix)/lfKx;
		}
		else //lfKxPow2 == 0.
		{
			m_MatrixTrans.m11 = 1.;
			m_MatrixTrans.m12 = m_lfL;
			m_MatrixTrans.m16 = 0.5*m_lfh*m_lfL*m_lfL;

			m_MatrixTrans.m21 = 0.;
			m_MatrixTrans.m22 = 1.;
			m_MatrixTrans.m26 = m_lfh*m_lfL;
		}

		m_MatrixTrans.m33 = cos(lfFiy);
		m_MatrixTrans.m34 = sin(lfFiy)/lfKy;

		m_MatrixTrans.m43 = -lfKy*sin(lfFiy);
		m_MatrixTrans.m44 = cos(lfFiy);
	}
	else
	{
		m_MatrixTrans = CFuncs::ObtainMatrixTransBend( m_lfL, m_lfh );
	}
}



void CombineFuncMagnet::WriteToFile1( FILE* a_File )const
{
	ElementBase::WriteToFile1( a_File );
	fwrite( &m_lfh, sizeof(m_lfh), 1, a_File );
	fwrite( &m_lfg, sizeof(m_lfg), 1, a_File );
}



void CombineFuncMagnet::ReadFromFile1( FILE* a_File, void*, void* )
{
	ElementBase::ReadFromFile1( a_File, NULL, NULL );
	fread( &m_lfh, sizeof(m_lfh), 1, a_File );
	fread( &m_lfg, sizeof(m_lfg), 1, a_File );
}
