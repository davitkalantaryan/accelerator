#ifndef __cquad_h__
#define __cquad_h__


#include "linearbase.h"


namespace DAVIT_CLASSES
{
	class CQuad : public LinearBase
	{
	public:
		enum _PARAMS{ GRADIENT = _PARAMS_ACCELEM_LAST, _PARAMS_QUAD_LAST };

		enum _MIRROR{ _NO_MIRROR = -1 };

		CQuad( const double& a_lfL = 0., const double& a_g = 0., const int& a_nKind = QUAD );
		
		ElementBase*	Clone()const;

		void			EQUATING( ElementBase* pSource );

		inline void SetFieldsPassive( const int& nWhich, const double& lfParam, const int& nIndex )
		{
			switch( nWhich )
			{
			case GRADIENT:
				m_g = lfParam;
				break;
			default:
				ElementBase::SetFieldsVeryPassive( nWhich, lfParam, nIndex );
				break;
			}
		}


		inline const double& GetFields( const int& a_nWhich, const int& /*Index*/ )const
		{
			if( a_nWhich == GRADIENT )
				return m_g;

			//return ElementBase::GetParam( a_nWhich );
			return m_lfL;

		}


		virtual inline void SetFields(  const int& nWhichParam, const double& lfParam, const int& Index )
		{
			switch( nWhichParam )
			{
			case GRADIENT:
				m_g = lfParam;
				m_lfK = sqrt( fabs( m_g ) );	
				m_MatrixTrans = CFuncs::ObtainMatrixTransQuad( m_lfL, m_g, m_lfK );
				ObtainMatrixTwiss();
				break;
			default:
				ElementBase::SetFieldsVeryPassive( nWhichParam, lfParam, Index );
				m_MatrixTrans = CFuncs::ObtainMatrixTransQuad( m_lfL, m_g, m_lfK );
				ObtainMatrixTwiss();
				break;
			}
		}


		void SetMirrorIndex( const int& a_nMirrorIndex );
		
		const int& GetMirrorIndex()const;

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

		SMatrix				GetMatrixTrans(	const double& a_lfS )const;

		virtual void		ReadFromFile1( FILE* File, void* Reserved, void* pFounded );

		virtual void		WriteToFile1( FILE* a_File )const;

		//void WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const;

		//virtual void LoadFromString( const char*const& a_pcBuff, int a_nRead );


	private:
		inline virtual void ObtainMatrixTrans()
		{
			m_lfK = sqrt( fabs( m_g ) );
			m_MatrixTrans = CFuncs::ObtainMatrixTransQuad( m_lfL, m_g, m_lfK );
		}


	protected:
		// Normalized gradient [m^-2]
		double			m_g;
		mutable double	m_lfK;/* = sqrt( m_g ) */
		int				m_nMirrorIndex;

	};
};



#endif/* #ifndef __cquad_h__ */
