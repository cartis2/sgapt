#pragma once

class cGrid;
class cCamera;
class cCrtController;
class cSkinnedMesh;

// Map Test
class iMap;
class cMtlTex;

class cBoundBox;
class cMainGame
{
private:
	cGrid*	m_pGrid;
	cCamera* m_pCamera;
	cCrtController* m_pControl;

	// xFile
	cSkinnedMesh* m_pSkinnedMesh;

	// Map Test;
	iMap* m_pMap;
	vector<cMtlTex*> m_vecMtlTex;
	LPD3DXMESH		 m_pMapMesh;

	bool wireframe;

	cBoundBox* Box;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
};