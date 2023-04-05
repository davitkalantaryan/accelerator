//
// file:            linearbase.hpp
// path:			include/accelerator/linearbase.hpp
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <accelerator/elementbase.h>
#include <accelerator/operators_on_data_types.h>

namespace DAVIT_CLASSES{

class ACCELERATOR_EXPORT LinearBase : public ElementBase
{
public:
	virtual ~LinearBase() override;
	LinearBase( const int& Kind = LINEARBASE, const double& Length = 0. );
	
	virtual ElementBase*		Clone()const override;
	virtual void				EQUATING( ElementBase* pSource ) override;
	virtual void				SetFieldsPassive( const int& WhichParam, const double& Param, const int& Index ) override;
	virtual void				SetFields( const int& WhichParam, const double& Param, const int& Index ) override;
	virtual int					GetIndex(const char*)const override;
	const SMatrix&				GetMatrixTrans()const override;
	virtual SMatrix				GetMatrixTrans(	const double& a_lfS )const override;
	const SMatrix&				GetMatrixTwiss()const override;
	virtual SMatrix				GetMatrixTwiss(	const double& a_lfS )const;
	void						GetTwissAllX(	
										const double& beta0, const double& alfa0, const double& gama,
										double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF )const;
	void						GetTwissAllY(
										const double& beta0, const double& alfa0, const double& gama,
										double*const& pBetaF, double*const& pAlfaF, double*const& pGamaF )const;
	
	virtual double				DfiX(
									const double& beta0, const double& alfa0, const double& gama0 = -1.,
									double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
									const double& lfS = -1.)const;

	virtual double				DfiY(
									const double& beta0, const double& alfa0, const double& gama0,
									double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
									const double& lfS = -1.	)const;
	
	virtual inline void			ObtainMatrixTrans( )
	{			
		m_MatrixTrans = ElementBase::CFuncs::ObtainMatrixTransDrift( m_lfL );
	}

		
	virtual inline void			ObtainMatrixTwiss( )
	{
		m_MatrixTwiss = ElementBase::CFuncs::ObtainMatrixTwiss( m_MatrixTrans );
	}

		
	inline virtual SVector		Track( const SVector& coord0, bool*const& /*survive*/, int*const& /*losseIndex*/ )
	{
		return m_MatrixTrans * coord0;
	}


