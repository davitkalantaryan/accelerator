#ifndef __matcher_h__
#define __matcher_h__

#define		LATTICE_INSIDE		0
#define		TRY_CLOSE_TWISS		1

#include <signal.h>
#include "elementbase.h"
#include "vectoroftype2.h"
#include "../../../.aallfiles.2017.01.26/sources/threaddv.h"

using namespace DAVIT_CLASSES;



struct SInputParams
{
	int		nWhichChange;	// This show which field of magnet can be changed (curent, length, ...)
	int		nIndex;
	double	par0;
	double	parF;
	double	DeltaPar;
	int		m_nNumber;
};



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
};


class Matcher;


class OptimAlg
{
public:
	class CMatcherThread
	{
		friend class Matcher;
		friend class OptimAlg;

		OptimAlg*		m_pOwner;
		ElementBase*	m_pLattice;
		ElementBase*	m_pLatticeMin;
		double			m_lfKshirMin;

		int64_tt		m_lli1;
		int64_tt		m_lli2;
		
		int64_tt*		m_pllnStep;

		STwiss			m_TwissF;

		ThreadDv		m_Thread;

		int*			m_pWork;

		void Run();

		void* ThreadFunc();

		static void* ThreadFuncStat( void* a_pArg );
	}friend;

	
public:
	OptimAlg( const size_t& unNumberThreads, class Matcher* pOwner  );

	~OptimAlg();

	void			StartMatch(int nThreadsNum);

private:
	void*			FinalMatcher();

	static void*	FinalMatcherStat(void*);

	void			TellOwnerOnFinish();

	
private:
	class Matcher*					m_pOwner;
	int64_tt*						m_pllnSize;
	double							m_lfKshirMinTotal;

	VectorOfType2<CMatcherThread*>	m_ThreadItems;

	sig_atomic_t					m_bMatchingActive;
	ThreadDv						m_MatcherTHread;
	int								m_bWork;

	//void (*m_fpFinished)(void*);

};



struct SMatchFields
{
	//unsigned int					m_unLatticeInside : 1;
	unsigned char	m_ucFlags;
	STwiss			m_Twiss0;
};



class Matcher
{
	friend class OptimAlg;
	friend class OptimAlg::CMatcherThread;
public:
	enum _MATCH_STATES{ MATCH_NOT_DONE, MATCH_DONE};

	Matcher( void* a_pGuiOwner, void (*a_fpFinished)(void*) );

	~Matcher();

	void			CreateLattice( ElementBase* pSource );

	void			SetLattice( ElementBase* pLattice );

	void			AddInput( const SInputParams& a_Input );

	void			AddInput( const char* cpcFamName, int nWhich, double Param0, double ParamF, int nNumber );

	void			AddInput( int nWhich, int nIndex, double lfParam0, double lfParamF, double DeltaParam );

	void			AddInput( int nWhich, int nIndex, double Param0, double ParamF, int nNumber );

	void			AddOutput(	double ParamValue, double Accuracy, double Importance,
								int whichParam1, int nWhere1=END_OF_LATTICE, double Koef1=1.,
								int whichParam2=MTR11, int nWhere2=NO_INDEX, double Koef2=1.  );

	void			AddOutput( const SParamsToMatch& a_Output );

	double			GetKshir(const ElementBase* pTestLattice, bool*const& bFound, STwiss*const& pTwissF)const;

	void			StartMatch(int nThreadsNum);

	void			PauseMatch();

	void			StopMatch();

	const STwiss&	GetTwiss0()const;

	void			SetTwiss0(const STwiss& Twiss0);

	STwiss*			GetTwissPtr(){return &m_Params.m_Twiss0;}

	void			LoadMinLattice();

	void			SetMatchFields1(const SMatchFields& a_Matcher );

	void			SetAnCorrMatchFields1(SMatchFields* a_pMatcherFlds );

	VectorOfType2<SInputParams>* GetInputs()
	{
		return &m_Inputs;
	}

	VectorOfType2<SParamsToMatch>* GetOutputs()
	{
		return &m_Outputs;
	}

	ElementBase*	GetLatticeMin()
	{
		return m_pLatticeMinTot;
	}

private:
	void			GetKshirSingle(	double& a_lfRet, const ElementBase* pTestLattice,
									const SParamsToMatch& a_Param,STwiss*const& pTwissF)const;

private:
	void*							m_pGuiOwner;
	void (*m_fpFinished)(void*);

	ElementBase*					m_pLattice;
	ElementBase*					m_pLatticeMinTot;
	VectorOfType2<SInputParams>		m_Inputs;
	VectorOfType2<SParamsToMatch>	m_Outputs;	

	OptimAlg*						m_pOptimizer;

	mutable sig_atomic_t			m_nMatchState;

	SMatchFields					m_Params;
};



#endif/* #ifndef __matcher_h__ */
