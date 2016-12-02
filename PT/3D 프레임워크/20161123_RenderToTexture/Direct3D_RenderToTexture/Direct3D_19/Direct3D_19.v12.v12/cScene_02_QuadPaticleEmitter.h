#pragma once

#include "cscene.h"

class cQuadParticleEmitter;

class cScene_02_QuadParticleEmitter : public cScene
{
private:
	cQuadParticleEmitter* m_pParticle;

public:
	cScene_02_QuadParticleEmitter();
	~cScene_02_QuadParticleEmitter();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();


	virtual void Scene_RenderSprite();
};

