#ifndef __combinefuncmagnet_h__
#define __combinefuncmagnet_h__


#include "linearbase.h"


class CombineFuncMagnet : public LinearBase
{
public:
	enum _PARAMS{CURV = _PARAMS_ACCELEM_LAST, GRADIENT, _PARAMS_COMBINE_LAST};

	CombineFuncMagnet(	const double& lfL = 0., const double& lfH = 0.01, 
						const double& lfg = 0., const int& nKind = COMBINEFUNCMAGNET );

private:
	virtual ElementBase*	Clone()const;

	void					EQUATING( ElementBase* pSource );

	const double&			GetFields( const int& nWhichParam, const int& nIndex )const;

	void					SetFieldsPassive( const int& nWhichParam, const double& lfParam, const int& nIndex );

	virtual void			SetFields( const int& nWhichParam, const double& lfParam, const int& nIndex );

	virtual inline SMatrix	GetMatrixTrans(	const double& a_lfS )const;

	virtual double			DfiX(
								const double& beta0, const double& alfa0, const double& gama0 = -1.,
								double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
								const double& lfS = -1.)const;

	virtual double			DfiY(
								const double& beta0, const double& alfa0, const double& gama0,
								double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
								const double& lfS = -1.	)const;

	virtual inline void		ObtainMatrixTrans( );

	void					WriteToFile1( FILE* a_File )const;

	void					ReadFromFile1( FILE* a_File, void*, void* );

protected:
	double			m_lfh;
	double			m_lfg;
};


#endif /* #ifndef __combinefuncmagnet_h__ */
