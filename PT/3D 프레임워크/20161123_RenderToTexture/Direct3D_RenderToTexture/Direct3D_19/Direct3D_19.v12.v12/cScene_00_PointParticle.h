#pragma once

#include "cScene.h"

class cScene_00_PointParticle : public cScene
{
private:
	struct PARTICLE_VERTEX{
		D3DXVECTOR3 pos;
		float		size;
		DWORD		color;
		enum{ FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
	};

private:
	PARTICLE_VERTEX		m_ParticleVertex[3];
	LPDIRECT3DTEXTURE9	m_pTexture;			//파티클에 사용될 Texture

public:
	cScene_00_PointParticle();
	~cScene_00_PointParticle();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update( float timDelta );

	virtual void Scene_Render1();


	virtual void Scene_RenderSprite();
};

