#include "stdafx.h"
#include "caperture.h"


using namespace DAVIT_CLASSES;

CAperture::CAperture()
	:	ElementBase(APERTURE,0.)
{
	m_lfHeigth = 1.;
	m_lfWeigth = 1.;
}



ElementBase* CAperture::Clone()const
{
	return new CAperture(*this);
}



void CAperture::EQUATING( ElementBase* pSource )
{
	CAperture* pAperture = (CAperture*)pSource;

	m_lfL		= pAperture->m_lfL;

	m_lfHeigth	= pAperture->m_lfHeigth;
	m_lfWeigth	= pAperture->m_lfWeigth;
}



const double& CAperture::GetFields( const int& a_nWhich, const int& /*Index*/ )const
{
	switch(a_nWhich)
	{
	case HEIGTH:
		return m_lfHeigth;
		break;

	case WEIGTH:
		return m_lfWeigth;
		break;

	default:
		break;
	}


	return ElementBase::GetFields(a_nWhich,END_OF_LATTICE);
}



void CAperture::SetFieldsPassive( const int& WhichParam, const double& Param, const int&)
{

	//enum _PARAMS{HEIGTH = _PARAMS_ACCELEM_LAST, WEIGTH, _PARAMS_APT_LAST};
	switch(WhichParam)
	{
	case HEIGTH:
		m_lfHeigth = Param;
		break;

	case WEIGTH:
		m_lfWeigth = Param;
		break;

	default:
		m_lfL = Param;
		break;
	}
}



void CAperture::SetFields( const int& WhichParam, const double& Param, const int& Index)
{
	CAperture::SetFieldsPassive(WhichParam,Param,Index);
}



void CAperture::WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const
{
}



void CAperture::LoadFromOptimString( const char*const& a_pcBuff, int a_nRead )
{
}



const SMatrix& CAperture::GetMatrixTrans()const
{
	return g_cmUnitMartix;
}



const SMatrix& CAperture::GetMatrixTwiss()const
{
	return g_cmUnitMartix;
}



void CAperture::GetTwissParam(double& lfRet, const int& /*nWhere1*/, const int& whichParam,
							  const STwiss& aTwis0, STwiss*const& pTwisF)const
{
	switch( whichParam )
	{/// Switch

	case MTR11: case MTR22: case MTR33: case MTR44: case MTR55: case MTR66:
		lfRet = 1. ;
		break;
	case MTR12: case MTR13: case MTR14: case MTR15: case MTR16:
	case MTR21: case MTR23: case MTR24: case MTR25:	case MTR26:
	case MTR31: case MTR32: case MTR34: case MTR35: case MTR36:
	case MTR41: case MTR42: case MTR43: case MTR45: case MTR46:
	case MTR51: case MTR52: case MTR53: case MTR54: case MTR56:
	case MTR61: case MTR62: case MTR63: case MTR64: case MTR65:
		lfRet = 0.;
		break;

	case ETAX:
		lfRet = aTwis0.etaX;
		break;
	case ETAPHX:
		lfRet = aTwis0.etaPhX;
		break;

	case ETAY:
		lfRet = aTwis0.etaY;
		break;
	case ETAPHY:
		lfRet = aTwis0.etaPhY;
		break;

	case QX: case QY:
		lfRet = 0.;
		break;
	
		/////////// Here special treatment
	case BETAX:
		lfRet = aTwis0.betaX;
		break;
	case ALFAX:
		lfRet = aTwis0.alfaX;
		break;
	case GAMAX:
		lfRet = aTwis0.gamaX;
		break;
	case DFIX:
		//lfRet = DfiX(	aTwis0.betaX, aTwis0.alfaX, aTwis0.gamaX,
		//				&pTwisF->betaX, &pTwisF->alfaX, &pTwisF->gamaX );
		break;
		
	case BETAY:
		lfRet = aTwis0.betaY;
		break;
	case ALFAY:
		lfRet = aTwis0.alfaY;
		break;
	case GAMAY:
		lfRet = aTwis0.gamaY;
		break;
	case DFIY:
		//lfRet = DfiY(	aTwis0.betaY, aTwis0.alfaY, aTwis0.gamaY,
		//				&pTwisF->betaY, &pTwisF->alfaY, &pTwisF->gamaY );
		break;
		
	default:
		break;
	}/// End Switch
}



void CAperture::ObtainMatrixTrans( )
{
}



void CAperture::ObtainMatrixTwiss( )
{
}



SVector CAperture::Track( const SVector& coord0, bool*const& survive, int*const& )
{
	*survive = fabs(coord0.x) < m_lfWeigth && fabs(coord0.y) < m_lfHeigth;

	return coord0;
}



void CAperture::ReadFromFile1( FILE* a_File, void* a_pReserved, void* a_pFounded )
{

	ElementBase::ReadFromFile1( a_File, a_pReserved, a_pFounded );
	
	/*fread( &m_lfL, sizeof(m_lfL), 1, a_File );

	char* aFamName = NULL;

	ElementCreator::StringFromFile( a_File, &aFamName );

	strncpy( m_FamName, aFamName,FAM_NAME_SIZE );

	fread( &m_ucFlags, sizeof(m_ucFlags), 1, a_File );*/

}

