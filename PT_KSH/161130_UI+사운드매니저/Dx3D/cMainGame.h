#pragma once

class cCamera;
class cGrid;
class cSoundTest;

#include "cUIButton.h"

class cMainGame : public iUIButtonDelegate
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	LPD3DXSPRITE				m_pSprite;
	cUIObject*					m_pUIRoot;

	cSoundTest*					m_pSoundTest;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();

	// iUIButtonDelegate override
	virtual void OnClick(cUIButton* pSender) override;
};

