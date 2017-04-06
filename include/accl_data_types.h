/*
 *	File      : accl_data_types.h
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef __accl_data_types_h__
#define __accl_data_types_h__

#include <stddef.h>		// For type size_t
#include <memory.h>		// For func. memset

#ifndef int64_tt
#ifdef WIN32
#define int64_tt __int64
#else
#define int64_tt long long int
#endif
#endif

#if defined(__cplusplus) & (__cplusplus >= 199711L)
#define _OVERRIDE_	override
#else
#define _OVERRIDE_
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SCoordVector
{
	double x;
	double px;
	double y;
	double py;
	double z;
	double delta;
}SCoordVector;


typedef struct STwiss
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

}STwiss;


typedef struct STransferMatrix
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
}STransferMatrix;


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus


static const STransferMatrix	s_ctmUniqTrMatrix = {
	1,0,0,0,0,0,
	0,1,0,0,0,0,
	0,0,1,0,0,0,
	0,0,0,1,0,0,
	0,0,0,0,1,0,
	0,0,0,0,0,1,
};

template<typename BaseVector>
class CVectorBase : public BaseVector
{
public:
	const double& operator[](const size_t& unIndex)const{
		const double* pclfDbl = (const double*)((const BaseVector*)this);
		return pclfDbl[unIndex];
	}
	double& operator[](const size_t& unIndex){
		double* plfDbl = (double*)((BaseVector*)this);
		return plfDbl[unIndex];
	}
};


template<typename BaseMatrix, typename BaseVector>
class CMatrixBase : public BaseMatrix
{
public:
	const CVectorBase<BaseVector>& operator[](const size_t& a_row)const{
		const BaseVector* pclfDbl = (const BaseVector*)((const BaseMatrix*)this);
		return (const CVectorBase<BaseVector>&)pclfDbl[a_row];
	}
	CVectorBase<BaseVector>& operator[](const size_t& a_row){
		BaseVector* pclfDbl = (BaseVector*)((BaseMatrix*)this);
		return (CVectorBase<BaseVector>&)pclfDbl[a_row];
	}
};


inline STransferMatrix operator *(const STransferMatrix& a_M1,const STransferMatrix& a_M2)
{
	STransferMatrix MUse;

#if 1
	CMatrixBase<STransferMatrix, SCoordVector>& rMUse= (CMatrixBase<STransferMatrix, SCoordVector>&)MUse;
	const CMatrixBase<STransferMatrix, SCoordVector>& M1 = 
		(const CMatrixBase<STransferMatrix, SCoordVector>&)a_M1;
	const CMatrixBase<STransferMatrix, SCoordVector>& M2 = 
		(const CMatrixBase<STransferMatrix, SCoordVector>&)a_M2;
	int j,k;
	for (int i(0); i < 6; ++i)
	{
		for (j = 0; j < 6; ++j)
		{
			rMUse[i][j] = 0.;
			for (k = 0; k < 6; ++k){rMUse[i][j] += (M1[i][k] * M2[k][j]);}
		} // for (j = 0; j < 6; ++j)
	} // for (int i(0); i < 6; ++i)

#else // #if 1/0
	const STransferMatrix& M1 = a_M1;
	const STransferMatrix& M2 = a_M2;
	MUse.m11 = M1.m11 * M2.m11 + M1.m12 * M2.m21 + M1.m13 * M2.m31 +
		M1.m14 * M2.m41 + M1.m15 * M2.m51 + M1.m16 * M2.m61;
	MUse.m12 = M1.m11 * M2.m12 + M1.m12 * M2.m22 + M1.m13 * M2.m32 +
		M1.m14 * M2.m42 + M1.m15 * M2.m52 + M1.m16 * M2.m62;
	MUse.m13 = M1.m11 * M2.m13 + M1.m12 * M2.m23 + M1.m13 * M2.m33 +
		M1.m14 * M2.m43 + M1.m15 * M2.m53 + M1.m16 * M2.m63;
	MUse.m14 = M1.m11 * M2.m14 + M1.m12 * M2.m24 + M1.m13 * M2.m34 +
		M1.m14 * M2.m44 + M1.m15 * M2.m54 + M1.m16 * M2.m64;
	MUse.m15 = M1.m11 * M2.m15 + M1.m12 * M2.m25 + M1.m13 * M2.m35 +
		M1.m14 * M2.m45 + M1.m15 * M2.m55 + M1.m16 * M2.m65;
	MUse.m16 = M1.m11 * M2.m16 + M1.m12 * M2.m26 + M1.m13 * M2.m36 +
		M1.m14 * M2.m46 + M1.m15 * M2.m56 + M1.m16 * M2.m66;

	MUse.m21 = M1.m21 * M2.m11 + M1.m22 * M2.m21 + M1.m23 * M2.m31 +
		M1.m24 * M2.m41 + M1.m25 * M2.m51 + M1.m26 * M2.m61;
	MUse.m22 = M1.m21 * M2.m12 + M1.m22 * M2.m22 + M1.m23 * M2.m32 +
		M1.m24 * M2.m42 + M1.m25 * M2.m52 + M1.m26 * M2.m62;
	MUse.m23 = M1.m21 * M2.m13 + M1.m22 * M2.m23 + M1.m23 * M2.m33 +
		M1.m24 * M2.m43 + M1.m25 * M2.m53 + M1.m26 * M2.m63;
	MUse.m24 = M1.m21 * M2.m14 + M1.m22 * M2.m24 + M1.m23 * M2.m34 +
		M1.m24 * M2.m44 + M1.m25 * M2.m54 + M1.m26 * M2.m64;
	MUse.m25 = M1.m21 * M2.m15 + M1.m22 * M2.m25 + M1.m23 * M2.m35 +
		M1.m24 * M2.m45 + M1.m25 * M2.m55 + M1.m26 * M2.m65;
	MUse.m26 = M1.m21 * M2.m16 + M1.m22 * M2.m26 + M1.m23 * M2.m36 +
		M1.m24 * M2.m46 + M1.m25 * M2.m56 + M1.m26 * M2.m66;

	MUse.m31 = M1.m31 * M2.m11 + M1.m32 * M2.m21 + M1.m33 * M2.m31 +
		M1.m34 * M2.m41 + M1.m35 * M2.m51 + M1.m36 * M2.m61;
	MUse.m32 = M1.m31 * M2.m12 + M1.m32 * M2.m22 + M1.m33 * M2.m32 +
		M1.m34 * M2.m42 + M1.m35 * M2.m52 + M1.m36 * M2.m62;
	MUse.m33 = M1.m31 * M2.m13 + M1.m32 * M2.m23 + M1.m33 * M2.m33 +
		M1.m34 * M2.m43 + M1.m35 * M2.m53 + M1.m36 * M2.m63;
	MUse.m34 = M1.m31 * M2.m14 + M1.m32 * M2.m24 + M1.m33 * M2.m34 +
		M1.m34 * M2.m44 + M1.m35 * M2.m54 + M1.m36 * M2.m64;
	MUse.m35 = M1.m31 * M2.m15 + M1.m32 * M2.m25 + M1.m33 * M2.m35 +
		M1.m34 * M2.m45 + M1.m35 * M2.m55 + M1.m36 * M2.m65;
	MUse.m36 = M1.m31 * M2.m16 + M1.m32 * M2.m26 + M1.m33 * M2.m36 +
		M1.m34 * M2.m46 + M1.m35 * M2.m56 + M1.m36 * M2.m66;

	MUse.m41 = M1.m41 * M2.m11 + M1.m42 * M2.m21 + M1.m43 * M2.m31 +
		M1.m44 * M2.m41 + M1.m45 * M2.m51 + M1.m46 * M2.m61;
	MUse.m42 = M1.m41 * M2.m12 + M1.m42 * M2.m22 + M1.m43 * M2.m32 +
		M1.m44 * M2.m42 + M1.m45 * M2.m52 + M1.m46 * M2.m62;
	MUse.m43 = M1.m41 * M2.m13 + M1.m42 * M2.m23 + M1.m43 * M2.m33 +
		M1.m44 * M2.m43 + M1.m45 * M2.m53 + M1.m46 * M2.m63;
	MUse.m44 = M1.m41 * M2.m14 + M1.m42 * M2.m24 + M1.m43 * M2.m34 +
		M1.m44 * M2.m44 + M1.m45 * M2.m54 + M1.m46 * M2.m64;
	MUse.m45 = M1.m41 * M2.m15 + M1.m42 * M2.m25 + M1.m43 * M2.m35 +
		M1.m44 * M2.m45 + M1.m45 * M2.m55 + M1.m46 * M2.m65;
	MUse.m46 = M1.m41 * M2.m16 + M1.m42 * M2.m26 + M1.m43 * M2.m36 +
		M1.m44 * M2.m46 + M1.m45 * M2.m56 + M1.m46 * M2.m66;

	MUse.m51 = M1.m51 * M2.m11 + M1.m52 * M2.m21 + M1.m53 * M2.m31 +
		M1.m54 * M2.m41 + M1.m55 * M2.m51 + M1.m56 * M2.m61;
	MUse.m52 = M1.m51 * M2.m12 + M1.m52 * M2.m22 + M1.m53 * M2.m32 +
		M1.m54 * M2.m42 + M1.m55 * M2.m52 + M1.m56 * M2.m62;
	MUse.m53 = M1.m51 * M2.m13 + M1.m52 * M2.m23 + M1.m53 * M2.m33 +
		M1.m54 * M2.m43 + M1.m55 * M2.m53 + M1.m56 * M2.m63;
	MUse.m54 = M1.m51 * M2.m14 + M1.m52 * M2.m24 + M1.m53 * M2.m34 +
		M1.m54 * M2.m44 + M1.m55 * M2.m54 + M1.m56 * M2.m64;
	MUse.m55 = M1.m51 * M2.m15 + M1.m52 * M2.m25 + M1.m53 * M2.m35 +
		M1.m54 * M2.m45 + M1.m55 * M2.m55 + M1.m56 * M2.m65;
	MUse.m56 = M1.m51 * M2.m16 + M1.m52 * M2.m26 + M1.m53 * M2.m36 +
		M1.m54 * M2.m46 + M1.m55 * M2.m56 + M1.m56 * M2.m66;

	MUse.m61 = M1.m61 * M2.m11 + M1.m62 * M2.m21 + M1.m63 * M2.m31 +
		M1.m64 * M2.m41 + M1.m65 * M2.m51 + M1.m66 * M2.m61;
	MUse.m62 = M1.m61 * M2.m12 + M1.m62 * M2.m22 + M1.m63 * M2.m32 +
		M1.m64 * M2.m42 + M1.m65 * M2.m52 + M1.m66 * M2.m62;
	MUse.m63 = M1.m61 * M2.m13 + M1.m62 * M2.m23 + M1.m63 * M2.m33 +
		M1.m64 * M2.m43 + M1.m65 * M2.m53 + M1.m66 * M2.m63;
	MUse.m64 = M1.m61 * M2.m14 + M1.m62 * M2.m24 + M1.m63 * M2.m34 +
		M1.m64 * M2.m44 + M1.m65 * M2.m54 + M1.m66 * M2.m64;
	MUse.m65 = M1.m61 * M2.m15 + M1.m62 * M2.m25 + M1.m63 * M2.m35 +
		M1.m64 * M2.m45 + M1.m65 * M2.m55 + M1.m66 * M2.m65;
	MUse.m66 = M1.m61 * M2.m16 + M1.m62 * M2.m26 + M1.m63 * M2.m36 +
		M1.m64 * M2.m46 + M1.m65 * M2.m56 + M1.m66 * M2.m66;
#endif // #if 1/0

	return MUse;
}// End SMatrix operator *

#endif // #ifdef __cplusplus

inline STransferMatrix& operator *=(STransferMatrix& a_M1, const STransferMatrix& a_M2)
{
	a_M1 = a_M1*a_M2;
	return a_M1;
}


#endif // #ifndef __accl_data_types_h__
