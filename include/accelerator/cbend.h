#ifndef __cbend_h__
#define __cbend_h__



#include "linearbase.h"


namespace DAVIT_CLASSES
{
	// Sector dipol
	class CBend : public LinearBase
	{
	public:
		enum _PARAMS{CURV = _PARAMS_ACCELEM_LAST, _PARAMS_BEND_LAST};

		CBend( const double& a_lfL = 0., const double& a_H = 0.01, const int& a_nKind = BEND );

		virtual ElementBase*	Clone()const;

		void					EQUATING( ElementBase* pSource );
		
		virtual inline void SetFieldsPassive( const int& nWhich, const double& lfParam, const int& nIndex )
		{

			if( nWhich == CURV )
				m_lfH = lfParam;
			else
				ElementBase::SetFieldsVeryPassive( LENGTH, lfParam, nIndex );

		}


		const double& GetFields( const int& nWhich, const int& /*Index*/ )const
		{
			if( nWhich == CURV )
				return m_lfH;
			
			return m_lfL;
		}


		inline void SetFields( const int& nWhichParam, const double& Param, const int& Index )
		{

			CBend::SetFieldsPassive( nWhichParam, Param, Index );

			ObtainMatrixTrans();
			ObtainMatrixTwiss();

		}

		virtual void		ReadFromFile1( FILE* File, void* Reserved, void* pFounded );

		virtual void		WriteToFile1( FILE* a_File )const;

		//void WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const;

		//virtual void LoadFromString( const char*const& a_pcBuff, int a_nRead );

		virtual double DfiX(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
			const double& lfS = -1.
							)const;
		virtual double DfiY(
			const double& beta0, const double& alfa0, const double& gama0 = -1. ,
			double*const& pBetaF = 0, double*const& pAlfaF = 0, double*const& pGamaF = 0,
			const double& lfS = -1.
							)const;

		SMatrix GetMatrixTrans(	const double& a_lfS )const;

	private:
		virtual inline void ObtainMatrixTrans( )
		{
			m_MatrixTrans = CFuncs::ObtainMatrixTransBend( m_lfL, m_lfH );
		}

	protected:
		// Bending Curvature[m^-1]
		double		m_lfH;

	};
};



#endif/* #ifndef __cbend_h__ */
