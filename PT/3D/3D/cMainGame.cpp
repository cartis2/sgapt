#include "stdAfx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cCrtController.h"
#include "cSkinnedMesh.h"
#include "cCube.h"

// Map Test
#include "cObjLoader.h"
#include "cObjMap.h"
#include "cMtlTex.h"

#include "cBoundBox.h"

cMainGame::cMainGame(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pControl(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pMap(NULL)
	, m_pMapMesh(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pControl);
	SAFE_DELETE(m_pSkinnedMesh);

	// Map Test
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pMapMesh);
	for each (auto p in m_vecMtlTex) SAFE_RELEASE(p);

	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pFontManager->Destory();
	g_pSkinnedMeshManager->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pControl = new cCrtController;

	//m_pSkinnedMesh = new cSkinnedMesh("Zealot/", "Zealot.X");
	//m_pSkinnedMesh->SetAnimationIndex(4);
	//m_pSkinnedMesh->SetRandomTrackPosition();
	//m_pSkinnedMesh->SetPosition(D3DXVECTOR3(0, 0, 0));

	// Map Test
	//D3DXMATRIXA16 matS, matR, matT, mat;
	//D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	//D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	//mat = matS * matR;

	//D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	//D3DXMatrixIdentity(&mat);
	//mat = matS;

	//vector<D3DXVECTOR3> tempVertex;
	//cObjLoader objloader;
	//m_pMapMesh = objloader.Load("./obj/Map.obj", m_vecMtlTex, tempVertex, &mat);
	//m_pMapMesh = objloader.Load("./Test/Test.obj", m_vecMtlTex, tempVertex, &mat);
	//m_pMapMesh = objloader.Load("./Test/1.obj", m_vecMtlTex, tempVertex, &mat);
	//m_pControl->Setup(tempVertex);

	//vector<D3DXVECTOR3> temp;
	//Box = new cBoundBox;
	//Box->GetBox(D3DXVECTOR3(-4, 1.2, -0.5), D3DXVECTOR3(1, 1, 1));

	wireframe = false;
	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pControl) m_pControl->Update();
	if (m_pCamera) m_pCamera->Update(m_pControl->GetPosition());

	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN) ||
		KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if(m_pSkinnedMesh)
			m_pSkinnedMesh->SetAnimationIndex(3);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN) ||
		KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (m_pSkinnedMesh)
			m_pSkinnedMesh->SetAnimationIndex(4);
	}

	if (KEYMANAGER->isOnceKeyDown('1')) wireframe = false;
	if (KEYMANAGER->isOnceKeyDown('2')) wireframe = true;
	
	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	//if (m_pGrid) m_pGrid->Render();
	if (m_pSkinnedMesh) m_pSkinnedMesh->UpdateAndRender(m_pControl->GetWorldTM());
	if (m_pControl) m_pControl->RayRender();

	// 와이어프레임 출력
	if (wireframe)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	//Box->Render();

	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMapMesh->DrawSubset(i);
	}

	// 기본 면으로 출력
	if (wireframe)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::SetLight()	
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Direction = D3DXVECTOR3( 1,-1, 1);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}