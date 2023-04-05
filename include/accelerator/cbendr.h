#ifndef __cbendr_h__
#define __cbendr_h__



#include "cbend.h"

namespace DAVIT_CLASSES
{

	// Rectangular Bend
	class CBendR : public CBend
	{
	public:
		CBendR( const double& a_lfL = 0., const double& a_h = 0.01 );

		ElementBase*	Clone()const;
		
		double DfiX(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
			const double& lfS = -1.
					)const;
		double DfiY(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
			const double& lfS = -1.
					)const;

		SMatrix		GetMatrixTrans(	const double& a_lfS )const;
							

	private:
		virtual inline void ObtainMatrixTrans( )
		{
			m_MatrixTrans = CFuncs::ObtainMatrixTransBendR( m_lfL, m_lfH );
		}

	};
};



#endif/* #ifndef __cbendr_h__ */
