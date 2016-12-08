#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	map<string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(char* szPath, vector<cGroup*>& vecGroup, D3DXMATRIXA16* pmat = NULL);
	LPD3DXMESH Load(char* szPath, vector<cMtlTex*>& vecMtlTex, vector<D3DXVECTOR3>& vertex, D3DXMATRIXA16* pmat = NULL);
private:
	void LoadMtlLib(char* szPath);
	void LoadMtlLib(char* szPath, vector<cMtlTex*>& vecMtlTex);
};

