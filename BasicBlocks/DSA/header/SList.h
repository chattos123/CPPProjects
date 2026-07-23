/***********************************************************************
* File: SList.h
* Description: Declares the SList class for a singly-linked list in the DSA library.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

struct tagNode {
    int m_iVal;
    tagNode* m_pNext;
};

using sNode = tagNode;
using psNode = tagNode*;

/***********************************************************************
* Class: SList
*
* Purpose: Implements a simple singly-linked list with insertion,
*          deletion, traversal, and display operations.
***********************************************************************/
class DSALIB_API SList
{
private:
	psNode m_pListHead;
	int m_iCount;
public:
	
	////////////////////////////////////////////////////////////////////////
	////////////	Standard constructor & destructor	////////////////////
	////////////////////////////////////////////////////////////////////////

	/// Constructor
	///
	SList();
	/// Destuctor
	///
	~SList();

	////////////////////////////////////////////////////////////////////////
	////////////	General Inline funtions	////////////////////////////////
	////////////////////////////////////////////////////////////////////////


	/***********************************************************************/
	/// <b>Function:	IsEmpty</b>
	///
	///	\param			NONE
	///
	/// \return			bool 
	///
	/// \remarks		Checks whether the list is empty.	
	///
	/***********************************************************************/
	inline bool IsEmpty()
	{
		return (m_pListHead == nullptr);
	}
	
	/***********************************************************************/
	/// <b>Function:	GetLength</b>
	///
	///	\param			NONE
	///
	/// \return			int 
	///
	/// \remarks		Returns the number of elements in the list.
	///
	/***********************************************************************/
	inline int GetLength()
	{
		return m_iCount;
	}

	////////////////////////////////////////////////////////////////////////
	////////////	General Member funtions	////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	bool AddElement(int iVal);

	psNode GetElementAt(int iCount=0);

	psNode GetLastElement();

	bool DeleteElement();

	bool Display();

	bool AddElementAfter(int iNodepos, const int iVal);
};