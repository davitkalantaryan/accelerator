#ifndef __vectoroftype2_h__
#define __vectoroftype2_h__


#define		_type_ind_	size_t


#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>		// For func. qsort
#include <string.h>		// For func. memmove

#include "structs_accl.h"


template<class Type>class VectorOfType2
{

public:
	/*
	 * Constructors
	 */
	VectorOfType2( _type_ind_ a_unReAllocSize )
		:	m_unReAllocSizeMin1( RoundInteger( a_unReAllocSize ? a_unReAllocSize : 1 ) - 1 ),
			m_unSize( 0 ),
			m_Elements( 0 )
	{
		m_Elements = (Type*)realloc( m_Elements, (m_unReAllocSizeMin1 + 1) * sizeof( Type ) );
	}

	
	VectorOfType2( const VectorOfType2& cM )
		:	m_unReAllocSizeMin1( cM.m_unReAllocSizeMin1 ),
			m_unSize( cM.m_unSize ),
			m_Elements(0)
	{

		_type_ind_ unMallocSize = RoundInteger( m_unSize );

		unMallocSize = (m_unReAllocSizeMin1 + 1) > unMallocSize ? (m_unReAllocSizeMin1 + 1) : unMallocSize;
				
		m_Elements = (Type*)realloc( m_Elements, unMallocSize * sizeof( Type ) );

		if( m_unSize )
		{
			memcpy( m_Elements, cM.m_Elements, m_unSize * sizeof( Type ) );
		}


	}


	~VectorOfType2()
	{
		free( m_Elements );
	}


	VectorOfType2& operator=( const VectorOfType2& aM )
	{

		m_unSize = aM.m_unSize;

		m_unReAllocSizeMin1 = aM.m_unReAllocSizeMin1 ;

		_type_ind_ unReAllocSize = RoundInteger( m_unSize );

		unReAllocSize = (1 + m_unReAllocSizeMin1) > unReAllocSize ? (1 + m_unReAllocSizeMin1) : unReAllocSize;

		m_Elements = (Type*)realloc( m_Elements, unReAllocSize * sizeof( Type ) );

		if( m_unSize )
		{
			memcpy( m_Elements, aM.m_Elements, m_unSize * sizeof( Type ) );
		}

		return *this;
	}


	const _type_ind_& ReAllocSizeMin1()const
	{
		return m_unReAllocSizeMin1;
	}


	inline const _type_ind_& size()const
	{
		return m_unSize;
	}


	/*
	 * This function must be changed
	 * Checking if realloc done succesfully or not
	 *
	 */
	void push_back( const Type& Element )
	{

		if( !( m_unSize & m_unReAllocSizeMin1 ) && m_unSize )
		{
			m_Elements = (Type*)realloc( m_Elements, (m_unSize + m_unReAllocSizeMin1 + 1) * sizeof( Type ) );
		}

		m_Elements[ m_unSize++ ] = Element;

	}


	void push_back( const Type*const& a_pElements, const _type_ind_& a_unAddSize )
	{


		if( a_unAddSize )
		{

			_type_ind_ unReallocated( ( 1 + m_unSize / (m_unReAllocSizeMin1+1) ) * (m_unReAllocSizeMin1+1) );
			_type_ind_ unNewSize = m_unSize + a_unAddSize ;

			if( unNewSize > unReallocated )
			{
				unReallocated = ( 1 + unNewSize / (m_unReAllocSizeMin1+1) ) * (m_unReAllocSizeMin1+1) ;
				m_Elements = (Type*)realloc( m_Elements, unReallocated * sizeof(Type) );
			}

			memcpy( m_Elements + m_unSize, a_pElements, a_unAddSize * sizeof(Type) );

			m_unSize = unNewSize ;

		}

		
	}
	
	
	void push_back( const VectorOfType2& aElements )
	{
		push_back( aElements.m_Elements, aElements.m_unSize );			
	}


	_type_ind_ AddAndGetIndex( const Type& Element )
	{


		if( !( m_unSize & m_unReAllocSizeMin1 ) && m_unSize )
		{
			m_Elements = (Type*)realloc( m_Elements, (m_unSize + m_unReAllocSizeMin1 + 1) * sizeof( Type ) );
		}

		m_Elements[ m_unSize ] = Element;

		return m_unSize++;

	}


	void Insert( const _type_ind_& Index, const Type& Element )
	{

		if( Index > m_unSize )
			return;

		if( !( m_unSize & m_unReAllocSizeMin1 ) && m_unSize )
		{
			m_Elements = (Type*)realloc( m_Elements, (m_unSize + m_unReAllocSizeMin1 + 1) * sizeof( Type ) );
		}


		if(Index < m_unSize)
			memmove( m_Elements + Index + 1, m_Elements + Index, (m_unSize++ - Index) * sizeof(Type) );
		else
			++m_unSize;

		m_Elements[ Index ] = Element;

	}


	bool RemoveElement( const _type_ind_& Index )
	{
		bool bRet;

		if( Index < m_unSize )
		{

			if( Index < --m_unSize )
			{
				memmove( m_Elements + Index, m_Elements + Index + 1, ( m_unSize - Index ) * sizeof( Type ) );
			}

			bRet = true;
			
			
		}
		else
		{
			bRet = false;
		}

		return bRet;
	}


	void RemoveLast( )
	{
		if( m_unSize )
		{
			--m_unSize;
		}
	}


	const Type& operator[]( const _type_ind_& Index )const
	{
		return m_Elements[ Index ];
	}


	Type& operator[]( const _type_ind_& Index )
	{
		return m_Elements[ Index ];
	}


	void Empty()
	{
		m_unSize = 0;
	}



	Type& GetLast()
	{
		return m_Elements[m_unSize - 1];
	}


	const Type& GetLast()const
	{
		return m_Elements[ m_unSize - 1 ];
	}
	

	void QSort( int (*fpCompare )(const void*, const void*) )
	{
		qsort( m_Elements, m_unSize, sizeof(Type), fpCompare );
	}


	Type* GetPtr()
	{
		return m_Elements;
	}


private:
	/*
	 * Members
	 *
	 */
	_type_ind_							m_unReAllocSizeMin1;
	_type_ind_							m_unSize;
	Type*								m_Elements;

};




#endif/* #ifndef __vectoroftype2_h__ */
