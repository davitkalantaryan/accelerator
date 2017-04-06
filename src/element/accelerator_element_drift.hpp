/*
 *	File      : accelerator_element_drift.hpp
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */

#include "accelerator_element_linear.hpp"

namespace accelerator{ namespace element{ 

class Drift : public Linear
{
public:
	Drift(double len);
	virtual ~Drift();

protected:
	virtual Base* Clone()const _OVERRIDE_;
	
};

}}
