#include "stdafx.h"
#include "cScene_02_QuadPaticleEmitter.h"
#include "cCamera.h"
#include "cQuadParticleEmitter.h"

cScene_02_QuadParticleEmitter::cScene_02_QuadParticleEmitter()
{
}


cScene_02_QuadParticleEmitter::~cScene_02_QuadParticleEmitter()
{
}


HRESULT cScene_02_QuadParticleEmitter::Scene_Init()
{
	m_pParticle = new cQuadParticleEmitter();

	m_pParticle->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);
	scales.push_back(5.0f);

	m_pParticle->Init(
		100,
		10.0f,
		3.5f,
		4.0f,
		D3DXVECTOR3(0, 5, 0),
		D3DXVECTOR3(0, 6, 0),
		D3DXVECTOR3(0, 0.5, 0),
		D3DXVECTOR3(0, 0.8, 0),
		D3DXVECTOR3(-90 * ONE_RAD, 0, 90 * ONE_RAD),		//초기시작시 회전Min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0.5),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0.5),				//초당 회전할 화전 량 Max
		D3DXVECTOR3(0, 0, 1),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 2),				//초당 회전 가속 Max
		colors, scales,
		3.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../../Resources/Testures/alpha.png"),
		true);

	m_pParticle->StartEmission();

	//카메라 소팅
	m_pParticle->SetCameraSort(this->pMainCamera, true);


	return S_OK;
}

void cScene_02_QuadParticleEmitter::Scene_Release()
{
	m_pParticle->Release();
	SAFE_DELETE(m_pParticle);
}

void cScene_02_QuadParticleEmitter::Scene_Update(float timeDelta)
{
	m_pParticle->Update(timeDelta);
	m_pParticle->pTransform->DefaultControl2(timeDelta);

	if (KEY_MGR->IsStayDown(VK_SPACE))
		m_pParticle->StartEmission();
	else
		m_pParticle->StopEmission();
}

void cScene_02_QuadParticleEmitter::Scene_Render1()
{
	m_pParticle->Render();
	m_pParticle->pTransform->RenderGimozo(Device);
}


void cScene_02_QuadParticleEmitter::Scene_RenderSprite()
{

}