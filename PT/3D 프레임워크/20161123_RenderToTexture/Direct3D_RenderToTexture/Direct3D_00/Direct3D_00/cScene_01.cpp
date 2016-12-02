#include "stdafx.h"
#include "cScene_01.h"


cScene_01::cScene_01()
{
}


cScene_01::~cScene_01()
{
}

void cScene_01::Init()
{
	//정점 버퍼 만든다
	Device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,	//만들어질 정점 버퍼의 바이트 크기
		D3DUSAGE_WRITEONLY,		//만들어지는 정점 버퍼의 속성 플레그 일단 D3DUSAGE_WRITEONLY 가 접근이 빠름, 만약 후에 정점 버퍼에 대한 접근이 자주 일어난다면 D3DUSAGE_DYNAMIC 으로 바꿔줘라
		MYVERTEX::FVF,			//넣을 정점 버퍼의 FVF 정보
		D3DPOOL_DEFAULT,		//메모리풀 보관방식
		&this->vb,				//생성된 정점 버퍼 포인터
		NULL);					//그냥 널~

	LPMYVERTEX pVertices = NULL; //Lock 하고 얻어올 포인터 LPMYVERTEX 포인터로 받기 위함

	this->vb->Lock(
		0,		//실제 메모리위치에서 offsetbyute 0이면 처음부터
		0,		//Lock 할크기, 전체 락할꺼면 0
		(void**)&pVertices, //Lock하고 얻어올 포인터
		0		//Lock 플레그 일단 0
		);

	//포인터를 통해서 값을 쓴다~
	pVertices[0].pos = D3DXVECTOR3(0.f, 1.f, 0.f);
	pVertices[0].color = 0xff0000ff;
	pVertices[1].pos = D3DXVECTOR3(1.f, 0.f, 0.f);
	pVertices[1].color = 0xff00ff00;
	pVertices[2].pos = D3DXVECTOR3(-1.f, 0.f, 0.f);
	pVertices[2].color = 0xffff0000;

	//다 썼으면 락해제
	this->vb->Unlock();

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void cScene_01::Release()
{
	//정점 버퍼 해제
	SAFE_RELEASE(this->vb);
}

void cScene_01::Update(float timeDelta)
{

}

void cScene_01::Render()
{
	Device->SetStreamSource(0, this->vb, 0, sizeof(MYVERTEX));
	
	Device->SetFVF(MYVERTEX::FVF);
	//Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE); //이렇게 해도 됨.

	Device->DrawPrimitive(
		D3DPT_TRIANGLELIST, //삼각형으로 그리겠다
		0,					//0번째부터
		1);					//하나 그린다
}