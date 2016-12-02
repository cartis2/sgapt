#pragma once

#define QUEUE_SIZE 5

class cCircularQueue
{
private:
	int m_nFront;
	int m_nRear;
	int m_aData[QUEUE_SIZE];

public:
	cCircularQueue(void);
	~cCircularQueue(void);

	void Enqueue(int n);
	void Dequeue();
	void Print();
	bool IsFull();
	bool IsEmpty();
};

