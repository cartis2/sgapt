#pragma once

class iMap;
class cOBB;
class cCrtController
{
private:
	float						m_fSpeed;
	float						m_fAngle;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);

	vector<D3DXVECTOR3> mapVertex;
	vector<D3DXVECTOR3> groundVertex; // 바닥
	vector<D3DXVECTOR3> wallVertex;   // 벽면
	D3DXVECTOR3 vPosition;

	LPD3DXFONT	m_pDefultFont; // 글자

	ST_PC_VERTEX RayX[2];
	ST_PC_VERTEX RayY[2];

	// 테스트
	cOBB* m_playerOBB;
	vector<cOBB> m_vecWall;
	D3DXCOLOR color;
private:
	void PrintText(string str, int x, int y, DWORD color);
	void SetWall();

public:
	cCrtController(void);
	~cCrtController(void);

	void Setup();
	void Update();
	bool GetHeight(IN float x, OUT float y, IN float z);

	D3DXVECTOR3* GetPosition() { return &m_vPosition; }
	D3DXMATRIXA16* GetWorldTM() { return &m_matWorld; }

	void SetMapVertex(vector<D3DXVECTOR3> vertex);
	void SetGroundVertex(vector<D3DXVECTOR3> vertex);
	void SetWallVertex(vector<D3DXVECTOR3> vertex);

	void Render();
	void WallCollision();
};
