#include "stdafx.h"
#include "cScene_02.h"


cScene_02::cScene_02()
{
}


cScene_02::~cScene_02()
{
}

void cScene_02::Init()
{
	//큐브 생성
	this->CreateCube();

	//회전량은 없다.
	this->forward = D3DXVECTOR3(0, 1, 0);
	this->up = D3DXVECTOR3(0, 0, -1);
	this->right = D3DXVECTOR3(1, 0, 0);

	//뷰행렬을 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3 lookAtPos(0, 0, 0);		//0, 0, 0,  위치를 본다.
	D3DXVECTOR3 eyePos(1, 3, -5);		//눈의 위치는 0, 1, -10 이다.
	D3DXVECTOR3 up(0, 1, 0);				//상방기준은 월드 위다.

	D3DXMatrixLookAtLH(
		&matView,			//얻어올 뷰행렬 
		&eyePos,			//눈위치 벡터
		&lookAtPos,			//바라볼 위치
		&up					//상방 기준 ( 완전 정확하지 않아도된다 )
		);
	//뷰행렬 셋팅
	Device->SetTransform(D3DTS_VIEW, &matView);


	//투영행렬 준비
	D3DXMATRIXA16 matProjection;
	D3DXMatrixPerspectiveFovLH(
		&matProjection,
		60.0f * ONE_RAD,		//화각 ( 60.0 도 )
		static_cast<float>(WINSIZE_X) / static_cast<float>(WINSIZE_Y),		//화면 종횡비,
		0.01f,					//근거리 평면 거리 ( 이값이 0 이면 뎁스 꼬인다 0 으로 주지말아라 )
		100.0f);					//원거리 평명 거리
	//투영행렬 셋팅
	Device->SetTransform(D3DTS_PROJECTION, &matProjection);


	//정점의 컬러 정보를 출력하기 위해서는 Device 의 기본 라이팅 
	//기능을 해재해야 한다
	//당분간 라이팅을 사용할일이 없으니 라이팅을 끄자.
	Device->SetRenderState(
		D3DRS_LIGHTING,			//뭘셋팅할꺼니?
		FALSE					//셋팅값은 어떻게 되니?
		);
}

void cScene_02::Release()
{
	SAFE_RELEASE(this->vb);
	SAFE_RELEASE(this->ib);
}

void cScene_02::Update(float timeDelta)
{
	if (KEY_MGR->IsStayDown(VK_LSHIFT))
	{
		if (KEY_MGR->IsStayDown('A'))
			this->RotateSelfYaw(-90.0f * ONE_RAD * timeDelta);
		else if (KEY_MGR->IsStayDown('D'))
			this->RotateSelfYaw(90.0f * ONE_RAD * timeDelta);

		if (KEY_MGR->IsStayDown('W'))
			this->RotateSelfPitch(-90.0f * ONE_RAD * timeDelta);
		else if (KEY_MGR->IsStayDown('S'))
			this->RotateSelfPitch(90.0f * ONE_RAD * timeDelta);

		if (KEY_MGR->IsStayDown('Q'))
			this->RotateSelfRoll(90.0f * ONE_RAD * timeDelta);

		else if (KEY_MGR->IsStayDown('E'))
			this->RotateSelfRoll(-90.0f  * ONE_RAD * timeDelta);
	}
	else
	{
		if (KEY_MGR->IsStayDown('A'))
			this->RotateWorldYaw(-90.0f * ONE_RAD * timeDelta);
		else if (KEY_MGR->IsStayDown('D'))
			this->RotateWorldYaw(90.0f * ONE_RAD * timeDelta);

		if (KEY_MGR->IsStayDown('W'))
			this->RotateWorldPitch(-90.0f * ONE_RAD * timeDelta);
		else if (KEY_MGR->IsStayDown('S'))
			this->RotateWorldPitch(90.0f * ONE_RAD * timeDelta);

		if (KEY_MGR->IsStayDown('Q'))
			this->RotateWorldRoll(90.0f * ONE_RAD * timeDelta);

		else if (KEY_MGR->IsStayDown('E'))
			this->RotateWorldRoll(-90.0f  * ONE_RAD * timeDelta);
	}

	matWorld._11 = right.x;		
	matWorld._12 = right.y;		
	matWorld._13 = right.z;		
	matWorld._14 = 0;
	
	matWorld._21 = up.x;		
	matWorld._22 = up.y;		
	matWorld._23 = up.z;		
	matWorld._24 = 0;
	
	matWorld._31 = forward.x;	
	matWorld._32 = forward.y;	
	matWorld._33 = forward.z;	
	matWorld._34 = 0;
	
	matWorld._41 = 0;			
	matWorld._42 = 0;			
	matWorld._43 = 0;			
	matWorld._44 = 1;

}


