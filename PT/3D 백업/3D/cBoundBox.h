#pragma once
class cBoundBox
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	vector<D3DXVECTOR3> BoundVertex;

public:
	void GetBox(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Render();

	vector<D3DXVECTOR3> Boxvertex() { return BoundVertex; }

	cBoundBox();
	~cBoundBox();
};

