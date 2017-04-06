#ifndef __commondialog_h__
#define __commondialog_h__


#include "elementbase.h"
#include "matcher.h"
#include "vectoroftype2.h"

using namespace DAVIT_CLASSES;

class CommonDialog
{
public:
	CommonDialog();

	virtual ~CommonDialog();

	virtual void	Func1( int nIndex )=0;

	virtual void	FuncOnOk( ) = 0;

	virtual void	FuncOnCancel() = 0;

	virtual void	Delete() = 0;

	virtual void	NewElem() = 0;

	virtual void	AddElements() = 0;

	void			NewFile();

	void			OpenFile( const char* a_FileName );

	void			SaveInFile( const char* a_FileName )const;

protected:
	void Empty();

protected:
	static int							m_nStNumber;
	
	bool								m_bIsCreating;
	ElementBase*						m_pActiveDevice;
	VectorOfType2<ElementBase*>			m_Devices;
	VectorOfType2<SMatchFields*>		m_MatcherFields;
	//Matcher								m_Matcher;
	int									m_nIndex;
};


#endif //#ifndef __commondialog_h__
