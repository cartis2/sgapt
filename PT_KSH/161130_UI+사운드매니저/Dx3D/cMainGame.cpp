#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
#include "cSoundTest.h"

enum eUITag
{
	E_TEXTVIEW = 3,
	E_BUTTON1,
	E_BUTTON2,
};
cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pUIRoot(NULL)
	, m_pSoundTest(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pUIRoot);

	m_pSoundTest->release();
	SAFE_DELETE(m_pSoundTest);

	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pFontManager->Destory();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pSoundTest = new cSoundTest;
	m_pSoundTest->init();

	m_pSoundTest->addSound("사운드1", "bgm1.mp3", true, true);
	m_pSoundTest->play("사운드1", 1.0f);











	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pImageView = new cUIImageView;
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetSpriteTexture(
		"./UI/panel-info.png.png",
		&stImageInfo);
	pImageView->SetTexture(pTexture);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	pImageView->SetLocalPos(D3DXVECTOR3(100, 50, 0));
	m_pUIRoot = pImageView;


	cUITextView* pTextView = new cUITextView;
	pTextView->SetText("동대문 역사문화 공원 역에서 인상이 10마리를 잡아오세요.");
	pTextView->SetFont(g_pFontManager->GetFont(cFontManager::E_FT_NORMAL));
	pTextView->SetLocalPos(D3DXVECTOR3(100, 100, 0));
	pTextView->SetSize(ST_SIZE(321, 200));
	pTextView->SetDrawTextFormat(DT_CENTER | DT_TOP | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	pTextView->SetTag(E_TEXTVIEW);
	pTextView->AutoRelease();
	m_pUIRoot->AddChild(pTextView);
	
	cUIButton* pButton = NULL;
	pButton = new cUIButton;
	pButton->SetTexture("./UI/btn-med-up.png.png",
		"./UI/btn-med-over.png.png",
		"./UI/btn-med-down.png.png");
	pButton->SetLocalPos(D3DXVECTOR3(135, 330, 0));
	pButton->SetDelegate(this);
	pButton->SetTag(E_BUTTON1);
	pButton->AutoRelease();
	m_pUIRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetTexture("./UI/btn-med-up.png.png",
		"./UI/btn-med-over.png.png",
		"./UI/btn-med-down.png.png");
	pButton->SetLocalPos(D3DXVECTOR3(135, 400, 0));
	pButton->SetDelegate(this);
	pButton->SetTag(E_BUTTON2);
	pButton->AutoRelease();
	m_pUIRoot->AddChild(pButton);

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pCamera)
		m_pCamera->Update(NULL/*m_pController->GetPosition()*/);
	
	if(m_pUIRoot)
		m_pUIRoot->Update();

	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{

	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_pGrid->Render();
	
	if (m_pUIRoot)
	{
		m_pUIRoot->Render(m_pSprite);
	}
	
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	//m_pSoundTest->play("사운드1", 1.0f);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	switch(message)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_SPACE:
				{
				}
				break;
			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
		}
		break;
	}
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

void cMainGame::OnClick( cUIButton* pSender )
{
	cUITextView* pTextView = (cUITextView*)m_pUIRoot->GetChildByTag(E_TEXTVIEW);
	if(pTextView)
	{
		if (pSender->GetTag() == E_BUTTON1)
		{
			pTextView->SetText("E_BUTTON1");
		}
		else if (pSender->GetTag() == E_BUTTON2)
		{
			pTextView->SetText("E_BUTTON2");
		}
	}
}

