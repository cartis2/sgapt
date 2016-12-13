#include "stdAfx.h"
#include "cCrtController.h"
#include "cOBB.h"

cCrtController::cCrtController(void)
	: m_vPosition(-8, 3.5, 0)
	//: m_vPosition(-10, 15, 0)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(0.2f)
	, m_fAngle(0.0f)
	, m_playerOBB(NULL)
{
}

cCrtController::~cCrtController(void)
{
	SAFE_DELETE(m_playerOBB);
	m_vecWall.clear();
}

void cCrtController::Setup()
{
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;

	m_pDefultFont = NULL;
	D3DXCreateFont(g_pD3DDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "굴림", &m_pDefultFont);

	m_playerOBB = new cOBB;
	m_playerOBB->Setup(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-1, -1, -1));

	color = RGB(255, 0, 255);

	SetWall();
}

void cCrtController::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) m_fAngle -= 0.1f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))  m_fAngle += 0.1f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &matR);	
	vPosition = m_vPosition;

	if (KEYMANAGER->isStayKeyDown(VK_UP))   vPosition = m_vPosition - (m_vDirection * m_fSpeed);
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) vPosition = m_vPosition + (m_vDirection * m_fSpeed);

	if (!GetHeight(vPosition.x, vPosition.y, vPosition.z))
	{
		m_vPosition = vPosition;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;

	D3DXMATRIXA16 matT2;
	D3DXMatrixTranslation(&matT2, m_vPosition.x + 0.5f, m_vPosition.y + 1.1f, m_vPosition.z + 0.5f);
	if (m_playerOBB) m_playerOBB->Update(&matT2);

	WallCollision();

	RayY[1].p = m_vPosition;
	RayY[1].c = RGB(0, 255, 0);

	RayX[0].p = m_vPosition;
	RayX[0].c = RGB(0, 0, 255);
	RayX[1].p = D3DXVECTOR3(m_vPosition.x - m_vDirection.x, m_vPosition.y - m_vDirection.y, m_vPosition.z - m_vDirection.z);
	RayX[1].c = RGB(0, 0, 255);

	if (KEYMANAGER->isOnceKeyDown('3')) m_vPosition =  D3DXVECTOR3(-1.26, 3.24, -17.34);

	// 종료 버튼
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostMessage(g_hWnd, WM_DESTROY, NULL, NULL);
}

bool cCrtController::GetHeight(IN float x, OUT float y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, y + 1.f, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float dist = 0.f;

	RayY[0].p = vRayPos;
	RayY[0].c = RGB(0, 255, 0);

	float u, v, d;
	// 바닥 박스 충돌
	u = 0.f; v = 0.f; d = 0.f;
	for (size_t i = 0; i < groundVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = groundVertex[i];
		D3DXVECTOR3 v1 = groundVertex[i + 1];
		D3DXVECTOR3 v2 = groundVertex[i + 2];

		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			return false;
		}
	}

	// 맵 충돌
	u = 0.f; v = 0.f; d = 0.f;
	for (size_t i = 0; i < mapVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = mapVertex[i];
		D3DXVECTOR3 v1 = mapVertex[i + 1];
		D3DXVECTOR3 v2 = mapVertex[i + 2];
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			dist = vRayPos.y - d;
			if (EPSILON < dist && dist < vRayPos.y)
			{
				m_vPosition.x = vPosition.x;
				m_vPosition.z = vPosition.z;
				m_vPosition.y = dist;
			}
			return true;
		}
	}
}

void cCrtController::SetMapVertex(vector<D3DXVECTOR3> vertex)
{
	for (size_t i = 0; i < vertex.size(); i++)
		mapVertex.push_back(vertex[i]);
}

void cCrtController::SetGroundVertex(vector<D3DXVECTOR3> vertex)
{
	for (size_t i = 0; i < vertex.size(); i++)
		groundVertex.push_back(vertex[i]);
}

void cCrtController::SetWallVertex(vector<D3DXVECTOR3> vertex)
{
	for (size_t i = 0; i < vertex.size(); i++) 
		wallVertex.push_back(vertex[i]);
}

void cCrtController::Render()
{
	// ====================player 좌표==================
	char szTemp[128];
	sprintf_s(szTemp, "%.2f, %.2f, %.2f", m_vPosition.x, m_vPosition.y, m_vPosition.z);
	PrintText(szTemp, 10, 10, 0xffffff00);

	// ====================Ray==================
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &RayY[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &RayX[0], sizeof(ST_PC_VERTEX));

	// ====================player==================
	m_playerOBB->DebugRender(color);

	// ====================벽면==================
	for (size_t i = 0; i < m_vecWall.size(); i++)
		m_vecWall[i].DebugRender(D3DXCOLOR(RGB(0, 255, 0)));
}

void cCrtController::PrintText(string str, int x, int y, DWORD color)
{
	//출력영역
	RECT rcTextArea = { x, y, 0, 0 };

	m_pDefultFont->DrawTextA(NULL, str.c_str(),	 -1,
		&rcTextArea, DT_LEFT | DT_NOCLIP, color);
}

