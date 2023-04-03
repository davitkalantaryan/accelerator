/*
 *	File      : data_types.h
 *
 *	Created on: 06 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef ACCELERATOR_INCLUDE_ACCELERATOR_DATA_TYPES_H
#define ACCELERATOR_INCLUDE_ACCELERATOR_DATA_TYPES_H

#include <accelerator/export_symbols.h>


CPPUTILS_BEGIN_C

typedef struct SCoordVector{
	double x;
	double px;
	double y;
	double py;
	double z;
	double delta;
}SCoordVector;


typedef struct STwiss{
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


typedef struct STransferMatrix{
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


CPPUTILS_END_C



#endif // #ifndef ACCELERATOR_INCLUDE_ACCELERATOR_DATA_TYPES_H
