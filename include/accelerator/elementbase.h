//
// file:            elementbase.hpp
// path:			include/accelerator/elementbase.hpp
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#include <accelerator/export_symbols.h>
#include <accelerator/operators_on_data_types.h>
#include <accelerator/std/stdio.h>
#include <math.h>

#define		CREATED_INSIDE		0
#define		IS_RING				1

#define		INIT_FAM_NAME		"ElementInit"
#define		FAM_NAME_SIZE		50

#define		NO_INDEX			-2
#define		END_OF_LATTICE		-1

//// Atention                           ////
//// This parameter must be calculated  ////
#define		aPAR			0.03
#define		KOEF_L			100.
//// End Atention                       ////

//const double PI = 4. * atan( 1. );
#define		PI				3.14159265358979
#define		PIKes			1.570796326794897



namespace DAVIT_CLASSES{


enum{
	INITMP,
		MTR11, MTR12, MTR13, MTR14, MTR15, MTR16,
		MTR21, MTR22, MTR23, MTR24, MTR25, MTR26,
		MTR31, MTR32, MTR33, MTR34, MTR35, MTR36,
		MTR41, MTR42, MTR43, MTR44, MTR45, MTR46,
		MTR51, MTR52, MTR53, MTR54, MTR55, MTR56,
		MTR61, MTR62, MTR63, MTR64, MTR65, MTR66,
		ETAX, ETAPHX, ETAY, ETAPHY,
		QX,QY,
		BETAX, ALFAX, GAMAX, DFIX,
		BETAY, ALFAY, GAMAY, DFIY,
		ENDMP
};

class ACCELERATOR_EXPORT ElementBase
{
public:
	enum _ELEM_KIND{INIT, LINEARBASE, DRIFT, QUAD, QF, QD, 
					BEND, BENDR, SEQUENCE, LINEAR, SEXTUPOLE, APERTURE, 
					COMBINEFUNCMAGNET, END };
	enum _PARAMS{LENGTH, _PARAMS_ACCELEM_LAST};

	virtual ~ElementBase();
	ElementBase(int a_nKind = INIT, double a_lfL = 0.);

	virtual void			ObtainAll();

	/**********************************************************************
	 * Pure virtual functions
	 **********************************************************************
	 */
	virtual ElementBase*	Clone()const = 0;
	virtual void			EQUATING( ElementBase* ) = 0;
	virtual void			SetFieldsPassive( const int& WhichParam, const double& Param, const int& )=0;
	virtual void			SetFields( const int& WhichParam, const double& Param, const int& )=0;
	virtual const SMatrix&	GetMatrixTrans()const = 0;
	virtual const SMatrix&	GetMatrixTwiss()const = 0;
	virtual void			GetTwissParam(	double& lfRet, const int& /*nWhere1*/, const int& whichParam,
											const STwiss& aTwis0, STwiss*const& pTwisF )const=0;
	virtual void			ObtainMatrixTrans( )=0;
	virtual void			ObtainMatrixTwiss( )=0;
	virtual SVector			Track( const SVector& coord0, bool*const& survive, int*const& losseIndex )=0;

	/**********************************************************************
	 * End of Pure virtual functions
	 **********************************************************************
	 */
	
	static void				FamNameFromFile1( FILE* File, char* FamName );
	virtual void			ReadFromFile1( FILE* File, void* Reserved, void* pFounded );
	virtual void			WriteToFile1( FILE* a_File )const;
	virtual void			WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const;
	virtual void			LoadFromOptimString( const char*const& a_pcBuff, int a_nRead );

	/// Get members for matchings (For tests)
	double					GetTwissParam2(	const int& whichParam,
											const STwiss& aTwiss0, STwiss*const& pTwisF=NULL, 
											const int& nI1=END_OF_LATTICE, const int& nI2=NO_INDEX )const;

	static double			GetTwissParamStat(	const SMatrix& a_MatrixTrans,
												const int& whichParam, const STwiss& aTwis0, STwiss*const& pTwisF);

