#include "stdafx.h"
#include "cScene_03_Snow.h"
#include "cCamera.h"
#include "cParticleEmitter.h"

cScene_03_Snow::cScene_03_Snow()
{
}


cScene_03_Snow::~cScene_03_Snow()
{
}


HRESULT cScene_03_Snow::Scene_Init()
{
	m_pParticle = new cParticleEmitter();

	m_pParticle->SetActive(true);


	//배열을 2 개이상 
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.1f);


	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../../Resources/Testures/particle_0.png");

	//파티클 랜더러 셋팅
	m_pParticle->Init(
		5000,				//최대 파티클 수
		500.0f,				//초당 파티클 발생 량
		7,					//하나의 파티클 입자 라이프 최소값
		10,					//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, -1.0f, 0),	//파티클 입자 속도 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, -2.0f, 0),	//파티클 입자 속도 최대값 ( 로컬기준 )
		D3DXVECTOR3(1, 3, 1),	//파티클 입자 가속 최소값 ( 로컬기준 )
		D3DXVECTOR3(-1, 5, -1), //파티클 입자 가속 최대값 ( 로컬기준 )
		colors,				//컬러 배열
		scales,				//스케일 배열
		1.1f,				//입자크기 최소값
		3.2f,				//최대값
		pTex,				//텍스쳐
		false);


	//눈
	/*
	m_pParticle->EmissionType = PATICLE_EMISSION_TYPE::BOX;

	m_pParticle->MinEmissionRangeX = -10.0f;
	m_pParticle->MaxEmissionRangeX = 10.0f;

	m_pParticle->MinEmissionRangeY = 10.0f;
	m_pParticle->MaxEmissionRangeY = 10.0f;

	m_pParticle->MinEmissionRangeZ = -10.0f;
	m_pParticle->MaxEmissionRangeZ = 10.0f;
	*/

	m_pParticle->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_pParticle->SphereEmissionRange = 3.0f;


	m_pParticle->StartEmission();

	return S_OK;
}

void cScene_03_Snow::Scene_Release()
{
	m_pParticle->Release();
	SAFE_DELETE(m_pParticle);
}

void cScene_03_Snow::Scene_Update(float timDelta)
{
	m_pParticle->Update(timDelta);
	m_pParticle->pTransform->DefaultControl2(timDelta);
}

void cScene_03_Snow::Scene_Render1()
{
	m_pParticle->Render();
	m_pParticle->pTransform->RenderGimozo();
}


void cScene_03_Snow::Scene_RenderSprite()
{

}