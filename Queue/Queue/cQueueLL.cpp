#include "StdAfx.h"
#include "cQueueLL.h"
#include "cNode.h"

cQueueLL::cQueueLL(void)
	: m_pFront(NULL)
	, m_pRear(NULL)
{
}

cQueueLL::~cQueueLL(void)
{
	if (m_pFront)
	{
		m_pFront->Destroy();
	}
}

void cQueueLL::Enqueue( cNode* pNode )
{
	pNode->m_pNext = NULL;
	if (m_pFront == NULL)
	{
		m_pFront = m_pRear = pNode;
	}
	else
	{
		m_pRear->m_pNext = pNode;
		m_pRear = pNode;
	}
}

void cQueueLL::Enqueue( int n )
{
	Enqueue(new cNode(n));
}

cNode* cQueueLL::Dequeue()
{
	if(m_pFront == NULL) return NULL;

	cNode* pTemp = m_pFront;
	m_pFront = m_pFront->m_pNext;

	if(m_pFront == NULL)
		m_pRear = NULL;
	
	return pTemp;
}

void cQueueLL::Print()
{
	if(m_pFront)
		m_pFront->Print();
}
