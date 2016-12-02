#include "StdAfx.h"
#include "cCircularQueue.h"


<<<<<<< HEAD
lkdlksjaflkas

sldkfjsadlkfjsal;

alksjdflsakjdflk
=======
sdagisdg
sdikgnagks
nskgndka
nkssdgnka
nssdng
>>>>>>> 84cc5abf9ab664e2f6f41c13e62cf4ec87241ab8

cCircularQueue::cCircularQueue(void)
	: m_nFront(0)
	, m_nRear(0)
{
}

cCircularQueue::~cCircularQueue(void)
{
}

void cCircularQueue::Enqueue( int n )
{
	if(IsFull()) return;
	m_aData[m_nRear] = n;
	m_nRear = (m_nRear + 1) % QUEUE_SIZE;
}

void cCircularQueue::Dequeue()
{
	if(IsEmpty()) return;
	m_nFront = (m_nFront + 1) % QUEUE_SIZE;
}

void cCircularQueue::Print()
{
	for (int i = m_nFront; i != m_nRear; i = (i + 1) % QUEUE_SIZE)
	{
		std::cout << m_aData[i] << std::endl;
	}
}

bool cCircularQueue::IsFull()
{
	return (m_nRear + 1) % QUEUE_SIZE == m_nFront;
}

bool cCircularQueue::IsEmpty()
{
	return m_nFront == m_nRear;
}
