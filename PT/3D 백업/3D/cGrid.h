#pragma once

//class cPyramid;

class cGrid
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;
	//vector<cPyramid*>	m_vecPyramid;

public:
	cGrid(void);
	~cGrid(void);

	void Setup(int nNumLine);
	void Render();
};

