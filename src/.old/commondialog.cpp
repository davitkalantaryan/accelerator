#include "stdafx.h"
#include "commondialog.h"

#include "elementcreator.h"

#define		DEVICE_SIZE		30

/*
static int							m_nStNumber;
	
	bool								m_bIsCreating;
	BaseAccElement*						m_pActiveDevice;
	VectorOfTypeNS<BaseAccElement*>		m_Devices;
	Matcher								m_Matcher;
	int									m_nIndex;*/


int CommonDialog::m_nStNumber		= 0;


CommonDialog::CommonDialog()
	:	m_Devices(512),
		m_MatcherFields(512),
		m_pActiveDevice(0)
{
	/*STwiss Twiss0 = GetTwiss();

	Twiss0.betaX = 7.46389;
	Twiss0.alfaX = -2.47405;
	Twiss0.betaY = 21.4304;
	Twiss0.alfaY = 0.112912;
	Twiss0.etaX = 1.27935;
	Twiss0.etaPhX = 0.0226439;

	m_Matcher2.SetTwiss(Twiss0);*/
}



CommonDialog::~CommonDialog()
{
	Empty();
}



void CommonDialog::NewFile()
{
	Empty();
}



void CommonDialog::OpenFile( const char* a_FileName )
{

	
	FILE* aFile = fopen( a_FileName, "rb" );

	if( !aFile )
		return;

	Empty();

	char vcFamName[FAM_NAME_SIZE];

	ElementBase *pElement;

	int i, j, nSize, nKind, nSizeFounded;
	bool bFound;

	fread( &nSize, sizeof(nSize), 1, aFile );

	VectorOfType2<ElementBase*> aFounded(nSize);


	for( i = 0; i < nSize; ++i )
	{

		nKind = ElementCreator::LoadKindFromFile( aFile );
		ElementBase::FamNameFromFile1( aFile, vcFamName );

		nSizeFounded = aFounded.size();
		bFound = false;

		for( j = 0; !bFound && j < nSizeFounded; /*++j*/ )
		{
			pElement = aFounded[j];
			if( !strncmp(vcFamName,pElement->GetFamName(),FAM_NAME_SIZE) )
			{
				bFound = true;
				aFounded.RemoveElement(j);
				//pElement->ReadFromFile1( aFile, &m_Devices, &aFounded );// Texapoxvec nerqev
			}
			else
			{
				++j;
			}

			nSizeFounded = aFounded.size(); // Sa kara ev chlini
		}

		if( !bFound )
		{
			pElement = ElementCreator::CreateNewDevice( nKind );
			pElement->SetFamName(vcFamName);
		}

		if( pElement )
		{
			pElement->ReadFromFile1( aFile, &m_Devices, &aFounded );
			pElement->ObtainMatrixTrans();
			m_Devices.push_back( pElement );
		}

		
	}

	for( i = 0; i < nSize; ++i )
	{
		m_Devices[i]->ObtainMatrixTrans();
	}


	////////////////////////////////////////////////////////////////
	SMatchFields* pMatchFields = NULL;
	for( i = 0; i < nSize; ++i )
	{
		pMatchFields = (SMatchFields*)malloc(sizeof(SMatchFields));
		//pMatchFields->m_Twiss0 = GetTwiss();
		//pMatchFields->m_ucFlags = 0;
		fread( pMatchFields, sizeof(SMatchFields), 1, aFile );
		m_MatcherFields.push_back(pMatchFields);
	}


	fclose( aFile );


}



void CommonDialog::SaveInFile( const char* a_FileName )const
{

	
	FILE* aFile = fopen( a_FileName, "wb" );

	if( !aFile )
		return;

	int i, nSize = (int)m_Devices.size();

	fwrite( &nSize, sizeof(nSize), 1, aFile );


	for( i = 0; i < nSize; ++i )
	{
		m_Devices[i]->SetFlag(CREATED_INSIDE,0);
		m_Devices[i]->WriteToFile1( aFile );
	}

	for( i = 0; i < nSize; ++i )
	{
		fwrite( m_MatcherFields[i], sizeof(SMatchFields), 1, aFile );
	}

	//fwrite( &

	fclose( aFile );


}



void CommonDialog::Empty()
{
	int nSize( (int)m_Devices.size() );

	for( int i(nSize-1); i >= 0; --i )
	{
		free( m_MatcherFields[i] );
		delete m_Devices[i];
	}

	m_MatcherFields.Empty();
	m_Devices.Empty();
}