	virtual const double&	GetFields(const int& /*Which*/, const int& /*Index*/)const;
	virtual const double&	GetLength( )const;
	void					SetFlagHard(unsigned char Flag);
	void					SetFlag(int Bit, int Value);
	static void				SetFlagStat(int Bit, int Value, unsigned char* pFlag);
	int						GetFlag(int Bit);
	static int				GetFlagStat(int Bit,unsigned char Flag);
	const int&				GetKind()const{ return m_nKind; }

	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void			SetFieldsVeryPassive(const int&, const double& lfParam, const int&);
	virtual int				GetIndex(const char*)const;
	virtual SMatrix			GetMatrixTrans(const double& a_lfS)const;
	void					SetFamName(const char* const& a_FamName);
	bool					IsSameFamily(const char* const& a_FamName)const;
	const char*				GetFamName()const;

protected:
	int				m_nKind;			// Element Kind
	double			m_lfL;				// Element length [m]
	//int			m_nCreatedInside : 1;
	unsigned char	m_ucFlags2;
	char			m_FamName[ FAM_NAME_SIZE ];

public:
	///////////////////////////////////////////////////////////////////////////
	/// This Class is static class for all functions                        ///
	///////////////////////////////////////////////////////////////////////////
	/// static class CFuncs
	class CFuncs
	{
	public:
		inline static SMatrix ObtainMatrixTwiss( const SMatrix& MatrixTrans )
		{

			SMatrix MatrixTwiss(g_ctmUniqTrMatrix);

			MatrixTwiss.m11 = MatrixTrans.m11 * MatrixTrans.m11;
			MatrixTwiss.m12 = -2 * MatrixTrans.m12 * MatrixTrans.m11;
			MatrixTwiss.m13 = MatrixTrans.m12 * MatrixTrans.m12;

			MatrixTwiss.m21 = -MatrixTrans.m11 * MatrixTrans.m21;
			MatrixTwiss.m22 = MatrixTrans.m12 * MatrixTrans.m21 + MatrixTrans.m22 * MatrixTrans.m11;
			MatrixTwiss.m23 = -MatrixTrans.m12 * MatrixTrans.m22;

			MatrixTwiss.m31 = MatrixTrans.m21 * MatrixTrans.m21;
			MatrixTwiss.m32 = -2 * MatrixTrans.m22 * MatrixTrans.m21;
			MatrixTwiss.m33 = MatrixTrans.m22 * MatrixTrans.m22;

			/// Y direction
			MatrixTwiss.m44 = MatrixTrans.m33 * MatrixTrans.m33;
			MatrixTwiss.m45 = -2 * MatrixTrans.m34 * MatrixTrans.m33;
			MatrixTwiss.m46 = MatrixTrans.m34 * MatrixTrans.m34;

			MatrixTwiss.m54 = -MatrixTrans.m33 * MatrixTrans.m43;
			MatrixTwiss.m55 = MatrixTrans.m34 * MatrixTrans.m43 + MatrixTrans.m44 * MatrixTrans.m33;
			MatrixTwiss.m56 = -MatrixTrans.m34 * MatrixTrans.m44;

			MatrixTwiss.m64 = MatrixTrans.m43 * MatrixTrans.m43;
			MatrixTwiss.m65 = -2 * MatrixTrans.m44 * MatrixTrans.m43;
			MatrixTwiss.m66 = MatrixTrans.m44 * MatrixTrans.m44;

			return MatrixTwiss;


		}

		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransDrift( const double& lfS )
		{
			SMatrix MatrRet(g_ctmUniqTrMatrix);
			MatrRet.m34 = MatrRet.m12 = lfS;

			return MatrRet;
		}

		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransQuad( const double& a_lfS, const double& a_lfG, const double& a_lfK )
		{
			//if( fabs( lfG ) < ACCURATY )
			if( a_lfG < 0. )
				return ObtainMatrixTransQD( a_lfS, a_lfK );

			if( a_lfG > 0. )
				return ObtainMatrixTransQF( a_lfS, a_lfK );

			return ObtainMatrixTransDrift( a_lfS );
		}

		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransQF( const double& lfS, const double& a_lfK )
		{
			SMatrix MatrRet(g_ctmUniqTrMatrix);
			double
			Phase( lfS * a_lfK ),	
			cosPhase( cos( Phase ) ),
			sinPhase( sin( Phase ) ),	
			coshPhase( cosh( Phase ) ),
			sinhPhase( sinh( Phase ) );

			MatrRet.m11 = cosPhase;
			MatrRet.m12 = sinPhase / a_lfK ;
			
			MatrRet.m21 = -a_lfK * sinPhase;
			MatrRet.m22 = cosPhase;
			
			/// Y Direction
			MatrRet.m33 = coshPhase;
			MatrRet.m34 = sinhPhase / a_lfK ;
			
			MatrRet.m43 = a_lfK * sinhPhase;
			MatrRet.m44 = coshPhase;

			return MatrRet;
		}
		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransQD( const double& lfS, const double& a_lfK )
		{
			SMatrix MatrRet(g_ctmUniqTrMatrix);
			double
				Phase( lfS * a_lfK ),	
				cosPhase( cos( Phase ) ),
				sinPhase( sin( Phase ) ),	
				coshPhase( cosh( Phase ) ),
				sinhPhase( sinh( Phase ) );

			MatrRet.m11 = coshPhase;
			MatrRet.m12 = sinhPhase / a_lfK ;
			
			MatrRet.m21 = a_lfK * sinhPhase;
			MatrRet.m22 = coshPhase;
			
			/// Y Direction
			MatrRet.m33 = cosPhase;
			MatrRet.m34 = sinPhase / a_lfK ;
			
			MatrRet.m43 = -a_lfK * sinPhase;
			MatrRet.m44 = cosPhase;

			return MatrRet;
		}
		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransBend( const double& lfS, const double& h )
		{
			SMatrix MatrRet(g_ctmUniqTrMatrix);
			double
				lfR( 1. / h ),
				Phase( h * lfS ),
				PhaseKes( Phase / 2. );

			MatrRet.m11 = cos( Phase );
			MatrRet.m12 = lfR * sin( Phase );
			MatrRet.m16 = lfR * (1. - cos( Phase ) );
			
			MatrRet.m21 = -h * sin( Phase );
			MatrRet.m22 = cos( Phase );
			MatrRet.m26 = sin( Phase );
			
			/// Y Direction
			MatrRet.m34 = lfS ;

			return MatrRet;
		}
		//enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		inline static SMatrix ObtainMatrixTransBendR(	const double& lfS, const double& h,
														const double& lfL_Bend = -1., const double& a = aPAR )
		{
			SMatrix MatrEdge(g_ctmUniqTrMatrix), MatrRet(g_ctmUniqTrMatrix);
			double
				lfR( 1. / h ),
				Phase( h * lfS ),
				PhaseKes( Phase / 2. );

			MatrEdge.m21 =  h * tan( PhaseKes );
			MatrEdge.m43 = -h * tan( PhaseKes ) + h * h * a;

			if( lfL_Bend < 0. )
			{
				MatrRet = MatrEdge * ObtainMatrixTransBend( lfS, h ) * MatrEdge;
			}
			else if( lfL_Bend < lfS )
			{
				MatrRet = ObtainMatrixTransDrift( lfS - lfL_Bend ) *
					MatrEdge * ObtainMatrixTransBend( lfS, h ) * MatrEdge;
			}
			else
			{
				MatrRet = ObtainMatrixTransBend( lfS, h ) * MatrEdge;
			}

			return MatrRet;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////
		//// Function for obtaining phase advances in different elements                               ////
		///////////////////////////////////////////////////////////////////////////////////////////////////
		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		//// This function obtains phase advances for drift X and Y and for Bend Y
		inline static double ObtainDFiDrift( const double& lfS, const double& beta0, const double& alfa0 )
		{
			return ( PIKes + atan( alfa0 - beta0 / lfS ) ) ;
		}

		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		//// This function obtains phase advances for QF-X, QD-Y, BEND-X
		inline static double ObtainDFiQF(	const double& lfS, const double& beta0, const double& alfa0, 
											const double& a_lfK /* = sqrt( g ) */ )
		{
			double Phase( a_lfK * lfS  );
			double N = floor( Phase / PI );
			return ( N*PI + PIKes + atan( alfa0 - beta0*a_lfK / tan( Phase ) ) ) ;
		}

		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		//// This function obtains phase advances for QF-Y, QD-X
		inline static double ObtainDFiQD(	const double& lfS, const double& beta0, const double& alfa0, 
											const double& a_lfK /* = sqrt( g ) */ )
		{
			return ( PIKes + atan( alfa0 - beta0*a_lfK / tanh( a_lfK * lfS ) ) ) ;
		}

		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, END };
		//// This function obtains phase advances for BENDR-X
		inline static double ObtainDFiBendRx(	const double& lfS, const double& beta0, const double& alfa0, 
												const double& hx /* = 1 / R  */, const double& L )
		{
			double
				delta( hx*L / 2. ),
				N( floor( hx*lfS / PI ) ),
				Phase(hx*lfS);

			return ( N*PI + PIKes +
				atan( alfa0 - beta0*hx*( cos(Phase) + tan(delta) * sin(Phase) ) / sin( Phase ) ) ) ;
		}

		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, LINEAR, END };
		//// This function obtains phase advances for BENDR-Y
		inline static double ObtainDFiBendRy(	const double& lfS, const double& beta0, const double& alfa0, 
												const double& hx /* = 1 / R  */, const double& L, const double& a )
		{
			double delta( hx*L / 2. ), ke( hx*tan(delta) - a*hx*hx );

			return ( PIKes + atan( alfa0 - beta0*( 1 - ke*lfS ) / lfS ) ) ;
		}

		//// enum {INIT, DRIFT, QUAD, QF, QD, BEND, BENDR, SEQ, LINEAR, END };
		//// This function obtains phase advances for BENDR-Y
		inline static double ObtainDFi(	const double& m11, const double& m12,
										const double& beta0, const double& alfa0 )
		{
			return ( PIKes + atan( alfa0 - beta0 * m11 / m12 ) ) ;
		}

	};/// End class CFuncs
	///////////////////////////////////////////////////////////////////////////
	/// This Class is static class for all functions                        ///
	///////////////////////////////////////////////////////////////////////////


};/* end class ElementBase */

}/* end namespace DAVIT_CLASSES */
