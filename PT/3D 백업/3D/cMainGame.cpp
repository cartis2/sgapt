#include "stdAfx.h"
#include "cMainGame.h"
#include "cMap.h"

cMainGame::cMainGame(void)
	: m_pMap(NULL)
	//UI관련
	, m_pSprite(NULL)
	, m_pSprite2(NULL)
	, m_pSprite3(NULL)
	, m_pSprite4(NULL)
	, m_pTexture(NULL)
	, m_pTexture2(NULL)
	, m_pTexture3(NULL)
	, m_pTexture4(NULL)
	, m_pFont(NULL)
	//
	, pos_x(1120)
	, pos_y(0)
	, m_R(255)
	, m_R2(255)
	, m_isLButtonDown(false)
	, m_move(false)
	, m_close(false)
	, agree(false)
	, cancle(false)
	, m_isSel(false)
	, sel(0)
{
	push_i = -1;
}

cMainGame::~cMainGame(void)
{
	//UI TEST
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite2);
	SAFE_RELEASE(m_pTexture2);
	SAFE_RELEASE(m_pFont);

	SAFE_RELEASE(m_pSprite3);
	SAFE_RELEASE(m_pTexture3);
	SAFE_RELEASE(m_pFont3);

	SAFE_RELEASE(m_pSprite4);
	SAFE_RELEASE(m_pTexture4);
	SAFE_RELEASE(m_pFont4);
	SAFE_DELETE(m_pMap);

	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pFontManager->Destory();
	g_pSkinnedMeshManager->Destroy();
}

