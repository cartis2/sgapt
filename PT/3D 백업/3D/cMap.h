#pragma once

class cMtlTex;
class cBoundBox;

// 캐릭터, 맵 테스트 관련 클래스
class cCamera;
class cCrtController;
class cSkinnedMesh;

class cMap
{
private:
	cCamera*        m_pCamera;
	cCrtController* m_pControl;
	cSkinnedMesh*   m_pSkinnedMesh;

	vector<cMtlTex*> m_vecMtlTex;
	LPD3DXMESH		 m_pMapMesh;
	vector<cBoundBox*> m_pGroundBox;

	bool wireframe;

	D3DXCOLOR color;
public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
	void BoxSetup();
};