void cCrtController::SetWall()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	cOBB Wall_1;
	Wall_1.Setup(D3DXVECTOR3(20.5, 7, -1.20), D3DXVECTOR3(18.5, 3.7, -1.15));
	Wall_1.Update(&mat);
	m_vecWall.push_back(Wall_1);

	cOBB Wall_2;
	Wall_2.Setup(D3DXVECTOR3(18.4, 7, -1.15), D3DXVECTOR3(16.2, 3.7, -1.10));
	Wall_2.Update(&mat);
	m_vecWall.push_back(Wall_2);

	cOBB Wall_3;
	Wall_3.Setup(D3DXVECTOR3(16.2, 7, -1.10), D3DXVECTOR3(13.9, 3.7, -1.04));
	Wall_3.Update(&mat);
	m_vecWall.push_back(Wall_3);

	cOBB Wall_4;
	Wall_4.Setup(D3DXVECTOR3(13.9, 7, -1.04), D3DXVECTOR3(11.9, 3.7, -0.99));
	Wall_4.Update(&mat);
	m_vecWall.push_back(Wall_4);

	cOBB Wall_5;
	Wall_5.Setup(D3DXVECTOR3(11.9, 7, -0.99), D3DXVECTOR3(9.9, 3.6, -0.93));
	Wall_5.Update(&mat);
	m_vecWall.push_back(Wall_5);

	cOBB Wall_6;
	Wall_6.Setup(D3DXVECTOR3(9.9, 7, -0.93), D3DXVECTOR3(7.9, 3.6, -0.87));
	Wall_6.Update(&mat);
	m_vecWall.push_back(Wall_6);

	cOBB Wall_7;
	Wall_7.Setup(D3DXVECTOR3(7.9, 7, -0.87), D3DXVECTOR3(5.9, 3.6, -0.81));
	Wall_7.Update(&mat);
	m_vecWall.push_back(Wall_7);

	cOBB Wall_8;
	Wall_8.Setup(D3DXVECTOR3(5.9, 7, -0.81), D3DXVECTOR3(3.9, 3.6, -0.75));
	Wall_8.Update(&mat);
	m_vecWall.push_back(Wall_8);

	cOBB Wall_9;
	Wall_9.Setup(D3DXVECTOR3(3.9, 7, -0.75), D3DXVECTOR3(1.6, 3.6, -0.69));
	Wall_9.Update(&mat);
	m_vecWall.push_back(Wall_9);

	cOBB Wall_10;
	Wall_10.Setup(D3DXVECTOR3(1.6, 6.5, -0.69), D3DXVECTOR3(1.5, 3.5, -4.8));
	Wall_10.Update(&mat);
	m_vecWall.push_back(Wall_10);

	cOBB Wall_11;
	Wall_11.Setup(D3DXVECTOR3(1.5, 6.5, -4.7), D3DXVECTOR3(-1.5, 3.5, -4.65));
	Wall_11.Update(&mat);
	m_vecWall.push_back(Wall_11);

	cOBB Wall_12;
	Wall_12.Setup(D3DXVECTOR3(-1.5, 6.5, -4.63), D3DXVECTOR3(-3.5, 3.5, -4.58));
	Wall_12.Update(&mat);
	m_vecWall.push_back(Wall_12);

	cOBB Wall_13;
	Wall_13.Setup(D3DXVECTOR3(-3.5, 6.5, -4.58), D3DXVECTOR3(-5.5, 3.5, -4.53));
	Wall_13.Update(&mat);
	m_vecWall.push_back(Wall_13);

	cOBB Wall_14;
	Wall_14.Setup(D3DXVECTOR3(-5.5, 6.5, -4.53), D3DXVECTOR3(-7.5, 3.5, -4.47));
	Wall_14.Update(&mat);
	m_vecWall.push_back(Wall_14);

	cOBB Wall_15;
	Wall_15.Setup(D3DXVECTOR3(-7.5, 6.5, -4.47), D3DXVECTOR3(-9.5, 3.5, -4.42));
	Wall_15.Update(&mat);
	m_vecWall.push_back(Wall_15);

	cOBB Wall_16;
	Wall_16.Setup(D3DXVECTOR3(-9.5, 6.5, -4.25), D3DXVECTOR3(-11.5, 3.5, -4.7));
	Wall_16.Update(&mat);
	m_vecWall.push_back(Wall_16);

	cOBB Wall_17;
	Wall_17.Setup(D3DXVECTOR3(-11.5, 6.5, -4.3), D3DXVECTOR3(-13.5, 3.5, -4.65));
	Wall_17.Update(&mat);
	m_vecWall.push_back(Wall_17);

}

void cCrtController::WallCollision()
{
	for (size_t i = 0; i < m_vecWall.size(); i++)
	{
		if (m_playerOBB->IsCollision(m_playerOBB, &m_vecWall[i]))
		{
			color = RGB(0, 0, 0);
			return;
		}
		else
			color = RGB(255, 0, 255);
	}
}