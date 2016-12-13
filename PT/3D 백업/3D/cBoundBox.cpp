#include "stdafx.h"
#include "cBoundBox.h"

cBoundBox::cBoundBox()
{
}

cBoundBox::~cBoundBox()
{
}

void cBoundBox::GetBox(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// size크기로 정점 생성
	vector<D3DXVECTOR3> vecVertex;
	vecVertex.push_back(D3DXVECTOR3(-size.x, -size.y, -size.z));
	vecVertex.push_back(D3DXVECTOR3(-size.x,  size.y, -size.z));
	vecVertex.push_back(D3DXVECTOR3( size.x,  size.y, -size.z));
	vecVertex.push_back(D3DXVECTOR3( size.x, -size.y, -size.z));
	vecVertex.push_back(D3DXVECTOR3(-size.x, -size.y,  size.z));
	vecVertex.push_back(D3DXVECTOR3(-size.x,  size.y,  size.z));
	vecVertex.push_back(D3DXVECTOR3( size.x,  size.y,  size.z));
	vecVertex.push_back(D3DXVECTOR3( size.x, -size.y,  size.z));

	// box 위치값 행렬 구해주자.
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	// box 정점 변경
	for (size_t i = 0; i < vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], &matT);

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

	D3DXCOLOR color = RGB(0, 255, 0);
	for (size_t i = 0; i < vecIndex.size(); ++i)
	{
		D3DXVECTOR3 p = vecVertex[vecIndex[i]];
		BoundVertex.push_back(p);
		m_vecVertex.push_back(ST_PC_VERTEX(p, color));
	}
}

void cBoundBox::Render()
{
	// 그려주는것은 월드행렬
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);

	g_pD3DDevice->LightEnable(0, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}