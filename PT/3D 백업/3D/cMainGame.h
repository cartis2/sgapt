#pragma once

// ¸Ê
class cMap;

class cMainGame
{
private:
	// ¸Ê
	cMap* m_pMap;

	//UI TEST
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	LPDIRECT3DTEXTURE9			m_pTexture;
	LPD3DXFONT					m_pFont;

	LPD3DXSPRITE				m_pSprite2;
	LPDIRECT3DTEXTURE9			m_pTexture2;
	D3DXIMAGE_INFO				m_stImageInfo2;

	//¼ö¶ô
	LPD3DXSPRITE				m_pSprite3;
	LPDIRECT3DTEXTURE9			m_pTexture3;
	D3DXIMAGE_INFO				m_stImageInfo3;
	LPD3DXFONT					m_pFont3;

	//°ÅÀý
	LPD3DXSPRITE				m_pSprite4;
	LPDIRECT3DTEXTURE9			m_pTexture4;
	D3DXIMAGE_INFO				m_stImageInfo4;
	LPD3DXFONT					m_pFont4;
	POINT pt;
	POINT ptS;
	bool m_close;
	float pos_x;
	float pos_y;
	int m_R;
	int m_R2;
	bool m_isSel;
	std::string s;
	float save_x;
	int sel;
	bool agree;
	bool cancle;
	int push_i;
	//¸¶¿ì½º
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	bool					m_move;
	float					m_fAngleX;
	float					m_fAngleY;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};