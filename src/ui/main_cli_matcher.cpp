/*
 *	File      : main_cli_matcher.cpp
 *
 *	Created on: 04 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */

#include "../element/accelerator_element_drift.hpp"

int main()
{
	accelerator::element::Drift aDr(1);

	STransferMatrix M1 = {
		1,0,0,0,0,0,
		1,2,0,0,0,0,
		1,0,3,3,0,0 ,
		1,0,0,4,4,0 ,
		1,0,0,0,5,0 ,
		1,0,0,0,0,6 };

	STransferMatrix M2 = M1*s_ctmUniqTrMatrix;

	return 0;
}
