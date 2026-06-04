#include "stdafx.h"
#include <accelerator/elemsseq.h>
#include <accelerator/clinear.h>
#include <accelerator/elementcreator.h>
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <cinternal/undisable_compiler_warnings.h>


namespace DAVIT_CLASSES {



inline void ElemsSeq::CopyFromPart(const ElemsSeq& a_cM)
{
    m_Elements = a_cM.m_Elements;
    m_MatrixesTrans = a_cM.m_MatrixesTrans;
    m_MatrixesTwiss = a_cM.m_MatrixesTwiss;
    m_MatrixTrans2 = a_cM.m_MatrixTrans2;
    m_MatrixTwiss2 = a_cM.m_MatrixTwiss2;    

    ElementBase* pElementToAdd;

    typedef const ElementBase* ConstElementBasePtr;
    typedef ElementBase* ElementBasePtr;
    const size_t unFamsSize(a_cM.m_Families.size());
    const ConstElementBasePtr* const pInpFamsPtrArray = a_cM.m_Families.data();
    m_Families.resize(unFamsSize);
    ElementBasePtr* const pOutFamsPtrArray = m_Families.data();

    for (size_t i(0); i < unFamsSize; ++i){
        if (pInpFamsPtrArray[i]->GetFlag(CREATED_INSIDE))
        {
            pElementToAdd = pInpFamsPtrArray[i]->Clone();
        }
        else
        {
            pElementToAdd = const_cast<ElementBase*>(pInpFamsPtrArray[i]);
        }

        pOutFamsPtrArray[i] = pElementToAdd;
    }  //  for (size_t i(0); i < unFamsSize; ++i){
}


inline void ElemsSeq::MoveFromPart(ElemsSeq* a_mM_p) noexcept
{
    m_Elements = ::std::move(a_mM_p->m_Elements);
    m_MatrixesTrans = ::std::move(a_mM_p->m_MatrixesTrans);
    m_MatrixesTwiss = ::std::move(a_mM_p->m_MatrixesTwiss);
    m_MatrixTrans2 = a_mM_p->m_MatrixTrans2;
    m_MatrixTwiss2 = a_mM_p->m_MatrixTwiss2;
    m_Families = ::std::move(a_mM_p->m_Families);
}


ElemsSeq::~ElemsSeq()
{
    typedef ElementBase* ElementBasePtr;
    const size_t unFamsSize(m_Families.size());
    const ElementBasePtr* const pFamsPtrArray = m_Families.data();

    for (size_t i(0); i < unFamsSize; ++i) {
        if (pFamsPtrArray[i]->GetFlag(CREATED_INSIDE))
        {
            delete pFamsPtrArray[i];
        }
    }  //  for (size_t i(0); i < unFamsSize; ++i){
}


ElemsSeq::ElemsSeq()
	:	ElementBase(ElementBase::SEQUENCE,0.0)
{
	m_MatrixTrans2 = g_ctmUniqTrMatrix;
	m_MatrixTwiss2 = g_ctmUniqTrMatrix;
}



ElemsSeq::ElemsSeq(const ElemsSeq& cM)
	:	
    ElementBase(cM)
{
    CopyFromPart(cM);
}


ElemsSeq::ElemsSeq(ElemsSeq&& a_mM) noexcept
    :
    ElementBase(std::move(a_mM))
{
    MoveFromPart(&a_mM);
}


ElemsSeq& ElemsSeq::operator=(const ElemsSeq& cM)
{
    ElementBase::operator=(cM);
    CopyFromPart(cM);
	return *this;
}


ElemsSeq& ElemsSeq::operator=(ElemsSeq&& a_mM)
{
    ElementBase::operator=(std::move(a_mM));
    MoveFromPart(&a_mM);
    return *this;
}



ElementBase* ElemsSeq::Clone()const
{
	return new ElemsSeq(*this);
}



void ElemsSeq::EQUATING( ElementBase* a_pSource )
{
	ElemsSeq& cM = *((ElemsSeq*)a_pSource);

	size_t unSize(cM.m_Families.size());

	for( size_t i(0); i < unSize; ++i )
	{
		m_Families[i]->EQUATING( cM.m_Families[i] );
	}
}



void ElemsSeq::AddElement(const ElementBase& aElement)
{
	ElementBase* pElement = aElement.Clone();
    pElement->SetFlag(CREATED_INSIDE, 1);
	ElemsSeq::AddElement(pElement,0);
}



void ElemsSeq::AddElement(ElementBase* a_pElement,int a_nIfCreate)
{
	m_lfL += a_pElement->GetLength();
	m_MatrixTrans2 = a_pElement->GetMatrixTrans() * m_MatrixTrans2;
    m_MatrixesTrans.push_back(m_MatrixTrans2);
    m_MatrixTwiss2 = a_pElement->GetMatrixTwiss() * m_MatrixTwiss2;
    m_MatrixesTwiss.push_back(m_MatrixTwiss2);

	///////////////////////////////////////////////////////////////
    size_t i;
    const size_t unSize(m_Families.size());

	for( i = 0; i < unSize; ++i ){
		if(m_Families[i]->IsSameFamily(a_pElement->GetFamName()))
		{
			m_Elements.push_back((int)i);
            if (a_pElement->GetFlag(CREATED_INSIDE)) {
                delete a_pElement;
            }
            return;
		}
	}  //  for( i = 0; i < unSize; ++i ){

	ElementBase* pElementToAdd;

    if (a_nIfCreate) {
        pElementToAdd = a_pElement->Clone();
        pElementToAdd->SetFlag(CREATED_INSIDE, a_nIfCreate);
    }
	else
		pElementToAdd = a_pElement;

	m_Families.push_back(pElementToAdd);
	m_Elements.push_back((int)unSize);
}



void ElemsSeq::RemoveElement(const int& a_nIndex)
{
	int nSize((int)m_Elements.size());
	
	if(a_nIndex >= nSize)
		return;

    bool bNotFound(true);
    int i;
	const int nFamily = m_Elements[a_nIndex];

	m_lfL -= m_Families[nFamily]->GetLength();
    m_MatrixTrans2 = (a_nIndex > 0) ? m_MatrixesTrans[a_nIndex - 1] : g_ctmUniqTrMatrix;
    m_MatrixTwiss2 = (a_nIndex > 0) ? m_MatrixesTwiss[a_nIndex - 1] : g_ctmUniqTrMatrix;
	m_Elements.erase(m_Elements.begin() + a_nIndex );
    m_MatrixesTrans.erase(m_MatrixesTrans.begin() + a_nIndex);
    m_MatrixesTwiss.erase(m_MatrixesTwiss.begin() + a_nIndex);
    SMatrix* const pMatrTransPtr = const_cast<SMatrix*>(m_MatrixesTrans.data());
    SMatrix* const pMatrTwissPtr = const_cast<SMatrix*>(m_MatrixesTwiss.data());
	--nSize;

    for (i = a_nIndex; i < nSize; ++i) {
        m_MatrixTrans2 = m_Families[m_Elements[i]]->GetMatrixTrans() * m_MatrixTrans2;
        m_MatrixTwiss2 = m_Families[m_Elements[i]]->GetMatrixTwiss() * m_MatrixTwiss2;
        pMatrTransPtr[i] = m_MatrixTrans2;
        pMatrTwissPtr[i] = m_MatrixTwiss2;
        if (bNotFound) {
            if (m_Elements[i] == nFamily) {
                bNotFound = false;
            }  //  if (m_Elements[i] == nFamily) {
        }  //  if (bNotFound) {
    }  //  for (i = a_nIndex; i < nSize; ++i) {

	if(bNotFound){
        for (i = 0; i < a_nIndex; ++i){
            if (m_Elements[i] == nFamily){
                return;
            }  //  if (m_Elements[i] == nFamily){
        }  //  for (i = 0; i < a_nIndex; ++i){
	}  //  if(bNotFound){

    ElementBase* const pFamilyToRemove = m_Families[nFamily];
    if(pFamilyToRemove->GetFlag(CREATED_INSIDE)) {
        delete pFamilyToRemove;
    }
    m_Families.erase(m_Families.begin() + nFamily);
}



void ElemsSeq::RemoveFamily(const char* cpcFamName)
{
	const int nFamily = ElemsSeq::GetIndex(cpcFamName);
	if( nFamily < 0 )return;
	ElemsSeq::RemoveFamily(nFamily);
}



void ElemsSeq::RemoveFamily(const int& a_nIndex)
{
	int nSizeFam((int)m_Families.size());
	
	if(a_nIndex >= nSizeFam)
		return;

	ElementBase* const pElemet = m_Families[a_nIndex];
	const double lfLength = pElemet->GetLength();

	m_Families.erase(m_Families.begin()+ a_nIndex);
    int nSize((int)m_Elements.size());
    int i, nFirstIndex= nSize-1;

	for( i=0; i < nSize; )
	{

		if( m_Elements[i] < a_nIndex )
		{
			++i;
		}
		else if( m_Elements[i] > a_nIndex )
		{
			--m_Elements[i];
			++i;
		}
		else /*( m_Elements[i] == a_nIndex )*/
		{
            if (i < nFirstIndex) {
                nFirstIndex = i;
            }
			m_Elements.erase(m_Elements.begin()+ i);
			m_lfL -= lfLength;
			--nSize;
		}
	}

    m_MatrixTrans2 = (nFirstIndex > 0) ? m_MatrixesTrans[nFirstIndex - 1] : g_ctmUniqTrMatrix;
    m_MatrixTwiss2 = (nFirstIndex > 0) ? m_MatrixesTwiss[nFirstIndex - 1] : g_ctmUniqTrMatrix;
    m_MatrixesTrans.resize(static_cast<size_t>(nSize));
    m_MatrixesTwiss.resize(static_cast<size_t>(nSize));
    SMatrix* const pMatrTransPtr = const_cast<SMatrix*>(m_MatrixesTrans.data());
    SMatrix* const pMatrTwissPtr = const_cast<SMatrix*>(m_MatrixesTwiss.data());

    for (i = nFirstIndex; i < nSize; ++i) {
        m_MatrixTrans2 = m_Families[m_Elements[i]]->GetMatrixTrans() * m_MatrixTrans2;
        m_MatrixTwiss2 = m_Families[m_Elements[i]]->GetMatrixTwiss() * m_MatrixTwiss2;
        pMatrTransPtr[i] = m_MatrixTrans2;
        pMatrTwissPtr[i] = m_MatrixTwiss2;
    }  //  for (i = nFirstIndex; i < nSize; ++i) {

    if(pElemet->GetFlag(CREATED_INSIDE)) {
        delete pElemet;
    }
}



void ElemsSeq::SetFieldsPassive( const int& a_nWhich, const double& a_lfParam, const int& a_nIndex )
{
	m_Families[a_nIndex]->SetFields(a_nWhich, a_lfParam, a_nIndex);
}



void ElemsSeq::SetFields( const int& a_nWhich, const double& a_lfParam, const int& a_nIndex )
{
	m_Families[a_nIndex]->SetFields(a_nWhich, a_lfParam, a_nIndex);
	ObtainMatrixTrans();
	ObtainMatrixTwiss();
}


/*
#define		NO_INDEX			-1
#define		END_OF_LATTICE		-2
*/



void ElemsSeq::GetTwissParam(double& lfRet, const int& nWhere1, const int& whichParam,
							 const STwiss& aTwis0, STwiss*const& pTwisF)const
{

	CLinear aLine;
    const int cnElemsSize = (int)m_Elements.size();
    if (cnElemsSize < 1) {
        return;
    }

	const int nWhere = ((nWhere1 >= cnElemsSize) || (nWhere1<0)) ? (cnElemsSize-1) : nWhere1;

	SMatrix aMatrixTrans(m_MatrixesTrans[static_cast<size_t>(nWhere)]);
	SMatrix aMatrixTwiss(m_MatrixesTwiss[static_cast<size_t>(nWhere)]);
	
	aLine.SetMatrixes( aMatrixTrans, aMatrixTwiss );
	aLine.GetTwissParam(lfRet,END_OF_LATTICE,whichParam,aTwis0,pTwisF);

}



int ElemsSeq::GetIndex(const char* cpcFamName)const
{
	int nIndex(NO_INDEX);

	for(int i(0); i < m_Families.size(); ++i)
	{
		if( m_Families[i]->IsSameFamily(cpcFamName) )
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}



void ElemsSeq::ObtainMatrixTrans()
{
}



void ElemsSeq::ObtainMatrixTwiss()
{
}



void ElemsSeq::ObtainAll()
{
}



void ElemsSeq::WriteToFile1( FILE* a_File )const
{

	ElementBase::WriteToFile1( a_File );

	int i, nKind, nSize = (int)m_Families.size();

	fwrite( &nSize, sizeof(nSize), 1, a_File );

	for( i = 0; i < nSize; ++i )
	{
		//ElementCreator::StringToFile( a_File, m_Families[i]->GetFamName() );
		fwrite( &m_ucFlags2, sizeof(m_ucFlags2), 1, a_File );

		if( m_Families[i]->GetFlag(CREATED_INSIDE) )
		{
			m_Families[i]->WriteToFile1(a_File);
		}
		else
		{
			ElementCreator::StringToFile( a_File, m_Families[i]->GetFamName() );
			nKind = m_Families[i]->GetKind();
			fwrite( &nKind, sizeof(nKind), 1, a_File );
		}
	}


	nSize = (int)m_Elements.size();

	fwrite( &nSize, sizeof(nSize), 1, a_File );

	for( i = 0; i < nSize; ++i )
	{

		fwrite( &m_Elements[i], sizeof(m_Elements[i]), 1, a_File );
	}
	
}



void ElemsSeq::ReadFromFile1( FILE* a_File, void* a_pDevices, void* a_pFounded )
{
	
	ElementBase::ReadFromFile1( a_File, NULL, NULL );

	::std::vector<ElementBase*>& aDevices = *( (::std::vector<ElementBase*>*)a_pDevices );
	::std::vector<ElementBase*>& aFounded = *( (::std::vector<ElementBase*>*)a_pFounded );

	bool bFound;

	unsigned char ucFlags;

	int nKind;
	int i, j, nIndex, nSize, nSizeVect( (int)aDevices.size() ), nSizeFounded((int)aFounded.size());

	char* pcFamName = NULL;

	ElementBase* pElement = NULL;

	fread( &nSize, sizeof(nSize), 1, a_File );

	for( i = 0; i < nSize; ++i )
	{
		//ElementCreator::StringFromFile( a_File, &pcFamName );
		fread( &ucFlags, sizeof(ucFlags), 1, a_File );

		//if( ElementBase::GetFlagStat(CREATED_INSIDE,ucFlags) )
		if( false )
		{
			nKind = ElementCreator::LoadKindFromFile( a_File );
			pElement = ElementCreator::CreateNewDevice( nKind );
			pElement->ReadFromFile1( a_File, a_pDevices, a_pFounded );
			//AddElement( pElement, 0 );
			m_Families.push_back(pElement);
			//pElement->SetCreatedInsideLattice(1);
			pElement->SetFlagHard( ucFlags );
		}
		else
		{
			ElementCreator::StringFromFile( a_File, &pcFamName );
			fread( &nKind, sizeof(nKind), 1, a_File );

			bFound = false;
			for( j = 0; !bFound && j < nSizeVect; ++j )
			{
				if( pcFamName && aDevices[j]->GetFamName() && !strcmp(pcFamName, aDevices[j]->GetFamName()) )
				{
					//AddElement( aDevices[j], 0 );
					m_Families.push_back(aDevices[j]);
					//aDevices[j]->SetCreatedInsideLattice(0);
					aDevices[j]->SetFlag(CREATED_INSIDE,0);
					bFound = true;
				}
			}


			for( j = 0; !bFound && j < nSizeFounded; ++j )
			{
				if( pcFamName && aFounded[j]->GetFamName() && !strcmp(pcFamName, aFounded[j]->GetFamName()) )
				{
					//AddElement( aDevices[j], 0 );
					m_Families.push_back(aFounded[j]);
					//aFounded[j]->SetCreatedInsideLattice(0);
					bFound = true;
				}
			}

			if( !bFound )
			{
				pElement = ElementCreator::CreateNewDevice( nKind );
				pElement->SetFamName( pcFamName );
				//AddElement( pElement, 0 );
				m_Families.push_back(pElement);
				pElement->SetFlag(CREATED_INSIDE,0);
				aFounded.push_back(pElement);
			}
		}

	}


	fread( &nSize, sizeof(nSize), 1, a_File );

	for( i = 0; i < nSize; ++i )
	{
		fread( &nIndex, sizeof(nIndex), 1, a_File );
		m_Elements.push_back(nIndex);
	}

	//ElemsSeq::ObtainAll();// Sxalneri kara beri
	/*if( memcmp(m_FamName,"ARC",3) == 0 )
	{
		m_lfL = 0.;
	}*/
}



void ElemsSeq::WriteOptiM( FILE*const& a_File, const double& a_lfReserve )const
{
}



void ElemsSeq::LoadFromOptimString( const char*const& a_pcBuff, int a_nRead )
{
}



const SMatrix& ElemsSeq::GetMatrixTrans()const
{
	return m_MatrixTrans2;
}



const SMatrix& ElemsSeq::GetMatrixTwiss()const
{
	return m_MatrixTwiss2;
}



SVector ElemsSeq::Track( const SVector& coord0, bool*const& survive, int*const& losseIndex )
{
	SVector aVectorF(coord0), aVector0(coord0);

	for( int i(0); i < m_Elements.size() && *survive; ++i )
	{
		aVectorF = m_Families[m_Elements[i]]->Track(aVector0,survive,losseIndex);
		if(!(*survive)){*losseIndex = i;}
		aVector0 = aVectorF;
	}


	return aVectorF;
}



int ElemsSeq::NumberOfDevices()const
{
	return (int)m_Elements.size();
}



int ElemsSeq::NumberOfFamilies()const
{
	return (int)m_Families.size();
}



ElementBase* ElemsSeq::operator[](const int& a_nIndex)
{
	return m_Families[m_Elements[a_nIndex]];
}



ElementBase* ElemsSeq::operator()(const int& a_nIndex)
{
	return m_Families[a_nIndex];
}



SMatrix ElemsSeq::GetMatrixTrans(	const double& a_lfS )const
{
	//CFuncs::ObtainMatrixTransQuad( m_lfL, m_g, m_lfK );

	int nSize((int)m_Elements.size());

	if( !nSize )return g_ctmUniqTrMatrix;

	int nPlace(0);

	double lfSkizb(0.), lfVerj(m_Families[m_Elements[nPlace]]->GetLength());

	while(lfVerj<a_lfS && nPlace<nSize-1)
	{
		lfSkizb += m_Families[m_Elements[nPlace]]->GetLength();
		lfVerj += m_Families[m_Elements[++nPlace]]->GetLength();
	}

	if( memcmp("arus1_2cell1", m_FamName, 12) == 0 )
	{
		int a = 0;
	}

	if( memcmp("arus1_2cell1", m_FamName, 12) == 0 && nPlace == 1 )
	{
		int a = 0;
	}

	if( nPlace == 4 )
	{
		int a = 0;
	}

	SMatrix retMatrix = m_Families[m_Elements[nPlace]]->GetMatrixTrans(a_lfS-lfSkizb);
	//SMatrix mMatrix;

	for( int i = nPlace-1; i>=0; --i )
	{ 
		retMatrix *= m_Families[m_Elements[i]]->GetMatrixTrans();

		//mMatrix = retMatrix;
		//retMatrix = mMatrix * m_Families[m_Elements[i]]->GetMatrixTrans() ;
	}

	return retMatrix;
}






////////////////////////////////////////////////
/*ElemsSeq DAVIT_CLASSES::operator+( const ElemsSeq& eS1, const ElemsSeq& eS2 )
{

	ElemsSeq elemSeqUse(eS1);

	for( size_t i = 0; i<eS2.m_unSize; ++i )
		elemSeqUse.AddElement( *eS2.m_ppElems[i],1 );

	return elemSeqUse;
}*/



ElemsSeq DAVIT_CLASSES::operator+( const ElementBase& aE1, const ElementBase& aE2 )
{
	ElemsSeq elemSeqUse;

	elemSeqUse.AddElement( aE1 );

	elemSeqUse.AddElement( aE2 );

	return elemSeqUse;
}



ElemsSeq DAVIT_CLASSES::operator+( const ElemsSeq& eS, const ElementBase& aE )
{
	ElemsSeq elemSeqUse(eS);

	elemSeqUse.AddElement( aE );

	return elemSeqUse;
}


/*
ElemsSeq DAVIT_CLASSES::operator+( const ElementBase& aE, const ElemsSeq& eS )
{
	ElemsSeq elemSeqUse;


	elemSeqUse.AddElement( aE,1 );

	for( size_t i = 0; i<eS.m_unSize; ++i )
		elemSeqUse.AddElement( *eS.m_ppElems[i],1 );

	return elemSeqUse;
}*/



ElemsSeq DAVIT_CLASSES::operator&( const ElementBase& aE1, const ElementBase& aE2 )
{
	ElemsSeq elemSeqUse;

	elemSeqUse.AddElement( aE1 );

	elemSeqUse.AddElement( aE2 );

	return elemSeqUse;
}



ElemsSeq DAVIT_CLASSES::operator&( const ElemsSeq& eS, const ElementBase& aE2 )
{

	ElemsSeq elemSeqUse( eS );

	elemSeqUse.AddElement( aE2 );

	return elemSeqUse;
}





ElemsSeq DAVIT_CLASSES::operator *( const int& a_nN, const ElemsSeq& eS )
{
	ElemsSeq elemSeqUse(eS);


	for( int i = 1; i<a_nN; ++i )
		elemSeqUse = elemSeqUse + eS;

	return elemSeqUse;
}



/*
ElemsSeq DAVIT_CLASSES::operator *( const int& a_nN, const ElementBase& aE )
{
	ElemsSeq elemSeqUse;


	for( int i = 0; i<a_nN; ++i )
		elemSeqUse.AddElement( aE );

	return elemSeqUse;
}*/


}  //  namespace DAVIT_CLASSES {
