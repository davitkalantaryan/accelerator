#ifndef __cdrift_h__
#define __cdrift_h__


#include "linearbase.h"

namespace DAVIT_CLASSES
{
	class CDrift : public LinearBase
	{
	public:
		CDrift( const double& a_lfL = 0., const int& a_nKind = DRIFT );

		virtual ElementBase*	Clone()const;

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
	};

};


#endif/* #ifndef __cdrift_h__ */
