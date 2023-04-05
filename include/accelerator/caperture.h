#ifndef __caperture_h__
#define __caperture_h__


#include "elementbase.h"


namespace DAVIT_CLASSES
{
	class CAperture : public ElementBase
	{
	public:
		enum _PARAMS{HEIGTH = _PARAMS_ACCELEM_LAST, WEIGTH, _PARAMS_APT_LAST};

		CAperture();

		ElementBase*	Clone()const;


		void			EQUATING( ElementBase* );
		
		void			SetFieldsPassive( const int& WhichParam, const double& Param, const int& Index);

		void			SetFields( const int& WhichParam, const double& Param, const int& Index);

		const double&	GetFields( const int& Which, const int& Index )const;

		void			ReadFromFile1( FILE* File, void* Reserved, void* pFounded );

		void			WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const;

		void			LoadFromOptimString( const char*const& a_pcBuff, int a_nRead );

		const SMatrix&	GetMatrixTrans()const;

		const SMatrix&	GetMatrixTwiss()const;

		void			GetTwissParam(	double& lfRet, const int& /*nWhere1*/, const int& whichParam,
										const STwiss& aTwis0, STwiss*const& pTwisF)const;

		void			ObtainMatrixTrans( );

		void			ObtainMatrixTwiss( );

		SVector			Track( const SVector& coord0, bool*const& survive, int*const& losseIndex );


	private:
		double		m_lfHeigth;
		double		m_lfWeigth;

	};

};


#endif/* #ifndef __caperture_h__ */