void cScene_02::Render()
{
	//큐브 월드 행렬 셋팅
	Device->SetTransform(D3DTS_WORLD, &matWorld);

	//스트림소스 셋팅
	Device->SetStreamSource(0, this->vb, 0, sizeof(MYVERTEX));

	//인덱스 버퍼 셋팅
	Device->SetIndices(this->ib);

	//지금그리는 정점에 대한 정점 정보 FVF 플레그 값을 넣어준다. 
	//Device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
	Device->SetFVF(MYVERTEX::FVF);

	//SetStreamSource 셋팅된 정점버퍼와 인덱스 버의 내용으로 그린다.
	Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,		//시작 버텍스배열 인덱스 
		0,
		24,		//정점 갯수 
		0,		//시작 인덱스배열 인덱스
		12		//그리는 개채수 삼각형이니깐 12 개
		);
}

void cScene_02::RotateSelfYaw(float angle)
{
	//자신의 up축을 기준으로 한 회전
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &up, angle);

	//forward 만 회전
	D3DXVec3TransformNormal(&forward, &forward, &matRot);

	//right 는 외적으로 구하자
	D3DXVec3Cross(&right, &up, &forward);

	//외적 결과는 정규화 해주는 센스
	D3DXVec3Normalize(&right, &right);
}

void cScene_02::RotateSelfPitch(float angle)
{

}

void cScene_02::RotateSelfRoll(float angle)
{

}

void cScene_02::RotateWorldYaw(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, angle);

	D3DXVec3TransformNormal(&this->right, &this->right, &matRot);
	D3DXVec3TransformNormal(&this->up, &this->up, &matRot);
	D3DXVec3TransformNormal(&this->forward, &this->forward, &matRot);
}

void cScene_02::RotateWorldPitch(float angle)
{

}

void cScene_02::RotateWorldRoll(float angle)
{

}


