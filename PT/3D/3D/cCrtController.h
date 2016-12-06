#pragma once

class iMap;
class cCrtController
{
private:
	float						m_fSpeed;
	float						m_fAngle;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);

	vector<D3DXVECTOR3> m_vecVertex;
	D3DXVECTOR3 vPosition;

	ST_PC_VERTEX RayX[2];
	ST_PC_VERTEX RayY[2];

public:
	cCrtController(void);
	~cCrtController(void);

	void Setup(vector<D3DXVECTOR3> vertex);
	void Update();
	bool GetHeight(IN float x, OUT float& y, IN float z);
	
	D3DXVECTOR3* GetPosition()  { return &m_vPosition; }
	D3DXMATRIXA16* GetWorldTM() { return &m_matWorld; }

	void RayRender();
};

