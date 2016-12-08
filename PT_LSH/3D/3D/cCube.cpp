#include "StdAfx.h"
#include "cCube.h"
#include "cCamera.h"

cCube::cCube(void)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cCube::~cCube(void)
{
}

void cCube::Setup(D3DXCOLOR color, float size)
{
	float x, y, z;
	x = 1 * size;
	y = 1 * size;
	z = 1 * size;

	vecVertex.push_back(D3DXVECTOR3(-x, -y, -z));
	vecVertex.push_back(D3DXVECTOR3(-x,  y, -z));
	vecVertex.push_back(D3DXVECTOR3( x,  y, -z));
	vecVertex.push_back(D3DXVECTOR3( x, -y, -z));
	vecVertex.push_back(D3DXVECTOR3(-x, -y,  z));
	vecVertex.push_back(D3DXVECTOR3(-x,  y,  z));
	vecVertex.push_back(D3DXVECTOR3( x,  y,  z));
	vecVertex.push_back(D3DXVECTOR3( x, -y,  z));

	GetMaxMin();

	vector<DWORD> vecIndex;
	vecIndex.push_back(0); vecIndex.push_back(1); vecIndex.push_back(2);
	vecIndex.push_back(0); vecIndex.push_back(2); vecIndex.push_back(3);

	vecIndex.push_back(4); vecIndex.push_back(6); vecIndex.push_back(5);
	vecIndex.push_back(4); vecIndex.push_back(7); vecIndex.push_back(6);

	vecIndex.push_back(4); vecIndex.push_back(5); vecIndex.push_back(1);
	vecIndex.push_back(4); vecIndex.push_back(1); vecIndex.push_back(0);

	vecIndex.push_back(3); vecIndex.push_back(2); vecIndex.push_back(6);
	vecIndex.push_back(3); vecIndex.push_back(6); vecIndex.push_back(7);

	vecIndex.push_back(1); vecIndex.push_back(5); vecIndex.push_back(6);
	vecIndex.push_back(1); vecIndex.push_back(6); vecIndex.push_back(2);

	vecIndex.push_back(4); vecIndex.push_back(0); vecIndex.push_back(3);
	vecIndex.push_back(4); vecIndex.push_back(3); vecIndex.push_back(7);

	for (size_t i = 0; i < vecIndex.size(); ++i)
	{
		D3DXVECTOR3 p = vecVertex[vecIndex[i]];
		m_vecVertex.push_back(ST_PC_VERTEX(p, color));
	}
}

void cCube::Update(D3DXMATRIXA16* pWorld)
{
	GetMaxMin();

	if (pWorld)
		m_matWorldTM = *pWorld;
}

void cCube::Render()
{	
	// 와이어프레임 출력
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));

	// 기본 면으로 출력
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cCube::GetMaxMin()
{
	// world값 기준으로 정점값을 다시 구해준다.
	for (size_t i = 0; i < vecVertex.size(); ++i)
			D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], &m_matWorldTM);

	// Max
	BoxX = vecVertex[0].x; BoxY = vecVertex[0].y; BoxZ = vecVertex[0].z;
	for (size_t i = 1; i < vecVertex.size(); i++)
	{
		if (vecVertex[i].x > BoxX) BoxX = vecVertex[i].x;
		if (vecVertex[i].y > BoxY) BoxY = vecVertex[i].y;
		if (vecVertex[i].z > BoxZ) BoxZ = vecVertex[i].z;
	}
	vMax = D3DXVECTOR3(BoxX, BoxY, BoxZ);

	// Min
	BoxX = vecVertex[0].x; BoxY = vecVertex[0].y; BoxZ = vecVertex[0].z;
	for (size_t i = 1; i < vecVertex.size(); i++)
	{
		if (vecVertex[i].x < BoxX) BoxX = vecVertex[i].x;
		if (vecVertex[i].y < BoxY) BoxY = vecVertex[i].y;
		if (vecVertex[i].z < BoxZ) BoxZ = vecVertex[i].z;
	}
	vMin = D3DXVECTOR3(BoxX, BoxY, BoxZ);
}