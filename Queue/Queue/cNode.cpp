#include "StdAfx.h"
#include "cNode.h"


cNode::cNode(void)
	: m_nData(0)
	, m_pNext(NULL)
{
}

cNode::cNode( int n, cNode* pNext /*= NULL*/ )
	: m_nData(n)
	, m_pNext(pNext)
{

}


cNode::~cNode(void)
{
}

void cNode::Insert( int n )
{
	if (m_pNext)
	{
		m_pNext->Insert(n);
	}
	else
	{
		m_pNext = new cNode(n);
	}
}

void cNode::Print()
{
	std::cout << m_nData << std::endl;
	if (m_pNext)
	{
		m_pNext->Print();
	}
}

void cNode::Delete( int n, cNode** ppThis )
{
	if (m_nData == n)
	{
		*ppThis = m_pNext;
		delete this;
	}
	else if (m_pNext)
	{
		m_pNext->Delete(n, &m_pNext);
	}
}

void cNode::Reverse( cNode* pPrev )
{
	if (m_pNext)
	{
		m_pNext->Reverse(this);
	}
	m_pNext = pPrev;
}

cNode* cNode::GetTail()
{
	if (m_pNext)
	{
		return m_pNext->GetTail();
	}
	return this;
}

void cNode::Destroy()
{
	if (m_pNext)
	{
		m_pNext->Destroy();
	}
	delete this;
}
