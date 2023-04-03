/*
 *	File      : operators_on_data_types.h
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef ACCELERATOR_INCLUDE_ACCELERATOR_OPERATORS_ON_DATA_TYPES_H
#define ACCELERATOR_INCLUDE_ACCELERATOR_OPERATORS_ON_DATA_TYPES_H

#include <accelerator/export_symbols.h>
#include <accelerator/data_types.h>
#include <stddef.h>


CPPUTILS_BEGIN_C

extern ACCELERATOR_EXPORT const STransferMatrix	g_ctmUniqTrMatrix;

CPPUTILS_END_C

template<typename BaseVector>
class ACCELERATOR_EXPORT CVectorBase : public BaseVector
{
public:
	const double& operator[](size_t a_index)const;
	double& operator[](size_t a_index);
};


template<typename BaseMatrix, typename BaseVector>
class ACCELERATOR_EXPORT CMatrixBase : public BaseMatrix
{
public:
	const CVectorBase<BaseVector>& operator[](size_t a_row)const;
	CVectorBase<BaseVector>& operator[](size_t a_row);
};


ACCELERATOR_EXPORT STransferMatrix operator *(const STransferMatrix& a_M1, const STransferMatrix& a_M2);
ACCELERATOR_EXPORT STransferMatrix& operator *=(STransferMatrix& a_M1, const STransferMatrix& a_M2);


#endif // #ifndef ACCELERATOR_INCLUDE_ACCELERATOR_DATA_TYPES_H
