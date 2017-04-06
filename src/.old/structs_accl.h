#ifndef __structs_accl_h__
#define __structs_accl_h__


#include <stddef.h>		// For type size_t
#include <memory.h>		// For func. memset


#ifndef int64_tt
#ifdef WIN32
#define int64_tt __int64
#else
#define int64_tt long long int
#endif
#endif


struct SVectorBase
{

	const double& operator[]( const size_t& unIndex )const
	{
		const double* pclfDbl = (const double*)this;
		return pclfDbl[ unIndex ];
	}
	double& operator[]( const size_t& unIndex )
	{
		double* plfDbl = (double*)this;
		return plfDbl[ unIndex ];
	}
};



/*struct SVector : public SVectorBase
{
	double x0;
	double x1;
	double x2;
	double x3;
	double x4;
	double x5;
};*/


struct SVector : public SVectorBase
{
	double x;
	double px;
	double y;
	double py;
	double z;
	double delta;
};



struct SVectorDec : public SVectorBase
{
	double x;
	double px;
	double y;
	double py;
	double z;
	double delta;
};



struct STwiss
{
	double betaX;
	double alfaX;
	double gamaX;
	double etaX;
	double etaPhX;

	double betaY;
	double alfaY;
	double gamaY;
	double etaY;
	double etaPhY;

	inline void ObtainGamaX()
	{ 
		gamaX = ( 1. + alfaX*alfaX ) / betaX ; 
	}
	inline void ObtainGamaY()
	{ 
		gamaY = ( 1. + alfaY*alfaY ) / betaY ; 
	}
};



inline static STwiss GetTwiss(	double betaX = 1.,
								double alfaX = 0.,
								double etaX = 0.,
								double etaPhX = 0.,
								
								double betaY = 1.,
								double alfaY = 0.,
								double etaY = 0,
								double etaPhY = 0 )
{
	STwiss TwUse;

	TwUse.betaX = betaX;
	TwUse.alfaX = alfaX;
	TwUse.ObtainGamaX();
	TwUse.etaX = etaX;
	TwUse.etaPhX = etaPhX;

	TwUse.betaY = betaY;
	TwUse.alfaY = alfaY;
	TwUse.ObtainGamaY();
	TwUse.etaY = etaY;
	TwUse.etaPhY = etaPhY;

	return TwUse;
}



struct SMatrix
{
	double m11;
	double m12;
	double m13;
	double m14;
	double m15;
	double m16;

	double m21;
	double m22;
	double m23;
	double m24;
	double m25;
	double m26;

	double m31;
	double m32;
	double m33;
	double m34;
	double m35;
	double m36;

	double m41;
	double m42;
	double m43;
	double m44;
	double m45;
	double m46;

	double m51;
	double m52;
	double m53;
	double m54;
	double m55;
	double m56;

	double m61;
	double m62;
	double m63;
	double m64;
	double m65;
	double m66;

	/// Jnjelu
	SMatrix operator-(const SMatrix& Matr2 )const
	{
		SMatrix MatrRet;

		double* pElemRet = &MatrRet.m11;
		const double* pElemMatr1 = &m11;
		const double* pElemMatr2 = &Matr2.m11;

		for( size_t i = 0; i < 36; ++i )
		{
			*pElemRet++ = *pElemMatr1++ - *pElemMatr2++;
			//pElemRet
		}

		return MatrRet;

	}

	const SVector& operator[]( const size_t& unIndex )const
	{
		const SVector* pVect = (const SVector*)this;
		return pVect[ unIndex ];
	}
	SVector& operator[]( const size_t& unIndex )
	{
		SVector* pVect = (SVector*)this;
		return pVect[ unIndex ];
	}


