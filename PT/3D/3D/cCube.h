#pragma once

class cCamera;

class cCube
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	vector<D3DXVECTOR3>  vecVertex;
	D3DXMATRIXA16 m_matWorldTM;

	float BoxX, BoxY, BoxZ;
	D3DXVECTOR3 vMax;
	D3DXVECTOR3 vMin;

private:
	void GetMaxMin();

public:
	cCube(void);
	~cCube(void);

	void Setup(D3DXCOLOR color, float size);
	void Update(D3DXMATRIXA16* pWorld);
	void Render();

	D3DXMATRIXA16* GetMatrix() { return &m_matWorldTM; }
	void SetMatrix(D3DXMATRIXA16* world) { m_matWorldTM = *world;}
	D3DXVECTOR3* GetvMax() { return &vMax; }
	D3DXVECTOR3* GetvMin() { return &vMin; }
};

