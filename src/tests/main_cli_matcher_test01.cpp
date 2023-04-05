//
// file:            main_cli_matcher_test01.cpp
// path:			src/tests/main_cli_matcher_test01.cpp
// created on:		2023 Apr 04
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <accelerator/elementbase.h>
#include <accelerator/elemsseq.h>
#include <accelerator/matcher.h>
#include <accelerator/cquad.h>
#include <accelerator/caperture.h>
#include <accelerator/cdrift.h>
#include <accelerator/cbendr.h>
#include <accelerator/csextupole.h>
#include <accelerator/comandsfl.h>
#include <iostream>


using namespace std;
using namespace DAVIT_CLASSES;

static ElemsSeq CrLattice(void);



static void MatchingFinishedClbk(void*){}

int main(void)
{

#if 1
	STwiss Twiss0 = g_ctmInitialTwissMatrix;
	ElemsSeq SS_Full;

	SS_Full = CrLattice();

	SS_Full.ObtainMatrixTrans();

	//CMainClass* pMainClass = CMainClass::Create( "C:\\InfoDDD.txt" ) ;
	Matcher* pMatcher = new Matcher(NULL, MatchingFinishedClbk);

	//pMainClass->CreateLattice( &SS_Full );
	//pMatcher->CreateLattice( &SS_Full);
	pMatcher->SetLattice(&SS_Full);

	Twiss0.betaX = 3.89615;
	Twiss0.alfaX = -0.109612;
	Twiss0.betaY = 21.4304;
	Twiss0.alfaY = 0.112912;
	Twiss0.etaX = 1.27935;
	Twiss0.etaPhX = 0.0226439;


	//pMainClass->SetTwiss( Twiss0 );
	pMatcher->SetTwiss0(Twiss0);


	//double lfParam = pMainClass->GetParam( BETAX );
	double lfParam = SS_Full.GetTwissParam2(BETAX, Twiss0);
	//lfParam = pMainClass->GetParam( SPECIAL2 );
	//lfParam = pMainClass->GetParam( BETAY );
	lfParam = SS_Full.GetTwissParam2(BETAY, Twiss0);
	//lfParam = pMainClass->GetParam( ALFAX );
	lfParam = SS_Full.GetTwissParam2(ALFAX, Twiss0);
	//lfParam = pMainClass->GetParam( ALFAY );
	lfParam = SS_Full.GetTwissParam2(ALFAY, Twiss0);
	//lfParam = pMainClass->GetParam( QX ) / 2. / PI;
	lfParam = SS_Full.GetTwissParam2(QX, Twiss0) / 2. / PI;
	//lfParam = pMainClass->GetParam( QY ) / 2. / PI;
	lfParam = SS_Full.GetTwissParam2(QY, Twiss0) / 2. / PI;
	//lfParam = ( pMainClass->GetParam( QX ) - 2. * PI * 0.291829 ) / 2. / PI;
	lfParam = (SS_Full.GetTwissParam2(QX, Twiss0) - 2. * PI * 0.291829) / 2. / PI;
	//lfParam = ( pMainClass->GetParam( QX ) - 2. * PI * 0.33701 ) / 2. / PI;
	lfParam = (SS_Full.GetTwissParam2(QX, Twiss0) - 2. * PI * 0.33701) / 2. / PI;
	//lfParam = pMainClass->GetParam( ETAX );
	lfParam = SS_Full.GetTwissParam2(ETAX, Twiss0);
	//lfParam = pMainClass->GetParam( ETAPHX );
	lfParam = SS_Full.GetTwissParam2(ETAPHX, Twiss0);


	//pMainClass->AddMatchParam( ETAX, 0., true, 0.00001 );
	//pMainClass->AddMatchParam( ETAPHX, 0., true, 0.00001 );
	pMatcher->AddOutput(0., 0.005, 1., ETAX);


	double dg = 0.15;


	double g_qFT2 = -0.025220;
	double g_qFT3 = -0.170581;
	//double g_qFT6 = -0.100664;
	//double g_qT8 = 0.011671;



	//pMainClass->SetElemParam( "qT9", CQuad::GRADIENT, g_qT9 );
	//pMainClass->SetElemParam( "qFF3", CQuad::GRADIENT, g_qFF3 );
	//pMainClass->SetElemParam( "qFF1", CQuad::GRADIENT, g_qFF1 );

	//pMainClass->SetElemParam( "qT10", CQuad::GRADIENT, 0.00313417364 );
	//pMainClass->SetElemParam( "qFF2", CQuad::GRADIENT, -0.430166398 );

#if 0
	pMainClass->SetMagnets(/**///
		/*nMagnets*/2,
		///*FamName[8]*/"qFT5", /*g1 = */g_qFT5 - dg, /*g2 = */g_qFT5 + dg,
		///*FamName[8]*/"qFT6", /*g1 = */g_qFT6 - dg, /*g2 = */g_qFT6 + dg,
		/*FamName[1]*/"qFT2", /*g1 = */g_qFT2 - dg, /*g2 = */g_qFT2 + dg,
		/*FamName[1]*/"qFT3", /*g1 = */g_qFT3 - dg, /*g2 = */g_qFT3 + dg
		///*FamName[0]*/"qFF2", /*g1 = */g_qFF2 - dg, /*g2 = */g_qFF2 + dg	

	);
#endif

	pMatcher->AddInput("qFT2", CQuad::GRADIENT, g_qFT2 - dg, g_qFT2 + dg, 500);
	pMatcher->AddInput("qFT3", CQuad::GRADIENT, g_qFT3 - dg, g_qFT3 + dg, 500);

	//pMatcher->AddInput("qDa", CQuad::GRADIENT, g_qFT2 - dg, g_qFT2 + dg, 2);
	//pMatcher->AddInput("qFT2", CQuad::GRADIENT, g_qFT2 - dg, g_qFT2 + dg, 3);
	//pMatcher->AddInput("qFT3", CQuad::GRADIENT, g_qFT3 - dg, g_qFT3 + dg, 4);


	CComands Comand;

	char pcComand[MAX_CHARACT_COMAND_LINE + 1];// Full comand line

	//unsigned long ulnN;
	//size_t unThreads;
	//char FileName[100];
	const char* pcArgs;
	//double lfDerivativeMax;

	while (strcmp(Comand.GetComand(), "EXIT"))
	{
		printf(">>");
		cin.getline(pcComand, MAX_CHARACT_COMAND_LINE);
		pcArgs = Comand.ReadComand(pcComand);

		/// 1.
		if (strcmp(Comand.GetComand(), "HELP") == 0)
		{
			/// 1.
			printf("\n\n1.\tHELP\t- shows all comands in this prog\n");
			/// 2.
			printf("2.\tEXIT\t- exit program\n");
			/// 3.
			printf("3.\tMATCH\t- start matching\n");
			/// 4.
			printf("4.\tPAUSE\t- pause matching\n");
			/// 5.
			printf("5.\tSTOP\t- stop matching\n");
			/// 6.
			printf("6.\tN\t- sets new number of points for matching\n");
			/// 7.
			printf("7.\tTHREADS\t- sets number of threads for matching\n");
			/// 8.
			printf("8.\tPATH\t- sets new path for log\n");
			/// 9.
			printf("9.\tSHOWLOG\t- shows log file information\n");
			/// 10.
			printf("10.\tSERVER\t- creates server\n");
			// 11.
			printf("11.\tOPTIM\t- creates optiM file, from min.\n");
			printf("\n");
		}
		/// 2.
		else if (strcmp(Comand.GetComand(), "EXIT") == 0)
		{
		}
		/// 3.
		else if (strncmp(Comand.GetComand(), "MATCH", 5) == 0)
		{
			/// Comand.GetStartMatchArgs( pcArgs, FileName );
			const char* pChTemp = Comand.GetComand();
			pChTemp += 5;
			int nAlg = atoi(pChTemp);
			//pMainClass->StartMatch( nAlg );
			//pMainClass->StartMatch(1);
			pMatcher->StartMatch(1);
		}
		/// 4.
		else if (strcmp(Comand.GetComand(), "PAUSE") == 0)
		{
			//pMainClass->PauseMatch();
			pMatcher->PauseMatch();
		}
		/// 5.
		else if (strcmp(Comand.GetComand(), "STOP") == 0)
		{
			//CMainClass::StopMatch();
			pMatcher->StopMatch();
		}
		/// 6.
		else if (strcmp(Comand.GetComand(), "THREADS") == 0)
		{
			//Comand.Get_N_Threads( pcArgs, unThreads );
			//pMainClass->SetThreadSCount( unThreads );
		}
		/// 7.
		else if (strcmp(Comand.GetComand(), "PATH") == 0)
		{
			//Comand.GetPath( pcArgs, FileName );
			//pMainClass->SetPath( FileName );
		}
		/// 8.
		else if (strcmp(Comand.GetComand(), "SHOWLOG") == 0)
		{
			//pMainClass->ShowLog();
		}
		/// 9.
		else if (strcmp(Comand.GetComand(), "OPTIM") == 0)
		{
			//Comand.GetPath( pcArgs, FileName );
			//pMainClass->CreateOptiMFile( FileName );
		}
		/// 10.
		else if (strcmp(Comand.GetComand(), "MATCH2") == 0)
		{
			//// pMainClass->Match2();
		}
		/// 11.
		else if (strcmp(Comand.GetComand(), "DERIVATIVE") == 0)
		{
			//Comand.Get_Derivative( pcArgs, lfDerivativeMax );
			//CMainClass::Match3::SetDerivativeMax( lfDerivativeMax );
		}
		else
		{
			printf("\nWrong Comand. Type help, for looking all comands.\n\n");
		}

	}




	delete pMatcher;

#endif

	return 0;
}



