/*
 *	File      : accelerator_element_base.hpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef __accelerator_element_base_hpp__
#define __accelerator_element_base_hpp__

#include <accl_data_types.h>

namespace accelerator{ namespace element{

class Base
{
public:
	Base(double length);
	virtual ~Base();
	virtual Base* Clone()const=0;  // This will be used for operator=
	virtual const STransferMatrix& TransferMatrix()const = 0;
	virtual bool Track(const SCoordVector& in, SCoordVector& out)const =0;  // False means particle lost
	virtual double Length()const;

protected:
	double m_lfLength;
};

}}


#endif  // #ifndef __accelerator_element_base_hpp__
