#ifndef __elemsseq_h__
#define __elemsseq_h__

#include "elementbase.h"
#include "vectoroftype2.h"

namespace DAVIT_CLASSES
{

class ElemsSeq : public ElementBase
{
public:
	ElemsSeq(const size_t& unDesiredNumber=3);

	ElemsSeq(const ElemsSeq& cM);


	ElementBase*	Clone()const;

	ElemsSeq&		operator=(const ElemsSeq& aM);

	void			EQUATING( ElementBase* pSource );

	void			AddElement(ElementBase* pElement,int IfCreate);

	void			AddElement(const ElementBase& aElement);

	void			RemoveElement(const int& a_nIndex);

	void			RemoveFamily(const int& a_nIndex);

	void			RemoveFamily(const char* cpcFamName);

	//const double&	GetFields( const int& /*nWhich*/ )const{return m_lfL;}

	void			SetFieldsPassive( const int& a_nWhich, const double& a_lfParam, const int& a_nIndex );

	void			SetFields( const int& a_nWhich, const double& a_lfParam, const int& a_nIndex );

	void			GetTwissParam(	double& lfRet, const int& nWhere1, const int& whichParam,
									const STwiss& aTwis0, STwiss*const& pTwisF)const;

	int				GetIndex(const char* cpcFamName)const;

	void			ObtainMatrixTrans();

	void			ObtainMatrixTwiss( );

	void			WriteToFile1( FILE* a_File )const;

	void			ReadFromFile1( FILE* aFile, void* pReserved, void* pFounded );

	void			WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const;

	void			LoadFromOptimString( const char*const& a_pcBuff, int a_nRead );

	const SMatrix&	GetMatrixTrans()const;

	const SMatrix&	GetMatrixTwiss()const;
	
	SVector			Track( const SVector& coord0, bool*const& /*survive*/, int*const& /*losseIndex*/ );

	const int&		NumberOfDevices()const;

	const int&		NumberOfFamilies()const;

	ElementBase*	operator[](const int& a_nIndex);

	ElementBase*	operator()(const int& a_nIndex);

	SMatrix			GetMatrixTrans(	const double& a_lfS )const;

private:
	void			ObtainAll();


private:
	VectorOfType2<ElementBase*>		m_Families;
	VectorOfType2<int>				m_Elements;

	SMatrix							m_MatrixTrans;
	SMatrix							m_MatrixTwiss;
};



ElemsSeq operator+( const ElementBase& aE1, const ElementBase& aE2 );
ElemsSeq operator+( const ElemsSeq& eS, const ElementBase& aE );
ElemsSeq operator *( const int& a_nN, const ElemsSeq& eS );

ElemsSeq operator&( const ElementBase& aE1, const ElementBase& aE2 );
ElemsSeq operator&( const ElemsSeq& eS, const ElementBase& aE2 );

};// namespace DAVIT_CLASSES



#endif/* #ifndef __elemsseq_h__ */