	inline SVector operator *( const SVector& V2 )const
	{
		SVector VUse;

		VUse.x = m11 * V2.x + m12 * V2.px + m13 * V2.y +
			m14 * V2.py + m15 * V2.z + m16 * V2.delta;
		VUse.px = m21 * V2.x + m22 * V2.px + m23 * V2.y +
			m24 * V2.py + m25 * V2.z + m26 * V2.delta;
		VUse.y = m31 * V2.x + m32 * V2.px + m33 * V2.y +
			m34 * V2.py + m35 * V2.z + m36 * V2.delta;
		VUse.py = m41 * V2.x + m42 * V2.px + m43 * V2.y +
			m44 * V2.py + m45 * V2.z + m46 * V2.delta;
		VUse.z = m51 * V2.x + m52 * V2.px + m53 * V2.y +
			m54 * V2.py + m55 * V2.z + m56 * V2.delta;
		VUse.delta = m61 * V2.x + m62 * V2.px + m63 * V2.y +
			m64 * V2.py + m65 * V2.z + m66 * V2.delta;

		return VUse;
	}

	inline SMatrix operator *( const SMatrix& M2 )const
	{
		SMatrix MUse;

		MUse.m11 = m11 * M2.m11 + m12 * M2.m21 + m13 * M2.m31 +
			m14 * M2.m41 + m15 * M2.m51 + m16 * M2.m61;
		MUse.m12 = m11 * M2.m12 + m12 * M2.m22 + m13 * M2.m32 +
			m14 * M2.m42 + m15 * M2.m52 + m16 * M2.m62;
		MUse.m13 = m11 * M2.m13 + m12 * M2.m23 + m13 * M2.m33 +
			m14 * M2.m43 + m15 * M2.m53 + m16 * M2.m63;
		MUse.m14 = m11 * M2.m14 + m12 * M2.m24 + m13 * M2.m34 +
			m14 * M2.m44 + m15 * M2.m54 + m16 * M2.m64;
		MUse.m15 = m11 * M2.m15 + m12 * M2.m25 + m13 * M2.m35 +
			m14 * M2.m45 + m15 * M2.m55 + m16 * M2.m65;
		MUse.m16 = m11 * M2.m16 + m12 * M2.m26 + m13 * M2.m36 +
			m14 * M2.m46 + m15 * M2.m56 + m16 * M2.m66;

		MUse.m21 = m21 * M2.m11 + m22 * M2.m21 + m23 * M2.m31 + 
			m24 * M2.m41 + m25 * M2.m51 + m26 * M2.m61;
		MUse.m22 = m21 * M2.m12 + m22 * M2.m22 + m23 * M2.m32 +
			m24 * M2.m42 + m25 * M2.m52 + m26 * M2.m62;
		MUse.m23 = m21 * M2.m13 + m22 * M2.m23 + m23 * M2.m33 +
			m24 * M2.m43 + m25 * M2.m53 + m26 * M2.m63;
		MUse.m24 = m21 * M2.m14 + m22 * M2.m24 + m23 * M2.m34 +
			m24 * M2.m44 + m25 * M2.m54 + m26 * M2.m64;
		MUse.m25 = m21 * M2.m15 + m22 * M2.m25 + m23 * M2.m35 +
			m24 * M2.m45 + m25 * M2.m55 + m26 * M2.m65;
		MUse.m26 = m21 * M2.m16 + m22 * M2.m26 + m23 * M2.m36 +
			m24 * M2.m46 + m25 * M2.m56 + m26 * M2.m66;

		MUse.m31 = m31 * M2.m11 + m32 * M2.m21 + m33 * M2.m31 +
			m34 * M2.m41 + m35 * M2.m51 + m36 * M2.m61;
		MUse.m32 = m31 * M2.m12 + m32 * M2.m22 + m33 * M2.m32 +
			m34 * M2.m42 + m35 * M2.m52 + m36 * M2.m62;
		MUse.m33 = m31 * M2.m13 + m32 * M2.m23 + m33 * M2.m33 +
			m34 * M2.m43 + m35 * M2.m53 + m36 * M2.m63;
		MUse.m34 = m31 * M2.m14 + m32 * M2.m24 + m33 * M2.m34 +
			m34 * M2.m44 + m35 * M2.m54 + m36 * M2.m64;
		MUse.m35 = m31 * M2.m15 + m32 * M2.m25 + m33 * M2.m35 +
			m34 * M2.m45 + m35 * M2.m55 + m36 * M2.m65;
		MUse.m36 = m31 * M2.m16 + m32 * M2.m26 + m33 * M2.m36 +
			m34 * M2.m46 + m35 * M2.m56 + m36 * M2.m66;

		MUse.m41 = m41 * M2.m11 + m42 * M2.m21 + m43 * M2.m31 +
			m44 * M2.m41 + m45 * M2.m51 + m46 * M2.m61;
		MUse.m42 = m41 * M2.m12 + m42 * M2.m22 + m43 * M2.m32 +
			m44 * M2.m42 + m45 * M2.m52 + m46 * M2.m62;
		MUse.m43 = m41 * M2.m13 + m42 * M2.m23 + m43 * M2.m33 +
			m44 * M2.m43 + m45 * M2.m53 + m46 * M2.m63;
		MUse.m44 = m41 * M2.m14 + m42 * M2.m24 + m43 * M2.m34 +
			m44 * M2.m44 + m45 * M2.m54 + m46 * M2.m64;
		MUse.m45 = m41 * M2.m15 + m42 * M2.m25 + m43 * M2.m35 +
			m44 * M2.m45 + m45 * M2.m55 + m46 * M2.m65;
		MUse.m46 = m41 * M2.m16 + m42 * M2.m26 + m43 * M2.m36 +
			m44 * M2.m46 + m45 * M2.m56 + m46 * M2.m66;

		MUse.m51 = m51 * M2.m11 + m52 * M2.m21 + m53 * M2.m31 +
			m54 * M2.m41 + m55 * M2.m51 + m56 * M2.m61;
		MUse.m52 = m51 * M2.m12 + m52 * M2.m22 + m53 * M2.m32 +
			m54 * M2.m42 + m55 * M2.m52 + m56 * M2.m62;
		MUse.m53 = m51 * M2.m13 + m52 * M2.m23 + m53 * M2.m33 +
			m54 * M2.m43 + m55 * M2.m53 + m56 * M2.m63;
		MUse.m54 = m51 * M2.m14 + m52 * M2.m24 + m53 * M2.m34 +
			m54 * M2.m44 + m55 * M2.m54 + m56 * M2.m64;
		MUse.m55 = m51 * M2.m15 + m52 * M2.m25 + m53 * M2.m35 +
			m54 * M2.m45 + m55 * M2.m55 + m56 * M2.m65;
		MUse.m56 = m51 * M2.m16 + m52 * M2.m26 + m53 * M2.m36 +
			m54 * M2.m46 + m55 * M2.m56 + m56 * M2.m66;

		MUse.m61 = m61 * M2.m11 + m62 * M2.m21 + m63 * M2.m31 +
			m64 * M2.m41 + m65 * M2.m51 + m66 * M2.m61;
		MUse.m62 = m61 * M2.m12 + m62 * M2.m22 + m63 * M2.m32 +
			m64 * M2.m42 + m65 * M2.m52 + m66 * M2.m62;
		MUse.m63 = m61 * M2.m13 + m62 * M2.m23 + m63 * M2.m33 +
			m64 * M2.m43 + m65 * M2.m53 + m66 * M2.m63;
		MUse.m64 = m61 * M2.m14 + m62 * M2.m24 + m63 * M2.m34 +
			m64 * M2.m44 + m65 * M2.m54 + m66 * M2.m64;
		MUse.m65 = m61 * M2.m15 + m62 * M2.m25 + m63 * M2.m35 +
			m64 * M2.m45 + m65 * M2.m55 + m66 * M2.m65;
		MUse.m66 = m61 * M2.m16 + m62 * M2.m26 + m63 * M2.m36 +
			m64 * M2.m46 + m65 * M2.m56 + m66 * M2.m66;

		return MUse;
	}// End SMatrix operator *


