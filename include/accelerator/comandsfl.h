#ifndef COMANDSFL_H
#define COMANDSFL_H

#define MAX_CHARACT_COMAND_LINE 1023

namespace DAVIT_CLASSES
{
	class CComands
	{
	public:
		CComands();
		~CComands();


		const char* ReadComand( const char*const& a_pcComandStr )const;
		static void StartMatch();

		inline const char*const& GetComand()const{ return m_pcComand; }

		void GetPath( const char*& a_pcArgs, char*const& a_pcFileName )const;
		void Get_N_Args( const char*& a_pcArgs, unsigned long& a_ulnN )const;
		void Get_N_Threads( const char*& a_pcArgs, size_t& a_unThreads )const;
		void Get_Derivative( const char*& a_pvArgs, double& a_lfDerivativeMax )const;

	private:
		char* m_pcComand;
	};
};

#endif