void cScene_02::CreateCube()
{
	//
	// 정점 버퍼 생성
	//
	Device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 24,
		D3DUSAGE_WRITEONLY,
		MYVERTEX::FVF,
		D3DPOOL_DEFAULT,		//저장될 메모리 풀 설정
		&this->vb,
		NULL);

	//저장될 메모리풀
	//D3DPOOL_DEFAULT			//정점버퍼의 메모리는 시스템사양에 맞춰 알아서 저장이되는데 보통은 비디오 카드메모리에 저장이된다.
	//D3DPOOL_MANAGED			//정점버퍼의 메모리는 시스템의 메모리영역에 저장이되고 비디오카드 메모리를 사용한다면 비디오카드 메모리에도 저장이된다, 즉 버퍼의 원본내용이 System 메모리에 저장이된 상태에서 비디오카드 메모리에 그거와 똑같은 사본을 만들어쓰는 방식인데... 이는 Device 가 해제 되어도 버퍼의 내용을 다시 복구할 수 있는 여지가 있다.


	//쿼드 플랜 정점
	MYVERTEX quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);


	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, -90.0f * ONE_RAD);


	//정점 배열준비
	MYVERTEX vertices[24];

	//앞면 
	memcpy(vertices, quad, sizeof(MYVERTEX) * 4);
	vertices[0].color = 0xff000080;
	vertices[1].color = 0xff000080;
	vertices[2].color = 0xff000080;
	vertices[3].color = 0xff000080;


	//돌려
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);

	//우측면 복사
	memcpy(vertices + 4, quad, sizeof(MYVERTEX) * 4);
	vertices[4].color = 0xffff0000;
	vertices[5].color = 0xffff0000;
	vertices[6].color = 0xffff0000;
	vertices[7].color = 0xffff0000;


	//돌려
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);

	//뒷면 복사
	memcpy(vertices + 8, quad, sizeof(MYVERTEX) * 4);
	vertices[8].color = 0xff0000ff;
	vertices[9].color = 0xff0000ff;
	vertices[10].color = 0xff0000ff;
	vertices[11].color = 0xff0000ff;


	//돌려
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);

	//좌측면 복사
	memcpy(vertices + 12, quad, sizeof(MYVERTEX) * 4);
	vertices[12].color = 0xff800000;
	vertices[13].color = 0xff800000;
	vertices[14].color = 0xff800000;
	vertices[15].color = 0xff800000;



	D3DXMatrixRotationZ(&matRot, -90.0f * ONE_RAD);

	//돌려
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);

	//윗면 복사
	memcpy(vertices + 16, quad, sizeof(MYVERTEX) * 4);
	vertices[16].color = 0xff00ff00;
	vertices[17].color = 0xff00ff00;
	vertices[18].color = 0xff00ff00;
	vertices[19].color = 0xff00ff00;


	D3DXMatrixRotationZ(&matRot, -180.0f * ONE_RAD);

	//돌려
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);

	//아랫면 복사
	memcpy(vertices + 20, quad, sizeof(MYVERTEX) * 4);
	vertices[20].color = 0xff008000;
	vertices[21].color = 0xff008000;
	vertices[22].color = 0xff008000;
	vertices[23].color = 0xff008000;


	//버퍼 Lock
	void* pVertices = NULL;
	this->vb->Lock(0, 0, &pVertices, 0);

	//얻어온 포인터에 정점정보 메모리 복사 
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 24);

	this->vb->Unlock();



	//
	// 인덱스 버퍼 생성
	//

	Device->CreateIndexBuffer(
		sizeof(WORD) * 36,		//Cube 는 36 개의 인덱스 정보가 필요,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,				//WORD 형인덱스는 2byte 이니 16 비트인덱스이다, DWORD 로 하면 4byte 니 32 비트 인덱스가 되어야 한다.
		D3DPOOL_DEFAULT,
		&this->ib,					//얻어올 인덱스버퍼 포인터
		NULL);

	//		5--------6
	//     /|       /|
	//    4--------7 |
	//    | |      | | 
	//    | 1------| 2
	//    |/       |/
	//    0--------3

	//인덱스 정보
	WORD indices[36];

	for (int i = 0; i < 6; i++)
	{
		//정점 스타트 인덱스
		WORD vertexIndex = i * 4;

		//인덱스 배열 스타트 인덱스
		WORD indicexIndex = i * 6;

		indices[indicexIndex + 0] = vertexIndex + 0;
		indices[indicexIndex + 1] = vertexIndex + 1;
		indices[indicexIndex + 2] = vertexIndex + 2;
		indices[indicexIndex + 3] = vertexIndex + 0;
		indices[indicexIndex + 4] = vertexIndex + 2;
		indices[indicexIndex + 5] = vertexIndex + 3;
	}

	//익덱스벙보 Lock
	void* pIndices = NULL;
	this->ib->Lock(0, 0, &pIndices, 0);

	memcpy(pIndices, indices, sizeof(WORD) * 36);

	this->ib->Unlock();

}