	inline virtual void GetTwissParam(	double& lfRet, const int& /*nWhere1*/, const int& whichParam,
										const STwiss& aTwis0, STwiss*const& pTwisF)const
	{

		switch( whichParam )
		{/// Switch
		case MTR11:
			lfRet = m_MatrixTrans.m11 ;
			break;
		case MTR12:
			lfRet = m_MatrixTrans.m12;
			break;
		case MTR13:
			lfRet = m_MatrixTrans.m13;
			break;
		case MTR14:
			lfRet = m_MatrixTrans.m14;
			break;
		case MTR15:
			lfRet = m_MatrixTrans.m15;
			break;
		case MTR16:
			lfRet = m_MatrixTrans.m16;
			break;
		
		case MTR21:
			lfRet = m_MatrixTrans.m21;
			break;
		case MTR22:
			lfRet = m_MatrixTrans.m22;
			break;
		case MTR23:
			lfRet = m_MatrixTrans.m23;
			break;
		case MTR24:
			lfRet = m_MatrixTrans.m24;
			break;
		case MTR25:
			lfRet = m_MatrixTrans.m25;
			break;
		case MTR26:
			lfRet = m_MatrixTrans.m26;
			break;
		
		case MTR31:
			lfRet = m_MatrixTrans.m31;
			break;
		case MTR32:
			lfRet = m_MatrixTrans.m32;
			break;
		case MTR33:
			lfRet = m_MatrixTrans.m33;
			break;
		case MTR34:
			lfRet = m_MatrixTrans.m34;
			break;
		case MTR35:
			lfRet = m_MatrixTrans.m35;
			break;
		case MTR36:
			lfRet = m_MatrixTrans.m36;
			break;
		
		case MTR41:
			lfRet = m_MatrixTrans.m41;
			break;
		case MTR42:
			lfRet = m_MatrixTrans.m42;
			break;
		case MTR43:
			lfRet = m_MatrixTrans.m43;
			break;
		case MTR44:
			lfRet = m_MatrixTrans.m44;
			break;
		case MTR45:
			lfRet = m_MatrixTrans.m45;
			break;
		case MTR46:
			lfRet = m_MatrixTrans.m46;
			break;
		
		case MTR51:
			lfRet = m_MatrixTrans.m51;
			break;
		case MTR52:
			lfRet = m_MatrixTrans.m52;
			break;
		case MTR53:
			lfRet = m_MatrixTrans.m53;
			break;
		case MTR54:
			lfRet = m_MatrixTrans.m54;
			break;
		case MTR55:
			lfRet = m_MatrixTrans.m55;
			break;
		case MTR56:
			lfRet = m_MatrixTrans.m56;
			break;
		
		case MTR61:
			lfRet = m_MatrixTrans.m61;
			break;
		case MTR62:
			lfRet = m_MatrixTrans.m62;
			break;
		case MTR63:
			lfRet = m_MatrixTrans.m63;
			break;
		case MTR64:
			lfRet = m_MatrixTrans.m64;
			break;
		case MTR65:
			lfRet = m_MatrixTrans.m65;
			break;
		case MTR66:
			lfRet = m_MatrixTrans.m66;
			break;

		case ETAX:
			lfRet = m_MatrixTrans.m11*aTwis0.etaX + m_MatrixTrans.m12*aTwis0.etaPhX + m_MatrixTrans.m16;
			break;
		case ETAPHX:
			lfRet = m_MatrixTrans.m21*aTwis0.etaX + m_MatrixTrans.m22*aTwis0.etaPhX + m_MatrixTrans.m26;
			break;

		case ETAY:
			lfRet = m_MatrixTrans.m33*aTwis0.etaY + m_MatrixTrans.m34*aTwis0.etaPhY + m_MatrixTrans.m36;
			break;
		case ETAPHY:
			lfRet = m_MatrixTrans.m43*aTwis0.etaY + m_MatrixTrans.m44*aTwis0.etaPhY + m_MatrixTrans.m46;
			break;

		case QX:
			lfRet = PIKes + atan( aTwis0.alfaX - m_MatrixTrans.m11 * aTwis0.betaX / m_MatrixTrans.m12 );
			break;
		case QY:
			lfRet = PIKes + atan( aTwis0.alfaY - m_MatrixTrans.m33 * aTwis0.betaY / m_MatrixTrans.m34 );
			break;
		
			/////////// Here special treatment
		case BETAX:
			lfRet = m_MatrixTwiss.m11 * aTwis0.betaX +
					m_MatrixTwiss.m12 * aTwis0.alfaX +
					m_MatrixTwiss.m13 * aTwis0.gamaX;
			break;
		case ALFAX:
			lfRet = m_MatrixTwiss.m21 * aTwis0.betaX +
					m_MatrixTwiss.m22 * aTwis0.alfaX +
					m_MatrixTwiss.m23 * aTwis0.gamaX;
			break;
		case GAMAX:
			lfRet = m_MatrixTwiss.m31 * aTwis0.betaX +
					m_MatrixTwiss.m32 * aTwis0.alfaX +
					m_MatrixTwiss.m33 * aTwis0.gamaX;
			break;
		case DFIX:
			lfRet = DfiX(	aTwis0.betaX, aTwis0.alfaX, aTwis0.gamaX,
							&pTwisF->betaX, &pTwisF->alfaX, &pTwisF->gamaX );
			break;
			
		case BETAY:
			lfRet = m_MatrixTwiss.m44 * aTwis0.betaY +
					m_MatrixTwiss.m45 * aTwis0.alfaY +
					m_MatrixTwiss.m46 * aTwis0.gamaY;
			break;
		case ALFAY:
			lfRet = m_MatrixTwiss.m54 * aTwis0.betaY +
					m_MatrixTwiss.m55 * aTwis0.alfaY +
					m_MatrixTwiss.m56 * aTwis0.gamaY;
			break;
		case GAMAY:
			lfRet = m_MatrixTwiss.m64 * aTwis0.betaY +
					m_MatrixTwiss.m65 * aTwis0.alfaY +
					m_MatrixTwiss.m66 * aTwis0.gamaY;
			break;
		case DFIY:
			lfRet = DfiY(	aTwis0.betaY, aTwis0.alfaY, aTwis0.gamaY,
							&pTwisF->betaY, &pTwisF->alfaY, &pTwisF->gamaY );
			break;
			
		default:
			break;
		}/// End Switch
		
	}


protected:
	SMatrix			m_MatrixTrans;
	SMatrix			m_MatrixTwiss;
};

}  //  namespace DAVIT_CLASSES{