	inline SMatrix& operator *=( const SMatrix& M1 )
	{
#if 1
		SMatrix MUse = (*this) * M1;
		*this = MUse;
		return *this;
#else
		SMatrix MUse;

		MUse.m11 = M1.m11 * m11 + M1.m12 * m21 + M1.m13 * m31 +
			M1.m14 * m41 + M1.m15 * m51 + M1.m16 * m61;
		MUse.m12 = M1.m11 * m12 + M1.m12 * m22 + M1.m13 * m32 +
			M1.m14 * m42 + M1.m15 * m52 + M1.m16 * m62;
		MUse.m13 = M1.m11 * m13 + M1.m12 * m23 + M1.m13 * m33 +
			M1.m14 * m43 + M1.m15 * m53 + M1.m16 * m63;
		MUse.m14 = M1.m11 * m14 + M1.m12 * m24 + M1.m13 * m34 +
			M1.m14 * m44 + M1.m15 * m54 + M1.m16 * m64;
		MUse.m15 = M1.m11 * m15 + M1.m12 * m25 + M1.m13 * m35 +
			M1.m14 * m45 + M1.m15 * m55 + M1.m16 * m65;
		MUse.m16 = M1.m11 * m16 + M1.m12 * m26 + M1.m13 * m36 +
			M1.m14 * m46 + M1.m15 * m56 + M1.m16 * m66;

		MUse.m21 = M1.m21 * m11 + M1.m22 * m21 + M1.m23 * m31 + 
			M1.m24 * m41 + M1.m25 * m51 + M1.m26 * m61;
		MUse.m22 = M1.m21 * m12 + M1.m22 * m22 + M1.m23 * m32 +
			M1.m24 * m42 + M1.m25 * m52 + M1.m26 * m62;
		MUse.m23 = M1.m21 * m13 + M1.m22 * m23 + M1.m23 * m33 +
			M1.m24 * m43 + M1.m25 * m53 + M1.m26 * m63;
		MUse.m24 = M1.m21 * m14 + M1.m22 * m24 + M1.m23 * m34 +
			M1.m24 * m44 + M1.m25 * m54 + M1.m26 * m64;
		MUse.m25 = M1.m21 * m15 + M1.m22 * m25 + M1.m23 * m35 +
			M1.m24 * m45 + M1.m25 * m55 + M1.m26 * m65;
		MUse.m26 = M1.m21 * m16 + M1.m22 * m26 + M1.m23 * m36 +
			M1.m24 * m46 + M1.m25 * m56 + M1.m26 * m66;

		MUse.m31 = M1.m31 * m11 + M1.m32 * m21 + M1.m33 * m31 +
			M1.m34 * m41 + M1.m35 * m51 + M1.m36 * m61;
		MUse.m32 = M1.m31 * m12 + M1.m32 * m22 + M1.m33 * m32 +
			M1.m34 * m42 + M1.m35 * m52 + M1.m36 * m62;
		MUse.m33 = M1.m31 * m13 + M1.m32 * m23 + M1.m33 * m33 +
			M1.m34 * m43 + M1.m35 * m53 + M1.m36 * m63;
		MUse.m34 = M1.m31 * m14 + M1.m32 * m24 + M1.m33 * m34 +
			M1.m34 * m44 + M1.m35 * m54 + M1.m36 * m64;
		MUse.m35 = M1.m31 * m15 + M1.m32 * m25 + M1.m33 * m35 +
			M1.m34 * m45 + M1.m35 * m55 + M1.m36 * m65;
		MUse.m36 = M1.m31 * m16 + M1.m32 * m26 + M1.m33 * m36 +
			M1.m34 * m46 + M1.m35 * m56 + M1.m36 * m66;

		MUse.m41 = M1.m41 * m11 + M1.m42 * m21 + M1.m43 * m31 +
			M1.m44 * m41 + M1.m45 * m51 + M1.m46 * m61;
		MUse.m42 = M1.m41 * m12 + M1.m42 * m22 + M1.m43 * m32 +
			M1.m44 * m42 + M1.m45 * m52 + M1.m46 * m62;
		MUse.m43 = M1.m41 * m13 + M1.m42 * m23 + M1.m43 * m33 +
			M1.m44 * m43 + M1.m45 * m53 + M1.m46 * m63;
		MUse.m44 = M1.m41 * m14 + M1.m42 * m24 + M1.m43 * m34 +
			M1.m44 * m44 + M1.m45 * m54 + M1.m46 * m64;
		MUse.m45 = M1.m41 * m15 + M1.m42 * m25 + M1.m43 * m35 +
			M1.m44 * m45 + M1.m45 * m55 + M1.m46 * m65;
		MUse.m46 = M1.m41 * m16 + M1.m42 * m26 + M1.m43 * m36 +
			M1.m44 * m46 + M1.m45 * m56 + M1.m46 * m66;

		MUse.m51 = M1.m51 * m11 + M1.m52 * m21 + M1.m53 * m31 +
			M1.m54 * m41 + M1.m55 * m51 + M1.m56 * m61;
		MUse.m52 = M1.m51 * m12 + M1.m52 * m22 + M1.m53 * m32 +
			M1.m54 * m42 + M1.m55 * m52 + M1.m56 * m62;
		MUse.m53 = M1.m51 * m13 + M1.m52 * m23 + M1.m53 * m33 +
			M1.m54 * m43 + M1.m55 * m53 + M1.m56 * m63;
		MUse.m54 = M1.m51 * m14 + M1.m52 * m24 + M1.m53 * m34 +
			M1.m54 * m44 + M1.m55 * m54 + M1.m56 * m64;
		MUse.m55 = M1.m51 * m15 + M1.m52 * m25 + M1.m53 * m35 +
			M1.m54 * m45 + M1.m55 * m55 + M1.m56 * m65;
		MUse.m56 = M1.m51 * m16 + M1.m52 * m26 + M1.m53 * m36 +
			M1.m54 * m46 + M1.m55 * m56 + M1.m56 * m66;

		MUse.m61 = M1.m61 * m11 + M1.m62 * m21 + M1.m63 * m31 +
			M1.m64 * m41 + M1.m65 * m51 + M1.m66 * m61;
		MUse.m62 = M1.m61 * m12 + M1.m62 * m22 + M1.m63 * m32 +
			M1.m64 * m42 + M1.m65 * m52 + M1.m66 * m62;
		MUse.m63 = M1.m61 * m13 + M1.m62 * m23 + M1.m63 * m33 +
			M1.m64 * m43 + M1.m65 * m53 + M1.m66 * m63;
		MUse.m64 = M1.m61 * m14 + M1.m62 * m24 + M1.m63 * m34 +
			M1.m64 * m44 + M1.m65 * m54 + M1.m66 * m64;
		MUse.m65 = M1.m61 * m15 + M1.m62 * m25 + M1.m63 * m35 +
			M1.m64 * m45 + M1.m65 * m55 + M1.m66 * m65;
		MUse.m66 = M1.m61 * m16 + M1.m62 * m26 + M1.m63 * m36 +
			M1.m64 * m46 + M1.m65 * m56 + M1.m66 * m66;

		*this = MUse;

		return *this;
#endif

	}

	
}/*const unitMatr*/;
inline SMatrix UnitMatrixFunc()
{
	SMatrix aMatrix;

	memset( &aMatrix, 0, sizeof(SMatrix) );

	aMatrix.m66 = aMatrix.m55 = aMatrix.m44 = aMatrix.m33 = aMatrix.m22 = aMatrix.m11 = 1;

	return aMatrix;
}
const SMatrix	g_cmUnitMartix = UnitMatrixFunc();



template<typename TypeInt> inline TypeInt RoundInteger( const TypeInt& a_tInitSize )
{

	if( !a_tInitSize )
	{
		return (TypeInt)0;
	}

	int i(0);
	TypeInt tRet(a_tInitSize);

	for( ; tRet; tRet = (a_tInitSize >> ++i) );


	tRet = ((TypeInt)1) << (i-1);

	if( tRet != a_tInitSize )
	{
		tRet <<= 1;
	}

	return tRet;
}



#endif /* #ifndef __structs_accl_h__ */
