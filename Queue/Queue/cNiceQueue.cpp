#include "StdAfx.h"
#include "cNiceQueue.h"
#include "cNode.h"

cNiceQueue::cNiceQueue(void)
{
}


cNiceQueue::~cNiceQueue(void)
{
}

void cNiceQueue::Enqueue( int n )
{
	cNode* pNode = m_DummyQueue.Dequeue();
	if (pNode)
	{
		cQueueLL::Enqueue(pNode);
	}
	else
	{
		cQueueLL::Enqueue(n);
	}
}

cNode* cNiceQueue::Dequeue()
{
	m_DummyQueue.Enqueue(cQueueLL::Dequeue());
	return NULL;
}
