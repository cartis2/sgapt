#include "stdafx.h"
#include "cScene_01_ParticleEmitter.h"
#include "cCamera.h"
#include "cParticleEmitter.h"

cScene_01_ParticleEmitter::cScene_01_ParticleEmitter()
{
}


cScene_01_ParticleEmitter::~cScene_01_ParticleEmitter()
{
}


HRESULT cScene_01_ParticleEmitter::Scene_Init()
{
	m_pParticle = new cParticleEmitter();

	m_pParticle->SetActive(true);

	//
	// ������ ����
	//

	//
	//�迭�� 2 ���̻�
	//VEC_COLOR colors;
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );

	//VEC_SCALE scales;
	//scales.push_back( 1.0f );
	//scales.push_back( 1.0f );
	//scales.push_back( 1.0f );

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//"../../Resources/Testures/particle_0.png" );

	//��ƼŬ ������ ����
	//m_pParticle->Init(
	//1000,				//�ִ� ��ƼŬ ��
	//200.0f,				//�ʴ� ��ƼŬ �߻� ��
	//5,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	//5,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	//D3DXVECTOR3(  0, 0, 5 ),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
	//D3DXVECTOR3(  0, 0, 5 ),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
	//D3DXVECTOR3(  0, 0, 0 ),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
	//D3DXVECTOR3(  0, 0, 0 ), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
	//colors,				//�÷� �迭
	//scales,				//������ �迭
	//1.0f,				//����ũ�� �ּҰ�
	//1.0f,				//�ִ밪
	//pTex,				//�ؽ���
	//true );
	//

	//
	// ���� ����
	//
	
	//�迭�� 2 ���̻�
	VEC_COLOR colors;
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 1.0f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.9f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.1f ) );
	colors.push_back( D3DXCOLOR( 0.1f, 1.0f, 1.0f, 0.0f ) );

	VEC_SCALE scales;
	scales.push_back( 3.0f );
	scales.push_back( 1.0f );
	scales.push_back( 1.0f );
	scales.push_back( 0.5f );
	scales.push_back( 0.1f );

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	"../../Resources/Testures/particle_0.png" );

	//��ƼŬ ������ ����
	m_pParticle->Init(
	1000,				//�ִ� ��ƼŬ ��
	200.0f,				//�ʴ� ��ƼŬ �߻� ��
	3,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	5,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	D3DXVECTOR3(  0, 0, 0 ),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
	D3DXVECTOR3(  0, 0, 0 ),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
	D3DXVECTOR3(  1, 1, 1 ),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
	D3DXVECTOR3(  -1, -1, -1 ), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
	colors,				//�÷� �迭
	scales,				//������ �迭
	0.1f,				//����ũ�� �ּҰ�
	0.2f,				//�ִ밪
	pTex,				//�ؽ���
	false );
	


	//
	// ȭ�� ����
	//
	//
	//VEC_COLOR colors;
	//colors.push_back( D3DXCOLOR( 0.0f, 0.0f, 1.0f, 0.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 0.0f, 1.0f, 0.5f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 0.0f, 1.0f, 1.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
	//colors.push_back( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 0.0f ) );


	//VEC_SCALE scales;
	//scales.push_back( 0.0f );
	//scales.push_back( 0.1f );
	//scales.push_back( 0.3f );
	//scales.push_back( 0.8f );
	//scales.push_back( 1.0f );
	//scales.push_back( 1.5f );

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//"../../Resources/Testures/FireExplosionBlurredGray.png" );

	////��ƼŬ ������ ����
	//m_pParticle->Init(
	//1000,
	//100.0f,
	//3,
	//3.5f,
	//D3DXVECTOR3(  0, 0, 3 ),
	//D3DXVECTOR3(  0, 0, 3 ),
	//D3DXVECTOR3(  0, 0.2f, -0.5f ),
	//D3DXVECTOR3(  0, 0.4f, -1.0f ),
	//colors,
	//scales,
	//2.3f,
	//3.0f,
	//pTex
	//);
	//

	//
	// ����
	//

	////�迭�� 2 ���̻� 
	//VEC_COLOR colors;
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.9f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.1f));
	//colors.push_back(D3DXCOLOR(0.1f, 1.0f, 1.0f, 0.0f));

	//VEC_SCALE scales;
	//scales.push_back(0.1f);
	//scales.push_back(0.5f);
	//scales.push_back(1.0f);
	//scales.push_back(2.5f);
	//scales.push_back(3.1f);

	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//	"../../Resources/Testures/particle_0.png");

	////��ƼŬ ������ ����
	//m_pParticle->Init(
	//	1000,				//�ִ� ��ƼŬ ��
	//	200.0f,				//�ʴ� ��ƼŬ �߻� ��
	//	3,					//�ϳ��� ��ƼŬ ���� ������ �ּҰ�
	//	5,					//�ϳ��� ��ƼŬ ���� ������ �ִ밪
	//	D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� �ӵ� �ּҰ� ( ���ñ��� )
	//	D3DXVECTOR3(0, 0, 0),	//��ƼŬ ���� �ӵ� �ִ밪 ( ���ñ��� )
	//	D3DXVECTOR3(1, 1, 1),	//��ƼŬ ���� ���� �ּҰ� ( ���ñ��� )
	//	D3DXVECTOR3(-1, -1, -1), //��ƼŬ ���� ���� �ִ밪 ( ���ñ��� )
	//	colors,				//�÷� �迭
	//	scales,				//������ �迭
	//	1.1f,				//����ũ�� �ּҰ�
	//	3.2f,				//�ִ밪
	//	pTex,				//�ؽ���
	//	false);


	return S_OK;
}

void cScene_01_ParticleEmitter::Scene_Release()
{
	m_pParticle->Release();
	SAFE_DELETE(m_pParticle);
}

void cScene_01_ParticleEmitter::Scene_Update(float timeDelta)
{
	m_pParticle->Update(timeDelta);
	m_pParticle->pTransform->DefaultControl2(timeDelta);

	if (KEY_MGR->IsStayDown(VK_SPACE))
		m_pParticle->StartEmission();
	else
		m_pParticle->StopEmission();

	if (KEY_MGR->IsOnceDown(VK_RETURN))
		m_pParticle->Burst(100, 1.4f, 2.7f, 0.1f, 0.5f);
}

void cScene_01_ParticleEmitter::Scene_Render1()
{
	m_pParticle->Render();
	m_pParticle->pTransform->RenderGimozo(Device);
}


void cScene_01_ParticleEmitter::Scene_RenderSprite()
{

}