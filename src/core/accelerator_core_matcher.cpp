#include "stdafx.h"
#include <accelerator/matcher.h>
#include <math.h>


namespace DAVIT_CLASSES {


void OptimAlg::CMatcherThread::Run()
{
	m_Thread = ::std::thread(&ThreadFuncStat,this);
}



void* OptimAlg::CMatcherThread::ThreadFuncStat( void* a_pArg )
{
	OptimAlg::CMatcherThread* pMatcher = (OptimAlg::CMatcherThread*)a_pArg;

	return pMatcher->ThreadFunc();
}



void* OptimAlg::CMatcherThread::ThreadFunc()
{

	int64_t iTmp, llnStep;
	int i2;
	const size_t nMagnets( m_pOwner->m_pOwner->m_Inputs.size() );
	SInputParams aInput;

	bool bIsFound;


	double lfKshir,lfParam;

	lfKshir = 0.;

	m_lfKshirMin = m_pOwner->m_lfKshirMinTotal;


	memset( m_pllnStep, -1, sizeof(int64_t)*nMagnets );


	for( int64_t lli(m_lli1); lli < m_lli2 && *m_pWork; ++lli )
	{/// For1

		iTmp = lli;

		for( i2 = 0; i2 < nMagnets; ++i2 )
		{/// For2


			llnStep = iTmp / m_pOwner->m_pllnSize[ nMagnets - i2 - 1 ];
			iTmp -= llnStep * m_pOwner->m_pllnSize[ nMagnets - i2 - 1 ];

			if( llnStep == m_pllnStep[i2] )
				continue;
			else
			{
				m_pllnStep[i2] = llnStep;
			}

			aInput = (m_pOwner->m_pOwner->m_Inputs)[i2];

			lfParam = aInput.par0 + ((double)llnStep) * aInput.DeltaPar;// *-@ kara chlini

			//m_pLattice->SetFieldsPassive( aInput.nWhichChange, lfParam, aInput.nIndex );// SetParamPassive
			m_pLattice->SetFields(aInput.nWhichChange,lfParam,aInput.nIndex);


			// Sranq stex avelord en
			lfKshir = m_pOwner->m_pOwner->GetKshir(m_pLattice,&bIsFound,&m_TwissF);

			if( bIsFound )
			{
				// Stop Optim Alg
				*m_pWork = 0;
				m_pOwner->m_pOwner->m_pLatticeMinTot->EQUATING(m_pLattice);
				return 0;
			}


			if( lfKshir < m_lfKshirMin  )
			{
				//m_pLatticeMin->EQUATING( m_pLattice );
				m_pLatticeMin->SetFieldsVeryPassive(aInput.nWhichChange,lfParam,aInput.nIndex);
				m_lfKshirMin = lfKshir;
			}


		}/// End For2

	}/// End For1
	

	return 0;
}







OptimAlg::OptimAlg( const size_t& unNumberThreads, class Matcher* pOwner  )
	:	m_pOwner(pOwner),
		m_pllnSize(NULL),
		m_lfKshirMinTotal(0.),
		m_ThreadItems(unNumberThreads),
		m_bMatchingActive(0)
{
}



OptimAlg::~OptimAlg()
{
	free( m_pllnSize);
}



/*
	class Matcher*					m_pOwner;
	int64_tt*						m_pllnSize;
	double							m_lfKshirMinTotal;
	ElementBase*					m_pLatticeMinTot;

	VectorOfType2<CMatcherThread*>	m_ThreadItems;

		OptimAlg*		m_pOwner;
		ElementBase*	m_pLattice;
		ElementBase*	m_pLatticeMin;
		double			m_lfKshirMin;

		int64_tt		m_lli1;
		int64_tt		m_lli2;
		
		int64_tt*		m_pllnStep;

		STwiss			m_TwissF;

		ThreadDv		m_Thread;
*/


void* OptimAlg::FinalMatcherStat(void* a_pArg)
{
	OptimAlg* pOwner = (OptimAlg*)a_pArg;

	return pOwner->FinalMatcher();
}



void* OptimAlg::FinalMatcher()
{
	if( !m_bMatchingActive )
		return 0;

	double lfKshir;
	bool bIsFound;
	OptimAlg::CMatcherThread* pThrItem;

	for( int i(0); i<m_ThreadItems.size(); ++i )
	{
		pThrItem = m_ThreadItems[i];
		(pThrItem->m_Thread).join();
		(pThrItem->m_pLatticeMin)->ObtainMatrixTrans();
		(pThrItem->m_pLatticeMin)->ObtainMatrixTwiss();

		lfKshir = m_pOwner->GetKshir(pThrItem->m_pLatticeMin,&bIsFound,&pThrItem->m_TwissF);

		if( lfKshir < m_lfKshirMinTotal && m_bWork  )
		{
			//m_pLatticeMin->EQUATING( m_pLattice );
			//m_pLatticeMin->SetFieldsVeryPassive(aInput.nWhichChange,lfParam,aInput.nIndex);
			m_lfKshirMinTotal = lfKshir;
			(m_pOwner->m_pLatticeMinTot)->EQUATING( pThrItem->m_pLatticeMin );
		}
	}


	(m_pOwner->m_pLatticeMinTot)->ObtainAll();


	m_bMatchingActive = 0;

	TellOwnerOnFinish();


	return 0;
}



void OptimAlg::TellOwnerOnFinish()
{
	if( m_pOwner->m_fpFinished )
	{
		(*m_pOwner->m_fpFinished)(m_pOwner->m_pGuiOwner);
	}
}



void OptimAlg::StartMatch(int nThreadsNum)
{

	bool bIsFound;
	STwiss aTwissF;
	m_lfKshirMinTotal = m_pOwner->GetKshir(m_pOwner->m_pLatticeMinTot,&bIsFound,&aTwissF);

	if( bIsFound )
	{
		TellOwnerOnFinish();
		return;
	}

	m_bWork = 1;

	const size_t nMagnets = (m_pOwner->m_Inputs).size();
	if(!nMagnets)
	{
		TellOwnerOnFinish();
		return ;
	}
	m_pllnSize = (int64_t*)realloc( m_pllnSize,sizeof(int64_t)*nMagnets );

	OptimAlg::CMatcherThread* pThrItem;

	int i,nSize( (int)m_ThreadItems.size() );


	int64_t llnTotalIters, llnSize(1);

	m_pllnSize[nMagnets-1] = llnSize;
	for( i = 1; i < nMagnets; ++i )
	{
		llnSize *= (m_pOwner->m_Inputs)[nMagnets-i].m_nNumber;
		m_pllnSize[nMagnets-i-1] = llnSize;
	}
	llnTotalIters = llnSize * (m_pOwner->m_Inputs)[0].m_nNumber;

	for( i = 0; i < nSize; ++i )
	{
		pThrItem = m_ThreadItems[i];
		free(pThrItem->m_pllnStep);
		delete pThrItem;
	}

	m_ThreadItems.clear();

	int64_t llni1(0), llndi(llnTotalIters/nThreadsNum + (llnTotalIters%nThreadsNum?1:0)), llni2(llndi);

	m_bMatchingActive = 1;

	for( i = 0; i < nThreadsNum; ++i )
	{
		pThrItem = new OptimAlg::CMatcherThread;
		pThrItem->m_pOwner = this;
		pThrItem->m_pLattice = (m_pOwner->m_pLattice)->Clone();
		pThrItem->m_pLatticeMin = (m_pOwner->m_pLatticeMinTot)->Clone();
		pThrItem->m_lfKshirMin = m_lfKshirMinTotal;
		pThrItem->m_lli1 = llni1;
		pThrItem->m_lli2 = i<nThreadsNum-1 ? llni2 : llnTotalIters;
		pThrItem->m_pWork = &m_bWork;
		llni1 += llndi;
		llni2 += llndi;
		pThrItem->m_pllnStep = (int64_t*)malloc( sizeof(int64_t)*nMagnets );
		m_ThreadItems.push_back(pThrItem);

		(pThrItem->m_Thread) = ::std::thread( &OptimAlg::CMatcherThread::ThreadFuncStat, pThrItem );
	}

	m_MatcherTHread = ::std::thread(&OptimAlg::FinalMatcherStat, this);
	m_MatcherTHread.detach(); // todo: think on this
}





/////////////////////////////////////////////
Matcher::Matcher( void* a_pGuiOwner, void (*a_fpFinished)(void*) )
	:	m_pGuiOwner(a_pGuiOwner),
		m_fpFinished(a_fpFinished),
		m_pLattice(NULL),
		m_pLatticeMinTot(NULL),
		m_Inputs(8),
		m_Outputs(8)
{
	/*
	struct STwiss
	{
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

		inline void ObtanGamaX(){ gamaX = ( 1. + alfaX*alfaX ) / betaX ; }
		inline void ObtanGamaY(){ gamaY = ( 1. + alfaY*alfaY ) / betaY ; }
	};
	*/


	//m_unLatticeInside = 0;
	memset( &m_Params, 0, sizeof(SMatchFields) );
	ElementBase::SetFlagStat( LATTICE_INSIDE, 0, &m_Params.m_ucFlags);
	m_pOptimizer = new OptimAlg(10,this);

	m_nMatchState = MATCH_NOT_DONE;

	m_Params.m_Twiss0.betaX	= 1.;
	m_Params.m_Twiss0.alfaX	= 0.;
	m_Params.m_Twiss0.gamaX	= 1.;
	m_Params.m_Twiss0.etaX	= 0.;
	m_Params.m_Twiss0.etaPhX= 0.;

	m_Params.m_Twiss0.betaY	= 1.;
	m_Params.m_Twiss0.alfaY	= 0.;
	m_Params.m_Twiss0.gamaY	= 1.;
	m_Params.m_Twiss0.etaY	= 0.;
	m_Params.m_Twiss0.etaPhY= 0.;
}



Matcher::~Matcher()
{
	delete m_pLatticeMinTot;
	if( ElementBase::GetFlagStat(LATTICE_INSIDE,m_Params.m_ucFlags) )delete m_pLattice;
}



void Matcher::CreateLattice( ElementBase* a_pSource )
{
	if( ElementBase::GetFlagStat(LATTICE_INSIDE,m_Params.m_ucFlags) )
		delete m_pLattice;

	m_pLattice = a_pSource->Clone();

	//m_unLatticeInside = 1;
	ElementBase::SetFlagStat( LATTICE_INSIDE,1,&m_Params.m_ucFlags );

	delete m_pLatticeMinTot;

	m_pLatticeMinTot = m_pLattice->Clone();

	m_nMatchState = MATCH_NOT_DONE;
}



void Matcher::SetLattice( ElementBase* a_pLattice )
{
	if( ElementBase::GetFlagStat(LATTICE_INSIDE,m_Params.m_ucFlags) )
		delete m_pLattice;

	m_pLattice = a_pLattice;

	//m_unLatticeInside = 0;
	ElementBase::SetFlagStat( LATTICE_INSIDE,0,&m_Params.m_ucFlags );

	delete m_pLatticeMinTot;

	m_pLatticeMinTot = m_pLattice->Clone();

	m_nMatchState = MATCH_NOT_DONE;
}



void Matcher::AddInput( const SInputParams& a_Input )
{
	m_Inputs.push_back(a_Input);
}



void Matcher::AddInput( const char* cpcFamName, int nWhich, double Param0, double ParamF, int nNumber )
{
	int nIndex = m_pLattice->GetIndex(cpcFamName);

	if( nIndex != NO_INDEX )
	{
		Matcher::AddInput(nWhich,nIndex,Param0,ParamF,nNumber);
	}
}



void Matcher::AddInput( int a_nWhich, int a_nIndex, double a_lfParam0, double a_lfParamF, double a_lfDeltaParam )
{
	SInputParams aInput;

	aInput.nWhichChange	= a_nWhich;
	aInput.nIndex		= a_nIndex;
	aInput.par0			= a_lfParam0;
	aInput.parF			= a_lfParamF;
	aInput.DeltaPar		= a_lfDeltaParam;
	aInput.m_nNumber	= (int)((a_lfParamF-a_lfParam0)/a_lfDeltaParam);

	m_Inputs.push_back(aInput);
}



void Matcher::AddInput( int a_nWhich, int a_nIndex, double a_lfParam0, double a_lfParamF, int a_nNumber )
{
	SInputParams aInput;

	aInput.nWhichChange	= a_nWhich;
	aInput.nIndex		= a_nIndex;
	aInput.par0			= a_lfParam0;
	aInput.parF			= a_lfParamF;
	aInput.DeltaPar		= (a_lfParamF - a_lfParam0)/((double)a_nNumber);
	aInput.m_nNumber	= a_nNumber;

	m_Inputs.push_back(aInput);

	m_nMatchState = MATCH_NOT_DONE;
}



void Matcher::AddOutput( const SParamsToMatch& a_Output )
{
	m_Outputs.push_back(a_Output);

	m_nMatchState = MATCH_NOT_DONE;
}


/*
struct SParamSingle
{
	int		m_nWhere;	// Magnet Index	(-2 means end of lattice)
	int		whichParam;
	double	m_lfKoef;
};



struct SParamsToMatch
{
	double			ParamValue;
	double			Accuracy;
	double			lfImportance;

	SParamSingle	m_Param1;
	SParamSingle	m_Param2;

};*/



void Matcher::AddOutput(double a_lfParamValue, double a_lfAccuracy, double a_lfImportance,
						int a_whichParam1, int a_nWhere1, double a_lfKoef1,
						int a_whichParam2, int a_nWhere2, double a_lfKoef2 )
{
	SParamsToMatch aOutput;

	aOutput.ParamValue			= a_lfParamValue;
	aOutput.Accuracy			= a_lfAccuracy;
	aOutput.lfImportance		= a_lfImportance;

	aOutput.m_Param1.m_nWhere	= a_nWhere1;
	aOutput.m_Param1.whichParam	= a_whichParam1;
	aOutput.m_Param1.m_lfKoef	= a_lfKoef1;

	aOutput.m_Param2.m_nWhere	= a_nWhere2;
	aOutput.m_Param2.whichParam	= a_whichParam2;
	aOutput.m_Param2.m_lfKoef	= a_lfKoef2;

	m_Outputs.push_back(aOutput);

	m_nMatchState = MATCH_NOT_DONE;
}



void Matcher::GetKshirSingle(double& a_lfRet, const ElementBase* pTestLattice,
							 const SParamsToMatch& a_Param,STwiss*const& pTwissF)const
{

	pTestLattice->GetTwissParam(a_lfRet,a_Param.m_Param1.m_nWhere,a_Param.m_Param1.whichParam,m_Params.m_Twiss0,pTwissF);

	if(a_Param.m_Param2.m_nWhere != NO_INDEX)
	{
		double lfValue2;
		pTestLattice->GetTwissParam(lfValue2,a_Param.m_Param2.m_nWhere,a_Param.m_Param2.whichParam,m_Params.m_Twiss0,pTwissF);

		a_lfRet = a_lfRet*a_Param.m_Param1.m_lfKoef + lfValue2*a_Param.m_Param2.m_lfKoef;
	}

}



double Matcher::GetKshir(const ElementBase* pTestLattice,bool*const& bFound,STwiss*const& pTwissF)const
{
	int nSize((int)m_Outputs.size());
	double lfValue,lfKshir(0.);

	*bFound = true;

	for( int i(0); i < nSize; ++i)
	{
		//if( !m_Outputs[i].ifCompare )continue;
		//pTestLattice->GetTwissParam(m_Outputs[i].whichParam,lfValue,m_Twiss0,pTwissF,m_Outputs[i].nIndex1,m_Outputs[i].nIndex2);
		
		Matcher::GetKshirSingle(lfValue,pTestLattice,m_Outputs[i],pTwissF);
		lfValue = fabs(lfValue-m_Outputs[i].ParamValue);
		lfKshir += lfValue*m_Outputs[i].lfImportance;

		*bFound = (*bFound) && (lfValue<m_Outputs[i].Accuracy);
	}

	if( *bFound )m_nMatchState = MATCH_DONE;

	return lfKshir;
}



void Matcher::StartMatch(int nThreadsNum)
{
	if(!m_pLattice)
		return;

	if(m_nMatchState == MATCH_DONE)
		return;

	m_pOptimizer->StartMatch(nThreadsNum);
}



void Matcher::PauseMatch()
{
}



void Matcher::StopMatch()
{
}



const STwiss& Matcher::GetTwiss0()const
{
	return m_Params.m_Twiss0;
}



void Matcher::SetTwiss0(const STwiss& Twiss0)
{
	m_Params.m_Twiss0 = Twiss0;

	TwissObtainGamaX(&(m_Params.m_Twiss0));
	TwissObtainGamaY(&(m_Params.m_Twiss0));
}



void Matcher::LoadMinLattice()
{
	m_pLattice->EQUATING( m_pLatticeMinTot );

	m_pLattice->ObtainAll();
}



void Matcher::SetAnCorrMatchFields1(SMatchFields* a_pMatcherFlds )
{
	TwissObtainGamaX(&(a_pMatcherFlds->m_Twiss0));
	TwissObtainGamaY(&(a_pMatcherFlds->m_Twiss0));

	memcpy( &m_Params, a_pMatcherFlds, sizeof(SMatchFields) );
}



void Matcher::SetMatchFields1(const SMatchFields& a_Matcher )
{
	memcpy( &m_Params, &a_Matcher, sizeof(SMatchFields) );

	TwissObtainGamaX(&(m_Params.m_Twiss0));
	TwissObtainGamaY(&(m_Params.m_Twiss0));
}


}  //  namespace DAVIT_CLASSES {
