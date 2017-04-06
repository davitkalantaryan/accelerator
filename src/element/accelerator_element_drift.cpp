/*
 *	File      : accelerator_element_drift.cpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */

#include "accelerator_element_drift.hpp"

accelerator::element::Drift::Drift(double a_lfLen)
	:
	Linear(m_lfLength,
	{
	1,a_lfLen,  0,0,       0,0,
	0,   1,     0,0,       0,0,
	0,   0,     1,a_lfLen, 0,0,
	0,   0,     0,   1,    0,0,
	1,a_lfLen,  0,   0,    1,0,
	1,a_lfLen,  0,   0,    0,1})
{
}

accelerator::element::Drift::~Drift()
{
}


accelerator::element::Base* accelerator::element::Drift::Clone()const
{
	return new Drift(*this);
}
