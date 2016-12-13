#include "stdafx.h"
#include "cMap.h"

#include "cCamera.h"
#include "cCrtController.h"
#include "cSkinnedMesh.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

#include "cBoundBox.h"

cMap::cMap()
	: m_pCamera(NULL)
	, m_pControl(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pMapMesh(NULL)
{
}

cMap::~cMap()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pControl);
	SAFE_DELETE(m_pSkinnedMesh);

	SAFE_RELEASE(m_pMapMesh);
	for each (auto p in m_vecMtlTex) SAFE_RELEASE(p);
	for each (auto p in m_pGroundBox) SAFE_DELETE(p);
}

void cMap::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pControl = new cCrtController;

	m_pSkinnedMesh = new cSkinnedMesh("Zealot/", "Zealot.X");
	m_pSkinnedMesh->SetAnimationIndex(4);
	m_pSkinnedMesh->SetRandomTrackPosition();
	m_pSkinnedMesh->SetPosition(D3DXVECTOR3(0, 0, 0));

	D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixIdentity(&mat);
	mat = matS;
	
	vector<D3DXVECTOR3> tempVertex;
	cObjLoader objloader;
	m_pMapMesh = objloader.Load("./Test/map.obj", m_vecMtlTex, tempVertex, &mat);
	m_pControl->Setup();
	m_pControl->SetMapVertex(tempVertex);

	wireframe = false;

	BoxSetup();
	SetLight();
}

void cMap::Update()
{
	if (m_pControl) m_pControl->Update();
	if (m_pCamera) m_pCamera->Update(m_pControl->GetPosition());

	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN) ||
		KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (m_pSkinnedMesh)
			m_pSkinnedMesh->SetAnimationIndex(3);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN) ||
		KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (m_pSkinnedMesh)
			m_pSkinnedMesh->SetAnimationIndex(4);
	}
		
	if (KEYMANAGER->isOnceKeyDown('1')) wireframe = false; // 면으로 보인다.
	if (KEYMANAGER->isOnceKeyDown('2')) wireframe = true;  // 선으로 보인다.
}

void cMap::Render()
{
	if (m_pSkinnedMesh) m_pSkinnedMesh->UpdateAndRender(m_pControl->GetWorldTM());

	// 와이어프레임 출력
	if (wireframe)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		if (m_pControl) m_pControl->Render();
		for (size_t i = 0; i < m_pGroundBox.size(); i++)
			m_pGroundBox[i]->Render();
	}


	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	SetLight();
	for (int i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMapMesh->DrawSubset(i);
	}

	// 기본 면으로 출력
	if (wireframe)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void cMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMap::BoxSetup()
{
	// ====================================바닥==================================
	cBoundBox* GroundBox1 = new cBoundBox;
	GroundBox1->GetBox(D3DXVECTOR3(-8.2, 3.3, -2), D3DXVECTOR3(4.2, 0.1, 2.4));
	m_pGroundBox.push_back(GroundBox1);

	cBoundBox* GroundBox2 = new cBoundBox;
	GroundBox2->GetBox(D3DXVECTOR3(19.5, 3.4, -3.6), D3DXVECTOR3(2.0, 0.1, 2.3));
	m_pGroundBox.push_back(GroundBox2);

	cBoundBox* GroundBox3 = new cBoundBox;
	GroundBox3->GetBox(D3DXVECTOR3(-6.5, 3.51, -5.45), D3DXVECTOR3(2.5, 0.05, 1));
	m_pGroundBox.push_back(GroundBox3);

	cBoundBox* GroundBox4 = new cBoundBox;
	GroundBox4->GetBox(D3DXVECTOR3(-7.1, 3.51, -7.3), D3DXVECTOR3(1.85, 0.05, 1));
	m_pGroundBox.push_back(GroundBox4);

	// ====================================벽면==================================
	//cBoundBox* WallBox1 = new cBoundBox;
	//WallBox1->GetBox(D3DXVECTOR3(16, 5.3, -1.2), D3DXVECTOR3(5, 1.8, 0.1));
	//m_pWallBox.push_back(WallBox1);
	//
	//cBoundBox* WallBox2 = new cBoundBox;
	//WallBox2->GetBox(D3DXVECTOR3(6, 5.3, -0.8), D3DXVECTOR3(5, 1.8, 0.1));
	//m_pWallBox.push_back(WallBox2);
	//
	//cBoundBox* WallBox3 = new cBoundBox;
	//WallBox3->GetBox(D3DXVECTOR3(1.5, 5, -2.6), D3DXVECTOR3(0.1, 1.5, 2));
	//m_pWallBox.push_back(WallBox3);
	//
	//cBoundBox* WallBox4 = new cBoundBox;
	//WallBox4->GetBox(D3DXVECTOR3(-6, 5, -4.7), D3DXVECTOR3(7.5, 1.5, 0.01));
	//m_pWallBox.push_back(WallBox4);
	//
	for (size_t i = 0; i < m_pGroundBox.size(); i++)
		m_pControl->SetGroundVertex(m_pGroundBox[i]->Boxvertex());

}

void cMap::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Direction = D3DXVECTOR3(1, -1, 1);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}