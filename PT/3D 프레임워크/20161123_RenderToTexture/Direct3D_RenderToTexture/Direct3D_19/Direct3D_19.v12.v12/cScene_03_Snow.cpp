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


	//�迭�� 2 ���̻� 
	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(0.1f);
	scales.push_back(0.1f);


	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../../Resources/Testures/particle_0.png");

	//��ƼŬ ������ ����
	m_pParticle->Init(
		5000,				//�ִ� ��ƼŬ ��
		500.0f,				//�ʴ� ��ƼŬ �߻� ��
		7,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
		10,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
		D3DXVECTOR3(0, -1.0f, 0),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(0, -2.0f, 0),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
		D3DXVECTOR3(1, 3, 1),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
		D3DXVECTOR3(-1, 5, -1), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
		colors,				//�÷� �迭
		scales,				//������ �迭
		1.1f,				//����ũ�� �ּҰ�
		3.2f,				//�ִ밪
		pTex,				//�ؽ���
		false);


	//��
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