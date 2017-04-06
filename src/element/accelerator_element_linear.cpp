/*
 *	File      : accelerator_element_linear.cpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */

#include "accelerator_element_linear.hpp"

accelerator::element::Linear::Linear(double a_lfLength,const STransferMatrix& a_transMatrix)
	:
	Base(a_lfLength),
	m_transMatrix(a_transMatrix)
{
}

accelerator::element::Linear::~Linear()
{
}

const STransferMatrix& accelerator::element::Linear::TransferMatrix()const
{
	return m_transMatrix;
}

bool accelerator::element::Linear::Track(const SCoordVector& a_in, SCoordVector& a_out)const
{
	return true;
}
