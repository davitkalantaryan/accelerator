/*
 *	File      : accelerator_element_base.cpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */

#include "accelerator_element_base.hpp"

accelerator::element::Base::Base(double a_lfLength)
	:
	m_lfLength(a_lfLength)
{}

accelerator::element::Base::~Base()
{
}


double accelerator::element::Base::Length()const
{
	return m_lfLength;
}
