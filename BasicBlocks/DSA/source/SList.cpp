/***********************************************************************
* File: SList.cpp
* Description: Implements the SList singly-linked list class for the DSA library.
***********************************************************************/
#include <stdexcept>
#include <iostream> 
#include "SList.h"

 
/***********************************************************************/
/// <b>Function:	SList</b>
///
///	\param			NONE
///
/// \remarks		Standard Constructor	
///
/***********************************************************************/
SList::SList()
{
	m_pListHead = NULL;
	m_iCount = 0;
}

/***********************************************************************/
/// <b>Function:	~SList</b>
///
///	\param			NONE
///
/// \remarks	    Standard Destructor
///
/***********************************************************************/
SList::~SList()
{
	psNode tempNode;

	if(NULL == m_pListHead)
	{
   		return;
	}
	else
	{
		while (m_pListHead != nullptr)
        {
            psNode tempNode = m_pListHead->m_pNext;
            delete m_pListHead;
            m_pListHead = tempNode;
        }

        m_iCount = 0; // reset count
	}
}

/***********************************************************************/
/// <b>Function:	AddElement</b>
///
/// \param			iVal	(in)
///
/// \return			BOOL 
///
/// \remarks	    Adds an element to the end of the list.
///
/***********************************************************************/
bool SList::AddElement(int iVal)
{
	bool bRetval = false;
	/// Add at first
	///
	psNode pTempNode = nullptr;
    psNode psCountNode =nullptr;

   if( m_pListHead == nullptr )
   {
		m_pListHead = new sNode();
		if(m_pListHead)
		{
			bRetval = true;
			m_pListHead->m_iVal = iVal;
			m_pListHead->m_pNext = nullptr;
			m_iCount++;
			return bRetval;
		}
		else
		{
			return bRetval;
		}
   }
   else
   {
   		psCountNode = m_pListHead;

		while( psCountNode->m_pNext != nullptr )
		{
      		psCountNode = psCountNode->m_pNext;
		}

		pTempNode = new sNode();

		if(pTempNode)
		{
			bRetval = true;
			pTempNode->m_iVal = iVal;
			pTempNode->m_pNext = nullptr;
			psCountNode->m_pNext = pTempNode;
			m_iCount ++;
			return bRetval;
		}
		else
		{
			return bRetval;
		}
			
   }

}

/***********************************************************************/
/// <b>Function:	GetElementAt</b>
///
/// \param			iCount	(in)
///
/// \return			pNode 
///
/// \remarks	    Returns the node at the specified index in the list.
///
/***********************************************************************/
psNode SList::GetElementAt(int iCount)
{
	int iCnt = 0;

	if(iCount == 0)
	{
		if(m_pListHead)
		{
			return m_pListHead;
		}
		else
		{
			std::cout<<"ERROR::Create List First";
			return nullptr;
		}
	}

	if(iCount >m_iCount)
	{
		
		return nullptr;
	}
	else
	{
		if(nullptr == m_pListHead)
		{
			std::cout<<"ERROR::Create List First";
			return nullptr;
		}
		else
		{
			psNode pTempNode = m_pListHead;
			while (iCnt < iCount)
			{
				pTempNode = pTempNode->m_pNext;
				iCnt++;
			}
			if(pTempNode)
			{
				return pTempNode;
			}
			else
			{
				return nullptr;
			}

		}
		
	}
}

/***********************************************************************/
/// <b>Function:	GetLastElement</b>
///
///	\param			NONE
///
/// \return			pNode 
///
/// \remarks		Returns the last node in the list.
///
/***********************************************************************/
psNode SList::GetLastElement()
{
	if(nullptr == m_pListHead)
	{
		std::cout<<"ERROR::Create List First";
		return nullptr;
	}
	else
	{
		psNode pTempNode = m_pListHead;
		while (pTempNode->m_pNext != nullptr)
		{
			pTempNode = pTempNode->m_pNext;
		}
		if(pTempNode)
		{
			return pTempNode;
		}
		else
		{
			return nullptr;
		}

	}	
}


/***********************************************************************/
/// <b>Function:	DeleteElement</b>
///
///	\param			NONE
///
/// \return			bool 
///
/// \remarks	    Deletes the last element from the list.
///
/***********************************************************************/
bool SList::DeleteElement()
{
	bool bRetval = false;
	if(nullptr == m_pListHead)
	{
		std::cout<<"ERROR::List is Empty, Cannot Delete";
		return bRetval;
	}
	else
	{
		psNode pTempNode = m_pListHead;
		psNode pIndexNode = pTempNode->m_pNext;

		if(nullptr == pIndexNode)
		{
			bRetval = true;
			delete pTempNode;
			pTempNode = nullptr;
			m_iCount --;
			return bRetval;
		}
		else
		{
			while (pIndexNode->m_pNext != nullptr) 
			{
				pIndexNode = pIndexNode->m_pNext;
				pTempNode = pTempNode->m_pNext;
			}

			if(pIndexNode)
			{
				bRetval = true;
				pTempNode->m_pNext = nullptr;
				delete pIndexNode;
				pIndexNode = nullptr;
				m_iCount--;
				return bRetval;
			}
			else
			{
				return bRetval;
			}
			
		}
		
	}
}

/***********************************************************************/
/// <b>Function:	Display</b>
///
///	\param			NONE
///
/// \return			bool 
///
/// \remarks	    Displays the contents of the list.
///
/***********************************************************************/
bool SList::Display()
{
	int iCnt = 0;
	psNode pCountNode = m_pListHead;
    
	if(nullptr == pCountNode)
	{
		std::cout<<"Now the List is empty\n\n";
		return 0;

	}
	else
	{
		do 
		{
			std::cout<< "E"<<iCnt<<"="<<pCountNode->m_iVal<<"\t";
			pCountNode = pCountNode->m_pNext;
			iCnt++;

		} while(pCountNode != nullptr);

		std::cout<<"\n\n";
		return 1;
	}
	
}


/***********************************************************************/
/// <b>Function:	AddElementAfter</b>
///
/// \param			iNodecount	(in)
///
/// \param			iVal	(in)
///
/// \return			BOOL 
///
/// \remarks	    Inserts a new element after the specified index in the list.
///
/***********************************************************************/
bool SList::AddElementAfter(int iNodepos, const int iVal)
{
	bool bRetval = false;
	if(m_pListHead)
	{
		if(iNodepos > (m_iCount-1))
		{
			std::cout<<"ERROR: Cannot Insert an element here";
			return false;
		}
		else
		{
			psNode pNewnode = new sNode();
			if(pNewnode)
			{
				psNode pTempNode = GetElementAt(iNodepos);

				if(pTempNode)
				{
					bRetval = true;
					pNewnode->m_pNext = pTempNode->m_pNext;
					pTempNode->m_pNext = pNewnode;
					pNewnode->m_iVal = iVal;
					m_iCount++;
					return bRetval;
				}
				else
				{
					return bRetval;
				}
			}
			else
			{
				return bRetval;
			}
		}
	}
	else
	{
		std::cout<<"ERROR: List is not created yet!";
		return bRetval;
	}
}
