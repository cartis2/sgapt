#pragma once
class cBoundBox
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	vector<D3DXVECTOR3> vecVertex;
	D3DXMATRIXA16 world;
public:
	void GetBox(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Render();

	vector<D3DXVECTOR3> Boxvertex() { return vecVertex; }

	cBoundBox();
	~cBoundBox();
};

