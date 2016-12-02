#pragma once
#include "cQueueLL.h"

class cNiceQueue : public cQueueLL
{
protected:
	cQueueLL m_DummyQueue;

public:
	cNiceQueue(void);
	virtual ~cNiceQueue(void);

	virtual void Enqueue(int n) override;
	virtual cNode* Dequeue() override;
};

