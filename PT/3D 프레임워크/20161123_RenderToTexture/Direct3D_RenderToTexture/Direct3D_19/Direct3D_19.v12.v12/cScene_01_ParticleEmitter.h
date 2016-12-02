#pragma once

#include "cScene.h"

class cParticleEmitter;

class cScene_01_ParticleEmitter : public cScene
{
private:
	cParticleEmitter* m_pParticle;

public:
	cScene_01_ParticleEmitter();
	~cScene_01_ParticleEmitter();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();


	virtual void Scene_RenderSprite();
};

