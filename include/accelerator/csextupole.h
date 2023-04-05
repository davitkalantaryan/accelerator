#ifndef __csextupole_h__
#define __csextupole_h__



#include "cdrift.h"

namespace DAVIT_CLASSES
{
	class CSextupole : public CDrift
	{
	public:
		enum _PARAMS{ GRADIENT = _PARAMS_ACCELEM_LAST, _PARAMS_SEXTUPOLE_LAST };

		CSextupole( const double& a_lfL = 0., const double& a_lfSG = 0.001);

		ElementBase*	Clone()const;

		void			SetFields( const int& Which, const double& Param, const int& Index );

		const double&	GetFields( const int& Which, const int& Index )const;

		void			WriteToFile1( FILE* a_File )const;

		void			ReadFromFile1( FILE* a_File, void* Group, void* Founded );

	private:
		double			m_lfSG;
	};
};




#endif/* #ifndef __csextupole_h__ */
