#pragma once

class cNode;

class cQueueLL
{
protected:
	cNode* m_pFront;
	cNode* m_pRear;

public:
	cQueueLL(void);
	virtual ~cQueueLL(void);

	virtual void Enqueue(cNode* pNode);
	virtual void Enqueue(int n);
	virtual cNode* Dequeue();
	virtual void Print();
};

