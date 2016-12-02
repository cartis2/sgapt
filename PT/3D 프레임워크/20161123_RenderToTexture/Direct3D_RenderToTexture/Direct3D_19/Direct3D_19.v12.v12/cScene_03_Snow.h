#pragma once

#include "cscene.h"

class cParticleEmitter;

class cScene_03_Snow : public cScene
{
private:
	cParticleEmitter* m_pParticle;

public:
	cScene_03_Snow();
	~cScene_03_Snow();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();


	virtual void Scene_RenderSprite();
};