void cMainGame::Setup()
{
	m_pMap = new cMap;
	m_pMap->Setup();

	//UI
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 25;
	fd.Width = 12;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "umberto");	//글꼴 스타일
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	LPDIRECT3DTEXTURE9 pTexture = NULL;
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./RES/IMAGE/인벤.png",
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexture);

	LPDIRECT3DTEXTURE9 pTexture2 = NULL;
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./RES/IMAGE/닫기.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo2,
		NULL,
		&m_pTexture2);
	//수락
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./RES/IMAGE/수락.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo3,
		NULL,
		&m_pTexture3);
	//거절
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"./RES/IMAGE/거절.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo4,
		NULL,
		&m_pTexture4);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite2);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite3);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite4);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	if (m_pMap) m_pMap->Update();
	
	if (push_i == 1)
	{
		if (pos_x >= 840)
			pos_x -= 10;

	}
	else if (push_i != 1)
	{
		if (pos_x <= 1120)
			pos_x += 10;

	}
	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pMap) m_pMap->Render();


	if (!m_close)
	{



		static float fAngle = 0.0f;
		fAngle += 0.1f;
		D3DXMATRIXA16 matWorld;

		D3DXMatrixTranslation(&matWorld, pos_x, pos_y, 0);

		//D3DXMatrixRotationZ(&matWorld, fAngle);



		/*if(agree==true)
		{
		s = s2;
		}

		if (cancle == true)
		{
		s = s3;
		}
		if (agree==false && cancle==false)
		{
		s = ("퀘스트를 수락하시겠습니까?");
		}
		*/
		RECT rc;
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND /*| D3DXSPRITE_SORT_TEXTURE*/);
		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(m_pTexture,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(200, 255, 255, 255));

		//std::string s("퀘스트를 수락하였습니다.");
		//std::string s2("퀘스트를 거절하였습니다.");
		//std::string s3("퀘스트");
		//std::string s5;
		//m_pFont->DrawTextA(m_pSprite,
		//	s5.c_str(),
		//	s5.length(),
		//	&rc,
		//	DT_CENTER | DT_VCENTER | DT_WORDBREAK,
		//	D3DCOLOR_ARGB(200, 128, 64, 64));

		//switch (sel)
		//{
		//case 1:
		//	
		//	s5 = s;
		//	m_pFont->DrawTextA(m_pSprite,
		//		s5.c_str(),
		//		s5.length(),
		//		&rc,
		//		DT_CENTER | DT_VCENTER | DT_WORDBREAK,
		//		D3DCOLOR_ARGB(200, 128, 64, 64));

		//	break;
		//case 2:
		//	
		//	s5 = s2;
		//	//m_pFont->Release();
		//	
		//m_pFont->DrawTextA(m_pSprite,
		//	s5.c_str(),
		//	s5.length(),
		//	&rc,
		//	DT_CENTER | DT_VCENTER | DT_WORDBREAK,
		//	D3DCOLOR_ARGB(200, 128, 64, 64));

		//	break;
		//default:
		//	//m_pFont->Release();

		//	s5 = s3;
		//	m_pFont->DrawTextA(m_pSprite,
		//		s3.c_str(),
		//		s3.length(),
		//		&rc,
		//		DT_CENTER | DT_WORDBREAK,
		//		D3DCOLOR_ARGB(200, 128, 64, 64));

		//	break;
		//}

		m_pSprite->End();


		//	//닫힘창
		//	D3DXMATRIXA16 matWorld2;

		//	D3DXMatrixTranslation(&matWorld2, pos_x + 300, pos_y, 0);
		//	RECT rc2;
		//	SetRect(&rc2, 0, 0, m_stImageInfo2.Width, m_stImageInfo2.Height);
		//	m_pSprite2->Begin(D3DXSPRITE_ALPHABLEND /*| D3DXSPRITE_SORT_TEXTURE*/);
		//	m_pSprite2->SetTransform(&matWorld2);
		//	m_pSprite2->Draw(m_pTexture2,
		//		&rc2,
		//		&D3DXVECTOR3(0, 0, 0),
		//		&D3DXVECTOR3(0, 0, 0),
		//		D3DCOLOR_ARGB(200, 255, 255, 255));

		//	/*m_pFont->DrawTextA(m_pSprite,
		//		s.c_str(),
		//		s.length(),
		//		&rc,
		//		DT_TOP | DT_LEFT | DT_WORDBREAK,
		//		D3DCOLOR_ARGB(200, 128, 64, 64));*/
		//	m_pSprite2->End();

		//	//수락
		//	D3DXMATRIXA16 matWorld3;

		//	D3DXMatrixTranslation(&matWorld3, pos_x+50, pos_y+200, 0);

		//	//D3DXMatrixRotationZ(&matWorld, fAngle);
		//	
		//	RECT rc3;
		//	SetRect(&rc3, 0, 0, m_stImageInfo3.Width, m_stImageInfo3.Height);

		//	m_pSprite3->Begin(D3DXSPRITE_ALPHABLEND /*| D3DXSPRITE_SORT_TEXTURE*/);
		//	m_pSprite3->SetTransform(&matWorld3);
		//	m_pSprite3->Draw(m_pTexture3,
		//		&rc3,
		//		&D3DXVECTOR3(0, 0, 0),
		//		&D3DXVECTOR3(0, 0, 0),
		//		D3DCOLOR_ARGB(250, m_R, 255, 255));


		//	m_pSprite3->End();

		//	//거절

		//	D3DXMATRIXA16 matWorld4;

		//	D3DXMatrixTranslation(&matWorld4, pos_x + 200, pos_y + 200, 0);

		//	//D3DXMatrixRotationZ(&matWorld, fAngle);

		//	RECT rc4;
		//	SetRect(&rc4, 0, 0, m_stImageInfo4.Width, m_stImageInfo4.Height);

		//	m_pSprite4->Begin(D3DXSPRITE_ALPHABLEND /*| D3DXSPRITE_SORT_TEXTURE*/);
		//	m_pSprite4->SetTransform(&matWorld4);
		//	m_pSprite4->Draw(m_pTexture4,
		//		&rc4,
		//		&D3DXVECTOR3(0, 0, 0),
		//		&D3DXVECTOR3(0, 0, 0),
		//		D3DCOLOR_ARGB(250, m_R2, 255, 255));


		//	m_pSprite4->End();

		//
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pMap) m_pMap->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{


		case VK_SPACE:
		{
		}
		break;
		case VK_RIGHT:
		{
			//pos_x+=0.1f;
		}
		break;
		case 'I':
		{
			push_i *= -1;




		}
		break;
		}
	}
	break;


	case WM_LBUTTONDOWN:
	{
		//if (pos_x + 300 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 30 < pos_x + 300
		//	&& pos_y < m_ptPrevMouse.y&&m_ptPrevMouse.y - 30 < pos_y)
		//{
		//	m_close = true;
		//}
		//else if (pos_x + 50 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 50
		//	&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
		//{
		//	//agree = true;
		//	sel = 1;
		//}
		//else if (pos_x + 200 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 200
		//	&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
		//{
		//	//cancle = true;
		//	sel = 2;
		//}
		//else if(pos_x<m_ptPrevMouse.x&&m_ptPrevMouse.x- 330<pos_x
		//	&&pos_y<m_ptPrevMouse.y&&m_ptPrevMouse.y - 277<pos_y)//&&m_ptPrevMouse.x<m_stImageInfo.Width+100)//&&m_ptPrevMouse.x<m_stImageInfo.Width)
		if (pos_x < m_ptPrevMouse.x&&m_ptPrevMouse.x - 300 < pos_x
			&&pos_y < m_ptPrevMouse.y&&m_ptPrevMouse.y - 30 < pos_y)//&&m_ptPrevMouse.x<m_stImageInfo.Width+100)//&&m_ptPrevMouse.x<m_stImageInfo.Width)
		{
			m_isLButtonDown = true;
		}
		//m_isLButtonDown = true;
		m_isSel = true;
		///
		//m_ptPrevMouse.x = m_ptPrevMouse.x - ptS.x;
		///
		//ptS.y = LOWORD(lParam);
		//m_ptPrevMouse.x = LOWORD(lParam);
		/*if (m_move)
		{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		}*/
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
		m_move = false;

		if (m_isSel == true)
		{
			if (pos_x + 300 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 30 < pos_x + 300
				&& pos_y < m_ptPrevMouse.y&&m_ptPrevMouse.y - 30 < pos_y)
			{
				m_close = true;
			}
			else if (pos_x + 50 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 50
				&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
			{
				//agree = true;
				sel = 1;
			}
			else if (pos_x + 200 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 200
				&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
			{
				//cancle = true;
				sel = 2;
			}

		}


	}
	break;

	case WM_MOUSEMOVE:
	{
		m_move = true;
		m_R = 255;
		m_R2 = 255;


		if (m_move)
		{
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);


			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);


			ptS.x = LOWORD(lParam);
			ptS.y = LOWORD(lParam);
			if (pos_x < m_ptPrevMouse.x&&m_ptPrevMouse.x - 330 < pos_x
				&&pos_y < m_ptPrevMouse.y&&m_ptPrevMouse.y - 277 < pos_y)
			{
			}

			if (m_isLButtonDown)
			{
				float nDeltaX = pt.x - m_ptPrevMouse.x;
				float nDeltaY = pt.y - m_ptPrevMouse.y;

				//m_ptPrevMouse = pt;
				pos_x = m_ptPrevMouse.x;
				pos_y = m_ptPrevMouse.y;
			}

		}
		if (pos_x + 50 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 50
			&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
		{
			//if(m_R!=0)
			m_R = 0;
		}
		if (pos_x + 200 < m_ptPrevMouse.x&&m_ptPrevMouse.x - 92 < pos_x + 200
			&& pos_y + 200 < m_ptPrevMouse.y&&m_ptPrevMouse.y - 60 < pos_y + 200)
		{
			m_R2 = 0;
		}

		if (pos_x  < m_ptPrevMouse.x&&m_ptPrevMouse.x)
		{
			push_i = 1;
		}
		else
		{
			push_i = -1;
		}
	}
	break;
	}

}