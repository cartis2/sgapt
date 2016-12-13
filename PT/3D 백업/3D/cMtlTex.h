#pragma once

class cMtlTex : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl);
	SYNTHESIZE(DWORD, m_dwAttrID, AttrID);
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);


public:
	cMtlTex(void);
	virtual ~cMtlTex(void);

};

