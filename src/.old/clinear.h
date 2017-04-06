#ifndef __clinear_h__
#define __clinear_h__



#include "linearbase.h"

namespace DAVIT_CLASSES
{
	class CLinear : public LinearBase
	{
	public:
		CLinear(const SMatrix& a_MatrTrans=g_cmUnitMartix, const double& a_lfL=0., const int& a_nKind = LINEAR) ;

		ElementBase*			Clone()const;

		virtual void			SetFieldsPassive( const int& nWhich, const double& lfParam, const int& nIndex );

		virtual void			SetFields( const int& nWhich, const double& lfParam, const int& nIndex );
	
		inline void SetMatrixes( const SMatrix& a_TransMatr )
		{
			m_MatrixTrans = a_TransMatr;
			ObtainMatrixTwiss();
		}

		
		double DfiX(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const pBetaF = 0, double*const pAlfaF = 0, double*const pGamaF = 0,
			const double& lfS = -1.
					)const;

		double DfiY(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const pBetaF = 0, double*const pAlfaF = 0, double*const pGamaF = 0,
			const double& lfS = -1.
					)const;
	};
};



#endif /* #ifndef __clinear_h__ */