static ElemsSeq CrLattice(void)
{


	//$qD  oqc  iQ      oo  $D  oo      sF qFT2 sF  oqc  $qF  oqc  iQ             od2           sD qDT1 sD oqc  $qD
	//$qD  oqc  iQ          od1             sF qFT3 sF  oqc  $qF  oqc  iQ      oo1  $D  oo     sD qDT1 sD oqc  $qD

		// $qD="hQ   qDa   hQ";
		// qDa			L[cm]=40/2				G[kG/cm]=-2.417274					Tilt[deg]=0
	double			L_qDa(0.2), g_qDa(-0.542510307);
	// oqc			L[cm]=$L_qc;$L_qc=10;
	double			L_oqc(0.1);
	// iQ			L[cm]=30				Tilt[deg]=0 
	double			L_iQ(0.3);
	// oo			L[cm]=$L_oo;$L_oo=30; 
	double			L_oo(0.3);
	// $D="hD gH bH gH hD    oo    hD gH bH gH hD";
	double			L_bH(1.94), h_bH(PI / 40. / L_bH);
	// bH			L[cm]=$Ldip				B[kG]=$Bdip G[kG/cm]=0				Tilt[deg]=0
	// sF			L[cm]=30/2*1.e-6		S[kG/cm/cm)]=30/2*1.e-6*$sF			Tilt[deg]=0
	double			L_sF(15.e-8), S_sF(30. / 2. * 1.e-6);
	// sD			L[cm]=30/2*1.e-6		S[kG/cm/cm)]=30/2*1.e-6*$sF			Tilt[deg]=0
	double			L_sD(15.e-8), S_sD(30. / 2. * 1.e-6);
	// $qF="hQ    qFa   hQ";
	// qFa			L[cm]=40				G[kG/cm]=2.478602					Tilt[deg]=0
	double			L_qFa(0.4), g_qFa(0.556274189);
	// od2			L[cm]=$L_miss2;$L_miss2=$L_oo1   + 2*$L_oo+2*$Ldip;  =>         578
	double			L_od2(5.78);
	// qDT1			L[cm]=30				G[kG/cm]=1.e-6						Tilt[deg]=0
	double			L_qDT1(0.3), g_qDT1(2.24430622e-007);
	// od1			L[cm]=$L_miss1;$L_miss1=$L_oo     + 2*$L_oo+2*$Ldip;  =>         478
	double			L_od1(4.78);
	// oo1			L[cm]=$L_oo1;$L_oo1=$L_oo+100;  =>         130
	double			L_oo1(1. + L_oo);
	// qFT1			L[cm]=30				G[kG/cm]=1.e-6						Tilt[deg]=0
	double			L_qFT1(0.3), g_qFT1(2.24430622e-007);



	ElemsSeq qD, qF, D, PART1, PART2, PART3, ARC;
	qD.SetFamName("qD");
	qF.SetFamName("qF");
	D.SetFamName("D");
	PART1.SetFamName("PART1");
	PART2.SetFamName("PART2");
	PART3.SetFamName("PART3");
	ARC.SetFamName("ARC");

	CAperture	hQ;							hQ.SetFamName("hQ");
	CAperture	hD;							hD.SetFamName("hD");
	CQuad		qDa(L_qDa, g_qDa);			qDa.SetFamName("qDa");
	CQuad		qFa(L_qFa, g_qFa);			qFa.SetFamName("qFa");
	CDrift		oqc(L_oqc);					oqc.SetFamName("oqc");
	CDrift		iQ(L_iQ);					iQ.SetFamName("iQ");
	CDrift		oo(L_oo);					oo.SetFamName("oo");
	CDrift		oo1(L_oo1);					oo1.SetFamName("oo1");
	CBendR		bH(L_bH, h_bH);				bH.SetFamName("bH");
	CSextupole	sF(L_sF, S_sF);				sF.SetFamName("sF");
	CSextupole	sD(L_sD, S_sD);				sD.SetFamName("sD");
	CDrift		od1(L_od1);					od1.SetFamName("od1");
	CDrift		od2(L_od2);					od2.SetFamName("od2");
	CQuad		qDT1(L_qDT1, g_qDT1);		qDT1.SetFamName("qDT1");
	CQuad		qFT2(L_qFT1, g_qFT1);		qFT2.SetFamName("qFT2");
	CQuad		qFT3(L_qFT1, g_qFT1);		qFT3.SetFamName("qFT3");

	qD = hQ + qDa + hQ;
	qF = hQ + qFa + hQ;
	D = hD + /*gH +*/ bH + /*gH +*/ hD + oo + hD + /*gH +*/ bH + /*gH +*/ hD;

	PART1 = qD + oqc + iQ + oo + D + oo + sF;
	//PART1 = oqc + iQ + oo + D + oo + sF;
	PART2 = sF + oqc + qF + oqc + iQ + od2 + sD + qDT1 + sD + oqc + qD + qD + oqc + iQ + od1 + sF;
	PART3 = sF + oqc + qF + oqc + iQ + oo1 + D + oo + sD + qDT1 + sD + oqc + qD;


	//ARC.AddElement( qDa);
	ARC.AddElement(PART1);
	ARC.AddElement(qFT2);
	ARC.AddElement(PART2);
	ARC.AddElement(qFT3);
	ARC.AddElement(PART3);


	return ARC;

}
