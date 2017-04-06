/*
 *	File      : accelerator_element_linear.hpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef __accelerator_element_linear_hpp__
#define __accelerator_element_linear_hpp__

#include "accelerator_element_base.hpp"

namespace accelerator{ namespace element{

class Linear : public Base
{
public:
	Linear(double length,const STransferMatrix& transMatrix);
	virtual ~Linear();

protected:
	virtual const STransferMatrix& TransferMatrix()const _OVERRIDE_;
	virtual bool Track(const SCoordVector& in, SCoordVector& out)const _OVERRIDE_;

protected:
	STransferMatrix	m_transMatrix;
};

}}

#endif  // #ifndef __accelerator_element_linear_hpp__
