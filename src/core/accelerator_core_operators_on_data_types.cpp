//
// file:            accelerator_core_operators_on_data_types.cpp
// path:			src/core/accelerator_core_operators_on_data_types.cpp
// created on:		2023 Apr 03
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <accelerator/operators_on_data_types.h>


CPPUTILS_BEGIN_C

ACCELERATOR_EXPORT const STransferMatrix	g_ctmUniqTrMatrix = {
	1,0,0,0,0,0,
	0,1,0,0,0,0,
	0,0,1,0,0,0,
	0,0,0,1,0,0,
	0,0,0,0,1,0,
	0,0,0,0,0,1,
};


ACCELERATOR_EXPORT const struct STwiss	g_ctmInitialTwissMatrix = {
	1., 0., 1., 0., 0., // betaX, alfaX, gammaX, etaX, etaPhX
	1., 0., 1., 0., 0.  // betaY, alfaY, gammaY, etaY, etaPhY
};


CPPUTILS_END_C


template<typename BaseVector>
const double& CVectorBase<BaseVector>::operator[](size_t a_index)const
{
	const double* pclfDbl = (const double*)((const BaseVector*)this);
	return pclfDbl[a_index];
}


template<typename BaseVector>
double& CVectorBase<BaseVector>::operator[](size_t a_index)
{
	double* plfDbl = (double*)((BaseVector*)this);
	return plfDbl[a_index];
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template<typename BaseMatrix, typename BaseVector>
const CVectorBase<BaseVector>& CMatrixBase<BaseMatrix, BaseVector>::operator[](size_t a_row)const
{
	const BaseVector* pclfDbl = (const BaseVector*)((const BaseMatrix*)this);
	return (const CVectorBase<BaseVector>&)pclfDbl[a_row];
}


template<typename BaseMatrix, typename BaseVector>
CVectorBase<BaseVector>& CMatrixBase<BaseMatrix, BaseVector>::operator[](size_t a_row)
{
	BaseVector* pclfDbl = (BaseVector*)((BaseMatrix*)this);
	return (CVectorBase<BaseVector>&)pclfDbl[a_row];
}



/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


ACCELERATOR_EXPORT STransferMatrix operator *(const STransferMatrix& a_M1, const STransferMatrix& a_M2)
{
	STransferMatrix MUse;
	CMatrixBase<STransferMatrix, SCoordVector>& rMUse = (CMatrixBase<STransferMatrix, SCoordVector>&)MUse;
	const CMatrixBase<STransferMatrix, SCoordVector>& M1 = (const CMatrixBase<STransferMatrix, SCoordVector>&)a_M1;
	const CMatrixBase<STransferMatrix, SCoordVector>& M2 = (const CMatrixBase<STransferMatrix, SCoordVector>&)a_M2;
	size_t j, k;
	for (size_t i(0); i < 6; ++i){
		for (j = 0; j < 6; ++j){
			rMUse[i][j] = 0.;
			for (k = 0; k < 6; ++k) { 
				rMUse[i][j] += (M1[i][k] * M2[k][j]); 
			}
		} // for (j = 0; j < 6; ++j)
	} // for (int i(0); i < 6; ++i)

	return MUse;
}


ACCELERATOR_EXPORT STransferMatrix& operator *=(STransferMatrix& a_M1, const STransferMatrix& a_M2)
{
	a_M1 = a_M1 * a_M2;
	return a_M1;
}


ACCELERATOR_EXPORT SVector operator *(const STransferMatrix& a_M1, const SVector& a_V2)
{
	size_t j;
	SVector vectRet;
	CVectorBase<SVector>& refVectRet = (CVectorBase<SVector>&)vectRet;
	const CMatrixBase<STransferMatrix, SVector>& M1 = (const CMatrixBase<STransferMatrix, SVector>&)a_M1;
	const CVectorBase<SVector>& V2 = (const CVectorBase<SVector>&)a_V2;

	for (size_t i(0); i < 6; ++i) {
		refVectRet[i] = 0.;
		for (j = 0; j < 6; ++j) {
			refVectRet[i] += M1[i][j] * V2[j];
		}
	}

	return vectRet;
}
