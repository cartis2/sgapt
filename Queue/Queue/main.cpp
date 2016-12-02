// Queue.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cCircularQueue.h"
#include "cQueueLL.h"
#include "cNiceQueue.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
jdaflkajdlfaksjadlkfajlskjlfaksjf;laskj
as;dfjasl;k;djf
asdkfljaslkdfja
sdjlskjs
skajas
a
a
a
a
a
// 	cCircularQueue q1;
// 	q1.Enqueue(1);
// 	q1.Enqueue(2);
// 	q1.Enqueue(3);
// 	q1.Enqueue(4);
// 	q1.Enqueue(5);
// 	q1.Enqueue(6);
// 	q1.Dequeue();
// 	q1.Print();
// 
// 	cQueueLL q2;
// 
// 	q2.Enqueue(1);
// 	q2.Enqueue(2);
// 	q2.Enqueue(3);
// 	q2.Enqueue(4);
// 	q2.Enqueue(5);
// 	q2.Enqueue(6);
// 	q2.Dequeue();
// 	q2.Print();

	cQueueLL q1;
	cNiceQueue q2;

	DWORD dwStart, dwFinish, dwQueue, dwNiceQueue;

	dwStart = GetTickCount();

	for (int i = 0; i < 500; i++)
	{
		for (int k = 0; k < 500; k++)
		{
			q1.Enqueue(i);
		}
		for (int k = 0; k < 500; k++)
		{
			cNode* pNode = q1.Dequeue();
			if(pNode)
				delete pNode;
		}
	}

	dwFinish = GetTickCount();
	dwQueue = dwFinish - dwStart;


	dwStart = dwFinish;

	for (int i = 0; i < 500; i++)
	{
		for (int k = 0; k < 500; k++)
		{
			q2.Enqueue(i);
		}
		for (int k = 0; k < 500; k++)
		{
			cNode* pNode = q2.Dequeue();
			if(pNode)
				delete pNode;
		}
	}

	dwFinish = GetTickCount();
	dwNiceQueue = dwFinish - dwStart;

	std::cout << dwQueue / (float)dwNiceQueue << std::endl;

	return 0;
}














